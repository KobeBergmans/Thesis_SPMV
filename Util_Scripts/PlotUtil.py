def get_color(algorithm):
    if algorithm == "sequential":
        return "tab:blue"
    elif algorithm == "OpenMP":
        return "tab:orange"
    elif algorithm == "TBB":
        return "tab:green"
    elif algorithm == "TBB_graphs_6":
        return "tab:red"
    elif algorithm == "Threadpool_10":
        return "tab:purple"
    elif algorithm == "CRSMerge":
        return "tab:brown"
    elif algorithm == "CSB":
        return "tab:pink"
    elif algorithm == "BlockCOH":
        return "tab:gray"
    
def get_algo_names(algorithms):
    for i in range(len(algorithms)):
        if algorithms[i] == "TBB_graphs_6":
            algorithms[i] = "TBB graph"
        elif algorithms[i] == "Threadpool_10":
            algorithms[i] = "thread_pool"
        elif algorithms[i] == "CRSMerge":
            algorithms[i] = "Merge-based"
        elif algorithms[i] == "BlockCOH":
            algorithms[i] = "Block CO-H"
            
    return algorithms