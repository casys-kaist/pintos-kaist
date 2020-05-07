# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(page-merge-seq) begin
(page-merge-seq) init
(page-merge-seq) sort chunk 0
(page-merge-seq) child[0] exec
(page-merge-seq) child[0] wait success
(page-merge-seq) sort chunk 1
(page-merge-seq) child[1] exec
(page-merge-seq) child[1] wait success
(page-merge-seq) sort chunk 2
(page-merge-seq) child[2] exec
(page-merge-seq) child[2] wait success
(page-merge-seq) sort chunk 3
(page-merge-seq) child[3] exec
(page-merge-seq) child[3] wait success
(page-merge-seq) sort chunk 4
(page-merge-seq) child[4] exec
(page-merge-seq) child[4] wait success
(page-merge-seq) sort chunk 5
(page-merge-seq) child[5] exec
(page-merge-seq) child[5] wait success
(page-merge-seq) sort chunk 6
(page-merge-seq) child[6] exec
(page-merge-seq) child[6] wait success
(page-merge-seq) sort chunk 7
(page-merge-seq) child[7] exec
(page-merge-seq) child[7] wait success
(page-merge-seq) sort chunk 8
(page-merge-seq) child[8] exec
(page-merge-seq) child[8] wait success
(page-merge-seq) sort chunk 9
(page-merge-seq) child[9] exec
(page-merge-seq) child[9] wait success
(page-merge-seq) sort chunk 10
(page-merge-seq) child[10] exec
(page-merge-seq) child[10] wait success
(page-merge-seq) sort chunk 11
(page-merge-seq) child[11] exec
(page-merge-seq) child[11] wait success
(page-merge-seq) sort chunk 12
(page-merge-seq) child[12] exec
(page-merge-seq) child[12] wait success
(page-merge-seq) sort chunk 13
(page-merge-seq) child[13] exec
(page-merge-seq) child[13] wait success
(page-merge-seq) sort chunk 14
(page-merge-seq) child[14] exec
(page-merge-seq) child[14] wait success
(page-merge-seq) sort chunk 15
(page-merge-seq) child[15] exec
(page-merge-seq) child[15] wait success
(page-merge-seq) merge
(page-merge-seq) verify
(page-merge-seq) success, buf_idx=1,032,192
(page-merge-seq) end
EOF
pass;
