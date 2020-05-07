# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(swap-anon) begin
(swap-anon) write sparsely over page 0
(swap-anon) write sparsely over page 512
(swap-anon) write sparsely over page 1024
(swap-anon) write sparsely over page 1536
(swap-anon) write sparsely over page 2048
(swap-anon) write sparsely over page 2560
(swap-anon) write sparsely over page 3072
(swap-anon) write sparsely over page 3584
(swap-anon) write sparsely over page 4096
(swap-anon) write sparsely over page 4608
(swap-anon) check consistency in page 0
(swap-anon) check consistency in page 512
(swap-anon) check consistency in page 1024
(swap-anon) check consistency in page 1536
(swap-anon) check consistency in page 2048
(swap-anon) check consistency in page 2560
(swap-anon) check consistency in page 3072
(swap-anon) check consistency in page 3584
(swap-anon) check consistency in page 4096
(swap-anon) check consistency in page 4608
(swap-anon) end
EOF
pass;
