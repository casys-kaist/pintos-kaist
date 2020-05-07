# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(page-merge-par) begin
(page-merge-par) init
(page-merge-par) sort chunk 0
(page-merge-par) sort chunk 1
(page-merge-par) sort chunk 2
(page-merge-par) sort chunk 3
(page-merge-par) sort chunk 4
(page-merge-par) sort chunk 5
(page-merge-par) sort chunk 6
(page-merge-par) sort chunk 7
(page-merge-par) wait for child 0
(page-merge-par) wait for child 1
(page-merge-par) wait for child 2
(page-merge-par) wait for child 3
(page-merge-par) wait for child 4
(page-merge-par) wait for child 5
(page-merge-par) wait for child 6
(page-merge-par) wait for child 7
(page-merge-par) merge
(page-merge-par) verify
(page-merge-par) success, buf_idx=1,048,576
(page-merge-par) end
EOF
pass;
