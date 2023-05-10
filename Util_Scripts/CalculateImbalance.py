import sys
import numpy as np

# Arguments:
#    1) File name of sim output
if __name__ == "__main__":
    file_name = sys.argv[1]
    file = open(file_name)
    file_content = file.readlines()
    
    # Instructions
    I_data = file_content[1][38:]
    I_array = np.fromstring(I_data, dtype=np.float32, sep="|")
    I_mean = np.mean(I_array[1:])
    I_var = np.var(I_array[1:])
    
    # Cycles
    C_data = file_content[2][38:]
    C_array = np.fromstring(C_data, dtype=np.float32, sep="|")
    C_mean = np.mean(C_array[1:])
    C_var = np.var(C_array[1:])
    
    # IPC
    IPC_data = file_content[3][38:]
    IPC_array = np.fromstring(IPC_data, dtype=np.float32, sep="|")
    IPC_mean = np.mean(IPC_array[1:])
    IPC_var = np.var(IPC_array[1:])
    
    # Idle time
    real_time_data = file_content[4][38:]
    real_time = np.fromstring(real_time_data, dtype=np.float32, sep="|")[1]
    
    idle_data = file_content[5][38:]
    idle_array = np.fromstring(idle_data, dtype=np.float32, sep="|")
    idle_mean = np.mean(idle_array[1:])
    idle_var = np.var(idle_array[1:])
    
    
    # Print results
    print("Instructions mean:     ", I_mean)
    print("Instructions variance: ", I_var)
    print("")
    print("Cycles mean:           ", C_mean)
    print("Cycles variance:       ", C_var)
    print("")
    print("IPC mean:              ", IPC_mean)
    print("IPC variance:          ", IPC_var)
    print("--------------------------------------------------------------")
    print("Execution time:        ", real_time)
    print("Idle time mean:        ", idle_mean)
    print("Idle time variance:    ", idle_var)
    print("Average idle time:     ", idle_mean/real_time)