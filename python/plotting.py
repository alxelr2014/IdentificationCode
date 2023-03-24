import matplotlib.pyplot as plt


def plotting(data, graph):
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
    plt.show()

    
