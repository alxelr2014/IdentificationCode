import matplotlib.pyplot as plt
import math
import numpy as np


def plotting(data, graph,path):
    fig, ax = plt.subplots()
    ax.spines['right'].set_visible(False)
    ax.spines['top'].set_visible(False)
    for _list in data:
        plt.plot(_list["x"],_list["y"],_list["color"], label = _list["label"])
    if "y_scale" in graph:
        ax.set_yscale(graph["y_scale"])
    if "x_label" in graph:
        plt.xlabel(graph["x_label"])
    if "y_label" in graph:
        plt.ylabel(graph["y_label"])

    ax.tick_params(axis = 'both', which = 'major', labelsize = 6)
    ax.tick_params(axis = 'both', which = 'minor', labelsize = 0)

    ax.tick_params(which = 'both', direction = 'out')    
    if "x_major_ticks" in graph:
        ax.set_xticks(graph["x_major_ticks"])
    if "x_minor_ticks" in graph:
        ax.set_xticks(graph["x_minor_ticks"], minor = True)
    if "y_major_ticks" in graph:
        ax.set_yticks(graph["y_major_ticks"])
    if "y_minor_ticks" in graph:
        ax.set_yticks(graph["y_minor_ticks"], minor = True)
    if "legend_loc" in graph:
        plt.legend(loc=graph["legend_loc"])
    ax.grid(which = 'minor', alpha = 0.3)
    ax.grid(which = 'major', alpha = 0.7)
    plt.savefig(path + ".png", bbox_inches='tight')


    
def get_sigdig(n):
    if n== 0: 
        return 1
    sig_power =  math.floor(math.log10(n))
    multiplier = 10 ** sig_power
    return round(n / multiplier) * multiplier

def msg_graph(data):
    graph_dict = {}
    graph_dict["x_label"] =  "Block Length"
    graph_dict["y_label"] = "LogLog2 of the Number of Messages"
    graph_dict["legend_loc"] = 'upper left'

    x_sig = get_sigdig(np.max(data["x"]))
    graph_dict["x_major_ticks"] = [x_sig//10 * z for z in range(11)]
    graph_dict["x_minor_ticks"] = [x_sig//50 * z for z in range(51)]

    y_sig = get_sigdig(np.max(data["y"]))
    graph_dict["y_major_ticks"] =  [y_sig//10 * z for z in range(11)]
    graph_dict["y_minor_ticks"] =  [y_sig//50 * z for z in range(51)]
    return graph_dict

def error_graph(data):
    graph_dict = {}
    graph_dict["x_label"] =  "Block Length"
    graph_dict["y_label"] = "Second Kind Error"
    graph_dict["legend_loc"] = 'upper left'
    x_sig = get_sigdig(np.max(data["x"]))
    graph_dict["x_major_ticks"] = [x_sig//10 * z for z in range(11)]
    graph_dict["x_minor_ticks"] = [x_sig//50 * z for z in range(51)]

    y_sig = get_sigdig(np.max(data["y"]))
    graph_dict["y_major_ticks"] =  [y_sig/10 * z for z in range(11)]
    graph_dict["y_minor_ticks"] =  [y_sig/50 * z for z in range(51)]
    return graph_dict


def time_graph(data):
    graph_dict = {}
    graph_dict["x_label"] =  "Block Length"
    graph_dict["y_label"] = "Average Simulation Time(µs)"
    graph_dict["legend_loc"] = 'upper left'
    x_sig = get_sigdig(np.max(data["x"]))
    graph_dict["x_major_ticks"] = [x_sig//10 * z for z in range(11)]
    graph_dict["x_minor_ticks"] = [x_sig//50 * z for z in range(51)]

    y_sig = get_sigdig(np.max(data["y"]))
    graph_dict["y_major_ticks"] =  [y_sig//10 * z for z in range(11)]
    graph_dict["y_minor_ticks"] =  [y_sig//50 * z for z in range(51)]
    return graph_dict

