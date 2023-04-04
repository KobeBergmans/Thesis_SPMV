function A = generateRandMat(size, avg_line, var_line, var_block)
%GENERATERANDMAT Generates a random sparse matrix
%   The matrix is created to have approximately the right properties
%   The properties are obtained by getting the amount of nonzero's from a
%   normal distribution with the right properties

lg_sqrt_size = ceil(log2(sqrt(size)));
block_bits = min(16, 3+lg_sqrt_size);
block_size = 2.^block_bits;
nb_blocks = ceil(size / block_size);

block_compensation = 1;
if mod(size, block_size) ~= 0 
    block_compensation = mod(size, block_size) / block_size;
end

row_cts = max(zeros(size, 1), round(sqrt(var_line)*randn(size, 1) + avg_line));
nnz = sum(row_cts);

block_row_cts = cell(nb_blocks, 1);
for block_row = 1:nb_blocks
    row_start = (block_row-1)*block_size+1;
    row_end = min(size, block_row*block_size);
    block_row_cts{block_row} = row_cts(row_start:row_end);
end

avg_block = (nnz / (size.^2)) * block_size.^2;

block_cts = {};
for i = 1:nb_blocks
    block_cts{i} = max(zeros(nb_blocks, 1), sqrt(var_block)*randn(nb_blocks, 1) + avg_block);
end

for block_index = 1:nb_blocks
    block_cts{nb_blocks}(block_index) = block_cts{nb_blocks}(block_index) * block_compensation;
    block_cts{block_index}(end) = block_cts{block_index}(end) * block_compensation;
end

for i = 1:nb_blocks
    block_cts{i} = round(block_cts{i});
end

A_parts = cell(nb_blocks, 1);
parfor block_row = 1:nb_blocks
    disp(['block row ', num2str(block_row), ' starting...']);
    block_row_nnz = sum(block_row_cts{block_row});

    if block_row ~= nb_blocks
        curr_row_cts = zeros(block_size, 1);
        rel_row_err = ones(block_size, 1);
    else
        am_rows = mod(size, block_size);
        if am_rows == 0
            am_rows = block_size;
        end
        curr_row_cts = zeros(am_rows, 1);
        rel_row_err = ones(am_rows, 1);
    end

    % Set rel_row_err to zero if there are no nonzeros on the row
    rel_row_err(block_row_cts{block_row} == 0) = 0;

    curr_block_cts = zeros(1, nb_blocks);
    rel_block_err = ones(1, nb_blocks);

    % Set rel_block_err to zero if there are no nonzeros in the block
    rel_block_err(block_cts{block_row} == 0) = 0;

    if (block_row ~= nb_blocks) || (mod(size, block_size) == 0)
        A_temp = spalloc(block_size, size, block_row_nnz);
    else
        A_temp = spalloc(mod(size, block_size), size, block_row_nnz);
    end
    
    for i=1:block_row_nnz
        if mod(i, 10000) == 0
            disp(['block row ', num2str(block_row), ' has processed ', num2str(i), ' nnz']);
        end

        % Find row and block col which needs the most nnz by checking the 
        % relative error
        [~, row_ind] = max(rel_row_err);
        [~, block_col_index] = max(rel_block_err);
    
        % Generate a random column index in this block col
        if (block_col_index ~= nb_blocks) || (mod(size, block_size) == 0)
            col_ind = block_size*(block_col_index-1) + randi(block_size);
        else 
            col_ind = block_size*(block_col_index-1) + randi(mod(size, block_size));
        end

        while A_temp(row_ind, col_ind) ~= 0
            if (block_col_index ~= nb_blocks) || (mod(size, block_size) == 0)
                col_ind = block_size*(block_col_index-1) + randi(block_size);
            else 
                col_ind = block_size*(block_col_index-1) + randi(mod(size, block_size));
            end
        end
        A_temp(row_ind, col_ind) = 1;
    
        curr_row_cts(row_ind) = curr_row_cts(row_ind) + 1;
        rel_row_err(row_ind) = (block_row_cts{block_row}(row_ind) - curr_row_cts(row_ind)) ./ block_row_cts{block_row}(row_ind);

        curr_block_cts(block_col_index) = curr_block_cts(block_col_index) + 1;
        rel_block_err(block_col_index) = (block_cts{block_row}(block_col_index) - curr_block_cts(block_col_index)) ./ block_cts{block_row}(block_col_index);
    end

    A_parts{block_row} = A_temp;
end

A = A_parts{1};
for block_row = 2:nb_blocks
    A = [A; A_parts{block_row}];
end

end