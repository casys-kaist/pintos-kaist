# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(page-merge-stk) begin
(page-merge-stk) init
(page-merge-stk) sort chunk 0
(page-merge-stk) sort chunk 1
(page-merge-stk) sort chunk 2
(page-merge-stk) sort chunk 3
(page-merge-stk) sort chunk 4
(page-merge-stk) sort chunk 5
(page-merge-stk) sort chunk 6
(page-merge-stk) sort chunk 7
(page-merge-stk) wait for child 0
(page-merge-stk) wait for child 1
(page-merge-stk) wait for child 2
(page-merge-stk) wait for child 3
(page-merge-stk) wait for child 4
(page-merge-stk) wait for child 5
(page-merge-stk) wait for child 6
(page-merge-stk) wait for child 7
(page-merge-stk) merge
(page-merge-stk) verify
(page-merge-stk) success, buf_idx=1,048,576
(page-merge-stk) end
EOF
pass;
