function A = generateRandMat(size, avg_line, var_line, var_block)
%GENERATERANDMAT Generates a random sparse matrix
%   The matrix is created to have approximately the right properties
%   The properties are obtained by getting the amount of nonzero's from a
%   normal distribution with the right properties

lg_sqrt_size = ceil(log2(sqrt(size)));
block_bits = min(16, 3+lg_sqrt_size);
block_size = 2.^block_bits;
nb_blocks = ceil(size / block_size);

row_cts = max(zeros(size, 1), round(sqrt(var_line)*randn(size, 1) + avg_line));
nnz = sum(row_cts);

block_row_cts = cell(nb_blocks, 1);
for block_row = 1:nb_blocks
    row_start = (block_row-1)*block_size+1;
    row_end = min(size, block_row*block_size);
    block_row_cts{block_row} = row_cts(row_start:row_end);
end

avg_block = nnz / nb_blocks.^2;
block_cts = max(zeros(nb_blocks, nb_blocks), round(sqrt(var_block)*randn(nb_blocks, nb_blocks) + avg_block));

A_parts = cell(nb_blocks, 1);
parfor block_row = 1:nb_blocks
    disp(['block row ', num2str(block_row), ' starting...']);
    block_row_nnz = sum(block_row_cts{block_row});
    
    if block_row ~= nb_blocks
        curr_row_cts = zeros(block_size, 1);
    else
        am_rows = mod(size, block_size);
        if am_rows == 0
            am_rows = block_size;
        end
        curr_row_cts = zeros(am_rows, 1);
    end
    curr_block_cts = zeros(1, nb_blocks);

    A_temp = spalloc(block_size, size, block_row_nnz);
    
    for i=1:block_row_nnz
        if mod(i, 10000) == 0
            disp(['block row ', num2str(block_row), ' has processed ', num2str(i), ' nnz']);
        end

        % Find row which needs the most nnz
        [~, row_ind] = max(block_row_cts{block_row} - curr_row_cts);
        
        % Find block col which needs the most nnz
        [~, block_col_index] = max(block_cts(block_row, :) - curr_block_cts);
    
        % Generate a random column index in this block col
        col_ind = min(size, block_size*(block_col_index-1) + randi(block_size));
        while A_temp(row_ind, col_ind) ~= 0
            col_ind = min(size, block_size*(block_col_index-1) + randi(block_size));
        end
        A_temp(row_ind, col_ind) = 1;
    
        curr_row_cts(row_ind) = curr_row_cts(row_ind) + 1;
        curr_block_cts(block_col_index) = curr_block_cts(block_col_index) + 1;
    end

    A_parts{block_row} = A_temp;
end

A = A_parts{1};
for block_row = 2:nb_blocks
    A = [A; A_parts{block_row}];
end

end

