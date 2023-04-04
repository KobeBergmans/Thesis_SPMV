import sys
import numpy as np
import matplotlib.pyplot as plt

def plot_results(algorithms, data_list, threads):
    
    for i in range(len(algorithms)):
        plt.plot(threads, data_list[i], '*-')
            
    plt.xlabel("Threads")
    plt.ylabel("Speedup")
    plt.legend(algorithms)
    plt.show()


# Arguments:
#    1) File name of test output
#    2) 0 to plot the median, 1 to plot the minimum
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
    for i in range(2, len(algorithms)):
        med_speedup.append([seq_med / med for med in med_list[i]])
        min_speedup.append([seq_min / min for min in min_list[i]])
    
        
    # Plot results (plot median if second argument is 0, minimum if it is 1, variance otherwise)
    if int(sys.argv[2]) == 0:
        plot_results(algorithms[2:], med_speedup, threads)
    elif int(sys.argv[2]) == 1:
        plot_results(algorithms[2:], min_speedup, threads)