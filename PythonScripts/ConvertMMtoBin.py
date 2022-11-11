import scipy.io
import scipy.sparse
import numpy as np
import sys

if __name__ == "__main__":
    A = scipy.io.mmread(sys.argv[1])
    
    row = A.row.astype(np.uint32)
    col = A.col.astype(np.uint32)
    
    store = np.column_stack((row, col))
    bytes = store.tobytes('C')
    
    newFile = open(sys.argv[2], "wb")
    newFile.write(bytes)