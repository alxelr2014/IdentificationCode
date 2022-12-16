import os
import subprocess
import string
import random
import matplotlib.pyplot as plt


# make sure to compile the executable first
base_address = "C:/Users/Emad Zinoghli/Desktop/Codes/IdentificationChannel/"
exe_address = base_address + "bin/main"
string_set = string.ascii_uppercase	+ string.ascii_lowercase + string.ascii_letters	+ string.digits
n = 0
m = 30
N = [10]
results = []
num_repeats = 18

for _i in range(num_repeats):
    file_address=  base_address + "logs/log-"+str(_i)+".txt"
    random_string = ''.join(random.choices(string_set,k=13))
    # cmd_line= exe_address + ' '+ file_address + ' ' +  str(N[-1]) + ' '+ str(n) + ' ' + str(m) + ' ' + random_string
    res_string = subprocess.check_output([exe_address, file_address, str(N[-1]), str(n), str(m), random_string],shell=True).decode()
    results.append(float(res_string))
    N.append(N[-1]* 10)
N.pop()

print(results)
fig, ax = plt.subplots()
ax.plot(N, results)
ax.set_xscale('log')
plt.show()