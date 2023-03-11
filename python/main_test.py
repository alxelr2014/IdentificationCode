import os
import subprocess
import string
import random
import matplotlib.pyplot as plt
import numpy
import math

# make sure to compile the executable first
base_address ="D:/Backup/Codes/IdentificationChannel/"
exe_address = base_address + "bin/main"
string_set = string.ascii_uppercase	+ string.ascii_lowercase + string.ascii_letters	+ string.digits
remove = True
alpha = 1.01

def plotting(data_x, data_y , label_x, label_y,scale = "linear",second_func = None):
    fig, ax = plt.subplots()
    ax.plot(data_x,data_y)
    ax.spines['right'].set_visible(False)
    ax.spines['top'].set_visible(False)
    ax.set_yscale(scale)
    plt.xlabel(label_x)
    plt.ylabel(label_y)
    if(second_func):
        plt.plot(second_func[0], second_func[1],second_func[2])
    plt.show()

def delete_files(n):
    for _i in range(n):
        file_address=  base_address + "logs/log-"+str(_i)+".txt"
        os.remove(file_address)

def run_experiments():
    # the block length is determined by the primes
    block_length = 0 
    number_of_repeats = 30
    loglog_number_of_messages = [4]
    number_of_encoding_iteration = 2
    increments = 3
    log_avg_errors = []
    avg_block_length = []
    avg_time = []
    number_of_experiments = 150

    for _i in range(number_of_experiments):
        # sets up the commandline prompt to run the simulation
        file_address=  base_address + "logs/log-"+str(_i)+".txt"
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
x = numpy.linspace(block_length[0], block_length[-1], 400)
y = 1/alpha * x
plotting(block_length,loglog_messages,"Block Length", "LogLog2 of the Number of Messages","linear" ,(x,y,'r'))
plotting(block_length, error, "Block Length", "Second Kind Error")
plotting(block_length, avg_time, "Block Length", "Average Simulation Time(ns)")

