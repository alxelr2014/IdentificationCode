import os
import subprocess
import string
import random
import numpy
import math
from plotting import plotting,error_graph,error_graphwo,msg_graph,time_graph
from tqdm import tqdm
from configparser import ConfigParser

#Get the configparser object
config_object = ConfigParser()


# make sure to compile the executable first
config_object.read("conf.ini")
base_address = str(config_object['DEFAULT']['base_address'])
exe_address = base_address + "bin/main"
string_set = string.ascii_uppercase	+ string.ascii_lowercase + string.ascii_letters	+ string.digits
remove = False
alpha = 1.01
graph_path = str(config_object['DEFAULT']['graph_path'])
curr_graph_num = str(config_object['DEFAULT']['graph_number'])
def delete_files(n):
    for _i in range(n):
        file_address=  base_address + "logs/log-"+str(_i)+".txt"
        os.remove(file_address)

def run_experiments():
    # the block length is determined by the primes
    block_length = 0 
    number_of_repeats = 300
    loglog_number_of_messages = [100]
    number_of_encoding_iteration = 2
    increments = 100
    log_avg_errors = []
    avg_block_length = []
    avg_time = []
    number_of_experiments = 15
    

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
thx = numpy.linspace(loglog_messages[0], loglog_messages[-1], 400)
thy = alpha * thx
ethy = [alpha/(xp)**(alpha-1) for xp in thx]



# data_msg = {"x": block_length, "y": loglog_messages, "color": '-b' , "label": "Average of Simulations", "color_p" : 'go'}
# data_theorymsg = {"x": thx, "y": thy, "color": '-r' , "label": "Theoretical limit 1/alpha"}
# data_error = {"x": block_length, "y": error, "color": '-b', "label": "Average of Simulations"}
# data_theoryerror = {"x": thx, "y": ethy, "color": '-r' , "label": "Approximate upperbound"}
# data_time = {"x": block_length, "y": avg_time, "color": '-b', "label": "Average of Simulations"}

data_msg = {"x": loglog_messages, "y": block_length, "color": '-b' , "label": "Average of Simulations"}#, "color_p" : 'go'}
data_theorymsg = {"x": thx, "y": thy, "color": '-r' , "label": "Theoretical limit alpha"}
data_error = {"x": loglog_messages, "y": error, "color": '-b', "label": "Average of Simulations"}
# data_theoryerror = {"x": thx, "y": ethy, "color": '-r' , "label": "Approximate upperbound"}
data_time = {"x": loglog_messages, "y": avg_time, "color": '-b', "label": "Average of Simulations"}



plotting([data_msg,data_theorymsg], msg_graph(data_msg), graph_path+"msg"+curr_graph_num)

# plotting([data_error,data_theoryerror], error_graph(data_error),graph_path+"err"+curr_graph_num)
plotting([data_error], error_graphwo(data_error),graph_path+"errwo"+curr_graph_num)

plotting([data_time], time_graph(data_time),graph_path+"time"+curr_graph_num)

config_object['DEFAULT']['graph_number']= str( int(config_object['DEFAULT']['graph_number']) + 1 )

with open('conf.ini', 'w') as configfile:    # save
    config_object.write(configfile)