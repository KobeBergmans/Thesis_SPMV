function A = generateRandMat(size, avg_line, var_line, var_block, unbalanced)
%GENERATERANDMAT Generates a random sparse matrix
%   The matrix is created to have approximately the right properties
%   The properties are obtained by getting the amount of nonzero's from a
%   normal distribution with the right properties

size = int64(size);

lg_sqrt_size = ceil(log2(sqrt(double(size))));
block_bits = min(16, 3+lg_sqrt_size);
block_size = int64(2.^block_bits);
nb_blocks = int64(ceil(double(size) / double(block_size)));

block_compensation = 1;
if mod(size, block_size) ~= 0 
    block_compensation = double(mod(size, block_size)) / double(block_size);
end

row_cts = max(ones(size, 1), round(sqrt(var_line)*randn(size, 1) + avg_line));

if unbalanced
    row_cts = unbalance_rows(row_cts, size);
    while is_balanced(row_cts, block_size, nb_blocks)
        row_cts = max(ones(size, 1), round(sqrt(var_line)*randn(size, 1) + avg_line));
        row_cts = unbalance_rows(row_cts, size);
    end
end

nnz = sum(row_cts);

block_row_cts = cell(nb_blocks, 1);
for block_row = 1:nb_blocks
    row_start = (block_row-1)*block_size+1;
    row_end = min(size, block_row*block_size);
    block_row_cts{block_row} = row_cts(row_start:row_end);
end

avg_block = (nnz / double(size.^2)) * double(block_size.^2);

block_cts = cell(nb_blocks, 1);
for i = 1:nb_blocks
    block_cts{i} = sqrt(var_block)*randn(nb_blocks, 1) + avg_block;
end

for block_index = 1:nb_blocks
    block_cts{nb_blocks}(block_index) = block_cts{nb_blocks}(block_index) * block_compensation;
    block_cts{block_index}(end) = block_cts{block_index}(end) * block_compensation;
end

for i = 1:nb_blocks
    block_cts{i} = max(ones(nb_blocks, 1), round(block_cts{i}));
end

A_parts = cell(nb_blocks, 1);
parfor block_row = 1:nb_blocks
    fprintf('block row %i starting...\n', block_row);
    block_row_nnz = int64(sum(block_row_cts{block_row}));

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

    curr_block_cts = zeros(1, nb_blocks);
    rel_block_err = ones(1, nb_blocks);

    indices = zeros(block_row_nnz, 2);
    
    for i=1:block_row_nnz
        if mod(i, int64(10000)) == 0
            fprintf('block row %i has processed %i nnz\n', block_row, i);
        end

        % Find row and block col which needs the most nnz by checking the 
        % relative error
        [~, row_ind] = max(rel_row_err);
        [~, block_col_index] = max(rel_block_err);

        indices(i, 1) = row_ind + double((block_row-1)*block_size);
    
        % Generate a random column index in this block col
        if (block_col_index ~= nb_blocks) || (mod(size, block_size) == 0)
            indices(i,2) = block_size*(block_col_index-1) + randi(block_size);
        else 
            indices(i,2) = block_size*(block_col_index-1) + randi(mod(size, block_size));
        end
    
        curr_row_cts(row_ind) = curr_row_cts(row_ind) + 1;
        rel_row_err(row_ind) = (block_row_cts{block_row}(row_ind) - curr_row_cts(row_ind)) ./ block_row_cts{block_row}(row_ind);

        curr_block_cts(block_col_index) = curr_block_cts(block_col_index) + 1;
        rel_block_err(block_col_index) = (block_cts{block_row}(block_col_index) - curr_block_cts(block_col_index)) ./ block_cts{block_row}(block_col_index);
    end

    A_parts{block_row} = indices;
end

indices = A_parts{1};
for block_row = 2:nb_blocks
    indices = [indices; A_parts{block_row}];
end
A = sparse(indices(:,1), indices(:,2), ones(nnz, 1), size, size);

end

function balance = is_balanced(row_cts, block_size, nb_blocks)
    block_row_nnz = zeros(nb_blocks, 1);
    for row = 1:length(row_cts)
        block_row_nnz(ceil(row / double(block_size))) = block_row_nnz(ceil(row / double(block_size))) + row_cts(row);
    end
    balance = ~any(find(block_row_nnz > 2*mean(block_row_nnz)));
end

function new_row_cts = unbalance_rows(row_cts, size)
    new_row_cts = sort(row_cts);
    perm1 = randperm(size, ceil(size / 2));
    perm2 = randperm(size, ceil(size / 2));
    temp = new_row_cts(perm1);
    new_row_cts(perm1) = new_row_cts(perm2);
    new_row_cts(perm2) = temp;
end