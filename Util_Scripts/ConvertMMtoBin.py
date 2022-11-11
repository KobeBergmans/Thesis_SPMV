import scipy.io
import scipy.sparse
import numpy as np
import sys

# Arguments:
# 1. Input file
# 2. Output file
# 3. If this is 1 we have a symmetric input matrix

if __name__ == "__main__":
    A = scipy.io.mmread(sys.argv[1])
    
    if int(sys.argv[3]) == 1:
        A = scipy.sparse.tril(A)
    
    row = A.row.astype(np.uint32)
    col = A.col.astype(np.uint32)
    
    store = np.column_stack((row, col))
    bytes = store.tobytes('C')
    
    newFile = open(sys.argv[2], "wb")
    newFile.write(bytes)