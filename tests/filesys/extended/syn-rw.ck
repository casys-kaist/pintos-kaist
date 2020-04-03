# -*- perl -*-
use strict;
use warnings;
use tests::tests;
use tests::random;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(syn-rw) begin
(syn-rw) create "logfile"
(syn-rw) open "logfile"
(syn-rw) exec child 1 of 4: "child-syn-rw 0"
(syn-rw) exec child 2 of 4: "child-syn-rw 1"
(syn-rw) exec child 3 of 4: "child-syn-rw 2"
(syn-rw) exec child 4 of 4: "child-syn-rw 3"
(syn-rw) wait for child 1 of 4 returned 0 (expected 0)
(syn-rw) wait for child 2 of 4 returned 1 (expected 1)
(syn-rw) wait for child 3 of 4 returned 2 (expected 2)
(syn-rw) wait for child 4 of 4 returned 3 (expected 3)
(syn-rw) end
EOF
pass;
