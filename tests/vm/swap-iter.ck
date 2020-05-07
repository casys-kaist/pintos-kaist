# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(swap-iter) begin
(swap-iter) write sparsely over page 0
(swap-iter) write sparsely over page 512
(swap-iter) write sparsely over page 1024
(swap-iter) write sparsely over page 1536
(swap-iter) write sparsely over page 2048
(swap-iter) write sparsely over page 2560
(swap-iter) write sparsely over page 3072
(swap-iter) write sparsely over page 3584
(swap-iter) write sparsely over page 4096
(swap-iter) write sparsely over page 4608
(swap-iter) open "large.txt"
(swap-iter) mmap "large.txt"
(swap-iter) check consistency in page 0
(swap-iter) check consistency in page 512
(swap-iter) check consistency in page 1024
(swap-iter) check consistency in page 1536
(swap-iter) check consistency in page 2048
(swap-iter) check consistency in page 2560
(swap-iter) check consistency in page 3072
(swap-iter) check consistency in page 3584
(swap-iter) check consistency in page 4096
(swap-iter) check consistency in page 4608
(swap-iter) end
EOF
pass;
