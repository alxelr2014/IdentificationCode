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
    log_number_of_messages = [4]
    number_of_encoding_iteration = 2
    increments = 1.5
    log_avg_errors = []
    avg_block_length = []
    number_of_experiments = 90

    for _i in range(number_of_experiments):
        # sets up the commandline prompt to run the simulation
        file_address=  base_address + "logs/log-"+str(_i)+".txt"
        random_string = ''.join(random.choices(string_set,k=13))
        # running the simulation
        res_string = subprocess.check_output([exe_address, file_address, str(log_number_of_messages[-1]), str(block_length),
             str(number_of_repeats), str(number_of_encoding_iteration), random_string],shell=True).decode()
        # separating error rate and block length
        res_list = res_string.split(" ")
        print(res_string)
        avg_block_length.append(int(res_list[0]))
        log_avg_errors.append(float(res_list[1]))
        log_number_of_messages.append(math.floor((log_number_of_messages[-1]*increments)))
    log_number_of_messages.pop()

    if remove:
        delete_files(number_of_experiments)
    return avg_block_length,log_number_of_messages,log_avg_errors


block_length, log_messages, error = run_experiments()
x = numpy.linspace(block_length[0], block_length[-1], 400)
y = numpy.exp2(x/1.3)
plotting(block_length,log_messages,"Block Length", "Log2 of the Number of Messages","linear" ,(x,y,'r'))
plotting(block_length, error, "Block Length", "Second Kind Error")

