import os
import subprocess
import string
import random
import numpy
import math
from plotting import plotting
from tqdm import tqdm

# make sure to compile the executable first
base_address ="D:/Backup/Codes/IdentificationChannel/"
exe_address = base_address + "bin/main"
string_set = string.ascii_uppercase	+ string.ascii_lowercase + string.ascii_letters	+ string.digits
remove = False
alpha = 1.01


def delete_files(n):
    for _i in range(n):
        file_address=  base_address + "logs/log-"+str(_i)+".txt"
        os.remove(file_address)

def run_experiments():
    # the block length is determined by the primes
    block_length = 0 
    number_of_repeats = 100
    loglog_number_of_messages = [4]
    number_of_encoding_iteration = 2
    increments = 10
    log_avg_errors = []
    avg_block_length = []
    avg_time = []
    number_of_experiments = 100
    

    for _i in tqdm(range(number_of_experiments)):
        # sets up the commandline prompt to run the simulation
        file_address=  base_address + "logs/log-"+str(1)+".txt"
        random_string = ''.join(random.choices(string_set,k=13))
        random_digit = ''.join(random.choices(string.digits,k=20))
        # running the simulation
        res_string = subprocess.check_output([exe_address, str(loglog_number_of_messages[-1]), str(block_length),
             str(number_of_repeats), str(number_of_encoding_iteration), str(alpha),file_address, random_string,random_digit],shell=True).decode()
        # separating error rate and block length
        res_list = res_string.split(" ")
        # print(res_string)
        avg_block_length.append(int(res_list[0]))
        log_avg_errors.append(float(res_list[1]))
        avg_time.append(int(res_list[2]))
        loglog_number_of_messages.append(math.floor((loglog_number_of_messages[-1]+increments)))
    loglog_number_of_messages.pop()

    if remove:
        delete_files(number_of_experiments)
    return avg_block_length,loglog_number_of_messages,log_avg_errors,avg_time



block_length, loglog_messages, error, avg_time = run_experiments()
thx = numpy.linspace(block_length[0], block_length[-1], 400)
thy = 1/alpha * thx

majt_dist = len(block_length)//10

data_msg = {"x": block_length, "y": loglog_messages, "color": '-b' , "label": "Average of Simulations"}
data_theorymsg = {"x": thx, "y": thy, "color": '-r' , "label": "Theoretical limit 1/alpha"}
data_error = {"x": block_length, "y": error, "color": '-b', "label": "Average of Simulations"}
data_time = {"x": block_length, "y": avg_time, "color": '-b', "label": "Average of Simulations"}



plotting([data_msg,data_theorymsg], {"x_label": "Block Length", "y_label" : "LogLog2 of the Number of Messages",
    "legend_loc": 'upper left', "x_major_ticks": data_msg["x"][::majt_dist],
    "y_major_ticks" : data_msg["y"][::majt_dist] , "x_minor_ticks": data_msg["x"],
    "y_minor_ticks": data_msg["y"]})

plotting([data_error], {"x_label": "Block Length", "y_label" :  "Second Kind Error",
    "legend_loc": 'upper left', "x_major_ticks": data_error["x"][::majt_dist],
    "y_major_ticks" : data_error["y"][::majt_dist] , "x_minor_ticks": data_error["x"],
    "y_minor_ticks": data_error["y"]})

plotting([data_time], {"x_label": "Block Length", "y_label" : "Average Simulation Time(µs)",
    "legend_loc": 'upper left', "x_major_ticks": data_time["x"][::majt_dist],
    "y_major_ticks" : data_time["y"][::majt_dist] , "x_minor_ticks": data_time["x"],
    "y_minor_ticks": data_time["y"]})
