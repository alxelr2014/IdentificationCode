import os
import subprocess
import string
import random
import numpy
import math
from plotting import plotting,error_graph,error_graphwo,msg_graph,time_graph,error_graphth
from tqdm import tqdm
from configparser import ConfigParser

# make sure to compile the executable first


base_address = ''
exe_address = ''
string_set = ''
remove = False
alpha = 0
graph_path = '' 
curr_graph_num = ' '
number_of_encoding_iteration = 0
increments = 0
number_of_experiments = 0
number_of_repeats = 0

def delete_files(n):
    for _i in range(n):
        file_address=  base_address + "logs/log-"+str(_i)+".txt"
        os.remove(file_address)

def run_experiments():
    # the block length is determined by the primes
    block_length = 0 
    loglog_number_of_messages = [100]
    log_avg_errors = []
    avg_block_length = []
    avg_time = []
    

    for _i in tqdm(range(number_of_experiments)):
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


def plots():
    block_length, loglog_messages, error, avg_time = run_experiments()
    thx = numpy.linspace(loglog_messages[0], loglog_messages[-1], 400)
    thy = alpha * thx
    ethy = [1/(alpha*xp)**(alpha-1) for xp in thx]
    eathy = [12/(alpha* xp)**(alpha) for xp in thx]
    tth = [18*(alpha*xp/1000)**4 for xp in thx]

    data_msg = {"x": loglog_messages, "y": block_length, "color": '-b' , "label": "Average of Simulations"}#, "color_p" : 'go'}
    data_theorymsg = {"x": thx, "y": thy, "color": '-r' , "label": "Theoretical limit α"}
    data_error = {"x": loglog_messages, "y": error, "color": '-b', "label": "Average of Simulations"}
    data_theoryerror = {"x": thx, "y": ethy, "color": '-g' , "label": "Theoretical upperbound"}
    data_simerror = {"x": thx, "y": eathy, "color": '-r' , "label": "Trend of Simulation"}
    data_time = {"x": loglog_messages, "y": avg_time, "color": '-b', "label": "Average of Simulations"}
    data_theory_time = {"x": thx, 'y': tth, 'color': '-r', 'label' : 'Theoretical O(n^4)'}

    settings = str(alpha)+";"+str(number_of_repeats)+";"+str(number_of_experiments)+";"

    plotting([data_msg,data_theorymsg], msg_graph(data_msg), graph_path+settings+"msg")
    plotting([data_error,data_simerror], error_graph(data_error),graph_path+settings+ "err")
    plotting([data_error], error_graphwo(data_error),graph_path+settings+"errwo")
    plotting([data_theoryerror], error_graphth(data_theoryerror),graph_path+settings+"errth")
    plotting([data_time,data_theory_time], time_graph(data_time),graph_path+settings+"time")


def main(params):
    #Get the configparser object
    config_object = ConfigParser()
    config_object.read("conf.ini")

    global base_address,exe_address,string_set,remove,alpha,graph_path,curr_graph_num,number_of_encoding_iteration,increments,number_of_experiments,number_of_repeats

    base_address = str(config_object['DEFAULT']['base_address'])
    exe_address = base_address + "bin/main"
    string_set = string.ascii_uppercase	+ string.ascii_lowercase + string.ascii_letters	+ string.digits
    remove = params['remove']
    alpha = params['alpha']
    graph_path = str(config_object['DEFAULT']['graph_path'])
    curr_graph_num = str(config_object['DEFAULT']['graph_number'])
    number_of_encoding_iteration = params['number_encoding']
    increments = params['number_increments']
    number_of_experiments = params['number_expriments']
    number_of_repeats = params['number_of_repeats']

    plots()

    config_object['DEFAULT']['graph_number']= str( int(config_object['DEFAULT']['graph_number']) + 1 )

    with open('conf.ini', 'w') as configfile:    # save
        config_object.write(configfile)