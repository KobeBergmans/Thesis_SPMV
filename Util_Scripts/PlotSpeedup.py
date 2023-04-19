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
        plt.plot(threads, data_list[i], '*-', color=get_color(algorithms[i]))
            
    plt.xlabel("Threads")
    plt.ylabel("Speedup")
    
    if legend:
        plt.legend(algorithms, loc="lower right")


# Arguments:
#    1) File name of test output
#    2) 0 to plot the median, 1 to plot the minimum
#    3) 1 to safe the file
#    4) 1 if the ymin must be 1
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
    
    for i in range(len(algorithms)):
        medians = []
        mins = []
        vars = []
        for res in results[i]:
            medians.append(np.median(res))
            mins.append(np.min(res))
            
        print("Algorithm: " + algorithms[i])
        print("Medians:")
        print(medians)
        print("Minima:")
        print(mins)
        
        med_list.append(medians)
        min_list.append(mins)
        
    # Calculate the speedup
    seq_med = med_list[0][0]
    seq_min = min_list[0][0]
    med_speedup = []
    min_speedup = []
    max_val = 0
    for i in range(1, len(algorithms)):
        med_speedup.append([seq_med / med for med in med_list[i]])
        min_speedup.append([seq_min / min for min in min_list[i]])
    
    plt.figure(figsize=(10,6))
        
    # Plot results (plot median if second argument is 0, minimum if it is 1, variance otherwise)
    if int(sys.argv[2]) == 0:
        plot_results(algorithms[1:], med_speedup, threads, len(sys.argv)==6)
    elif int(sys.argv[2]) == 1:
        plot_results(algorithms[1:], min_speedup, threads, len(sys.argv)==6)
        
    if int(sys.argv[4]) == 1:
        # Calculate the maximum value
        max_val = 0
        if int(sys.argv[2]) == 0:
            max_val = max(max_val, max(np.concatenate(med_speedup).flat))
        elif int(sys.argv[2]) == 1:
            max_val = max(max_val, max(np.concatenate(min_speedup).flat))
        
        plt.ylim([1, 1.1*max_val])
        
    if int(sys.argv[3]) == 1:
        plt.savefig(file_name[:-3]+'pdf', bbox_inches="tight", pad_inches=0.)
    else:
        plt.show()