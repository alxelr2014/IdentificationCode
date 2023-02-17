import os
import subprocess
import string
import random
import matplotlib.pyplot as plt

# make sure to compile the executable first
base_address = "C:/Users/Emad Zinoghli/Desktop/Codes/IdentificationChannel/"
exe_address = base_address + "bin/main"
string_set = string.ascii_uppercase	+ string.ascii_lowercase + string.ascii_letters	+ string.digits

def plotting(data_x, data_y , label_x, label_y,scale = "linear"):
    fig, ax = plt.subplots()
    ax.plot(data_x,data_y)
    ax.spines['right'].set_visible(False)
    ax.spines['top'].set_visible(False)
    ax.set_yscale(scale)
    plt.xlabel(label_x)
    plt.ylabel(label_y)
    plt.show()

def run_experiments():
    # the block length is determined by the primes
    block_length = 0 
    number_of_repeats = 30
    number_of_messages = [10]
    avg_errors = []
    avg_block_length = []
    number_of_experiments = 22

    for _i in range(number_of_experiments):
        # sets up the commandline prompt to run the simulation
        file_address=  base_address + "logs/log-"+str(_i)+".txt"
        random_string = ''.join(random.choices(string_set,k=13))
        # running the simulation
        res_string = subprocess.check_output([exe_address, file_address, str(number_of_messages[-1]), str(block_length), str(number_of_repeats), random_string],shell=True).decode()
        # separating error rate and block length
        res_list = res_string.split(" ")
        avg_block_length.append(int(res_list[0]))
        avg_errors.append(float(res_list[1]))
        number_of_messages.append(number_of_messages[-1]* 10)
    number_of_messages.pop()
    return avg_block_length,number_of_messages,avg_errors

block_length, messages, error = run_experiments()
plotting(block_length,messages,"Block Length", "Number of Messages", 'log')
plotting(block_length, error, "Block Length", "Second Kind Error")