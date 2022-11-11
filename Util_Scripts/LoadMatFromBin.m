function A = LoadMatFromBin(filename, size)

fileID = fopen(filename, 'r');
A = fread(fileID, 'uint32') + 1;
A = reshape(A, [2 length(A)/2]);

A = sparse(A(1,:), A(2,:), ones(1, length(A(1,:))), size, size);

end

