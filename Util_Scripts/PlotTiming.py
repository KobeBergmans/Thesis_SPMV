import sys
import numpy as np
import matplotlib.pyplot as plt

def get_color(algorithm):
    if algorithm == "sequential":
        return "tab:blue"
    elif algorithm == "OpenMP":
        return "tab:orange"
    elif algorithm == "TBB":
        return "tab:green"
    elif algorithm == "TBB_graphs":
        return "tab:red"
    elif algorithm == "Threadpool":
        return "tab:purple"
    elif algorithm == "CRSMerge":
        return "tab:brown"
    elif algorithm == "CSB":
        return "tab:pink"
    elif algorithm == "BlockCOH":
        return "tab:gray"

def plot_results(algorithms, data_list, threads, legend=False):
    
    for i in range(len(algorithms)):
        if algorithms[i] == "sequential":
            plt.plot([threads[0], threads[-1]], [data_list[i][0], data_list[i][0]], color=get_color(algorithms[i]))
        else:
            plt.plot(threads, data_list[i], '*-', color=get_color(algorithms[i]))
            
    plt.xlabel("Threads")
    plt.ylabel("Milliseconds")
    
    if legend:
        plt.legend(algorithms, loc="lower right")


# Arguments:
#    1) File name of test output
#    2) 0 to plot the median, 1 to plot the minimum, 2 to plot the variance
#    3) 1 to safe the file
#    4) 1 if the ymin must be 0
#    5) 1 if a legend needs to be plotted
if __name__ == "__main__":
    file_name = sys.argv[1]
    
    results = []
    algorithms = []
    alg_result = []
    
    # Read file
    with open(file_name, "r") as fileStream:
        threads = np.fromstring(fileStream.readline(), dtype=np.int8, sep=" ")
        
        
        for line in fileStream:
            if len(line) <= 1:
                break
            
            if line.startswith('Running'):
                
                if len(alg_result) > 0:
                    results.append(alg_result)
                    

                currLine = line.split(' ')
                algorithms.append(currLine[1])
                alg_result = []
            elif not line.startswith('Time') and len(line) > 1: # Check if it is a timing line
                currLine = line.strip()
                
                temp_res = np.fromstring(currLine, dtype=np.double, sep=",")
                    
                alg_result.append(temp_res)
    
    # Add last result to results file
    results.append(alg_result)

    # Calculate mean and minimum of each result
    print("Threads:")
    print(threads)
    
    med_list = []
    min_list = []
    var_list = []
    max_val = -1
    
    for i in range(len(algorithms)):
        medians = []
        mins = []
        vars = []
        for res in results[i]:
            medians.append(np.median(res))
            mins.append(np.min(res))
            vars.append(np.var(res))
            
        print("Algorithm: " + algorithms[i])
        print("Medians:")
        print(medians)
        print("Minima:")
        print(mins)
        print("Variance:")
        print(vars)
        
        if int(sys.argv[2]) == 0:
            max_val = max(max(medians), max_val)
        elif int(sys.argv[2]) == 1:
            max_val = max(max(mins), max_val)
        else:
            max_val = max(max(vars), max_val)
        
        
        
        med_list.append(medians)
        min_list.append(mins)
        var_list.append(vars)
    
    plt.figure(figsize=(10,6))
        
    # Plot results (plot median if second argument is 0, minimum if it is 1, variance otherwise)
    if int(sys.argv[2]) == 0:
        plot_results(algorithms, med_list, threads, len(sys.argv)==6)
    elif int(sys.argv[2]) == 1:
        plot_results(algorithms, min_list, threads, len(sys.argv)==6)
    else:
        plot_results(algorithms, var_list, threads, len(sys.argv)==6)
        
    if int(sys.argv[4]) == 1:
        plt.ylim([0, 1.1*max_val])

    
    if int(sys.argv[3]) == 1:
        plt.savefig(file_name[:-3]+'pdf', bbox_inches="tight", pad_inches=0.)
    else:
        plt.show()