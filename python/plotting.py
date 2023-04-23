import matplotlib.pyplot as plt
import math
import numpy as np



plt.rc('axes', labelsize=12)    # fontsize of the x and y labels
plt.rc('legend', fontsize=12)    # legend fontsize

def get_good_point(data):
    size_list = len(data["x"])
    num_points = 10
    step = size_list//num_points
    start = size_list % step
    point_list = {"x": data["x"][start::step],"y": data["y"][start::step], "label": []}
    for _i in range(num_points):
        point_list["label"].append("( " + str(point_list["x"][_i]) + ", " + str(point_list["y"][_i]) + " )")
    return point_list

def plotting(data, graph,path):
    fig, ax = plt.subplots()
    ax.spines['right'].set_visible(False)
    ax.spines['top'].set_visible(False)
    for _list in data:
        plt.plot(_list["x"],_list["y"],_list["color"], label = _list["label"])
        if "color_p" in _list:
            point_list = get_good_point(_list)
            plt.plot(point_list["x"], point_list["y"], _list["color_p"])
            for _i in range(len(point_list["x"])):
                ax.annotate(point_list["label"][_i], xy= (point_list["x"][_i], point_list["y"][_i]), horizontalalignment="left",
                verticalalignment="top")
    if "y_scale" in graph:
        ax.set_yscale(graph["y_scale"])
    if "x_label" in graph:
        plt.xlabel(graph["x_label"])
    if "y_label" in graph:
        plt.ylabel(graph["y_label"])

    ax.tick_params(axis = 'both', which = 'major', labelsize = 10)
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
    graph_dict["x_label"] =  "LgLg of the Number of Messages"
    graph_dict["y_label"] = "Block Length"
    graph_dict["legend_loc"] = 'upper left'

    x_max = np.max(data["x"])
    x_sig = get_sigdig(x_max)
    x_sig1 = x_sig//10
    x_parts = x_max // x_sig1
    x_subdiv = 5
    graph_dict["x_major_ticks"] = [x_sig1 * z for z in range(x_parts + 1)]
    graph_dict["x_minor_ticks"] = [x_sig1//x_subdiv * z for z in range(x_subdiv*x_parts + 1)]

    y_max = np.max(data["y"])
    y_sig = get_sigdig(y_max)
    y_sig1 = y_sig//10
    y_parts = y_max // y_sig1
    y_subdiv = 5
    graph_dict["y_major_ticks"] =  [y_sig1 * z for z in range(y_parts + 1)]
    graph_dict["y_minor_ticks"] =  [y_sig1//y_subdiv * z for z in range(y_subdiv*y_parts + 1)]

    return graph_dict

def error_graph(data):
    graph_dict = {}
    graph_dict["x_label"] = "LgLg of the Number of Messages"
    graph_dict["y_label"] = "Second Kind Error"
    graph_dict["legend_loc"] = 'upper left'

    x_max = np.max(data["x"])
    x_sig = get_sigdig(x_max)
    x_sig1 = x_sig//10
    x_parts = x_max // x_sig1
    x_subdiv = 5
    graph_dict["x_major_ticks"] = [x_sig1 * z for z in range(x_parts + 1)]
    graph_dict["x_minor_ticks"] = [x_sig1//x_subdiv * z for z in range(x_subdiv*x_parts + 1)]

    y_sig = get_sigdig(1)
    graph_dict["y_major_ticks"] =  [y_sig/15 * z for z in range(16)]
    graph_dict["y_minor_ticks"] =  [y_sig/75 * z for z in range(76)]
    return graph_dict

def error_graphwo(data):
    graph_dict = {}
    graph_dict["x_label"] =  "LgLg of the Number of Messages"
    graph_dict["y_label"] = "Second Kind Error"
    graph_dict["legend_loc"] = 'upper left'

    x_max = np.max(data["x"])
    x_sig = get_sigdig(x_max)
    x_sig1 = x_sig//10
    x_parts = x_max // x_sig1
    x_subdiv = 5
    graph_dict["x_major_ticks"] = [x_sig1 * z for z in range(x_parts + 1)]
    graph_dict["x_minor_ticks"] = [x_sig1//x_subdiv * z for z in range(x_subdiv*x_parts + 1)]

    y_max = np.max(data["y"])
    y_sig = get_sigdig(y_max)
    y_sig1 = y_sig/10
    y_parts = round(y_max / y_sig1)
    y_subdiv = 5
    graph_dict["y_major_ticks"] = [y_sig1 * z for z in range(y_parts + 1)]
    graph_dict["y_minor_ticks"] = [y_sig1/y_subdiv * z for z in range(y_subdiv*y_parts + 1)]
    return graph_dict



def time_graph(data):
    graph_dict = {}
    graph_dict["x_label"] =  "LgLg2 of the Number of Messages"
    graph_dict["y_label"] = "Average Simulation Time(ms)"
    graph_dict["legend_loc"] = 'upper left'
    
    x_max = np.max(data["x"])
    x_sig = get_sigdig(x_max)
    x_sig1 = x_sig//10
    x_parts = x_max // x_sig1
    x_subdiv = 5
    graph_dict["x_major_ticks"] = [x_sig1 * z for z in range(x_parts + 1)]
    graph_dict["x_minor_ticks"] = [x_sig1//x_subdiv * z for z in range(x_subdiv*x_parts + 1)]

    y_sig = get_sigdig(np.max(data["y"]))
    graph_dict["y_major_ticks"] =  [y_sig//10 * z for z in range(11)]
    graph_dict["y_minor_ticks"] =  [y_sig//50 * z for z in range(51)]
    return graph_dict

