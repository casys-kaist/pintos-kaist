# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(page-merge-mm) begin
(page-merge-mm) init
(page-merge-mm) sort chunk 0
(page-merge-mm) sort chunk 1
(page-merge-mm) sort chunk 2
(page-merge-mm) sort chunk 3
(page-merge-mm) sort chunk 4
(page-merge-mm) sort chunk 5
(page-merge-mm) sort chunk 6
(page-merge-mm) sort chunk 7
(page-merge-mm) wait for child 0
(page-merge-mm) wait for child 1
(page-merge-mm) wait for child 2
(page-merge-mm) wait for child 3
(page-merge-mm) wait for child 4
(page-merge-mm) wait for child 5
(page-merge-mm) wait for child 6
(page-merge-mm) wait for child 7
(page-merge-mm) merge
(page-merge-mm) verify
(page-merge-mm) success, buf_idx=1,048,576
(page-merge-mm) end
EOF
pass;
