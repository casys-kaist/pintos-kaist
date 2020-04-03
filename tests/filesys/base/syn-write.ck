# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(syn-write) begin
(syn-write) create "stuff"
(syn-write) exec child 1 of 10: "child-syn-wrt 0"
(syn-write) exec child 2 of 10: "child-syn-wrt 1"
(syn-write) exec child 3 of 10: "child-syn-wrt 2"
(syn-write) exec child 4 of 10: "child-syn-wrt 3"
(syn-write) exec child 5 of 10: "child-syn-wrt 4"
(syn-write) exec child 6 of 10: "child-syn-wrt 5"
(syn-write) exec child 7 of 10: "child-syn-wrt 6"
(syn-write) exec child 8 of 10: "child-syn-wrt 7"
(syn-write) exec child 9 of 10: "child-syn-wrt 8"
(syn-write) exec child 10 of 10: "child-syn-wrt 9"
(syn-write) wait for child 1 of 10 returned 0 (expected 0)
(syn-write) wait for child 2 of 10 returned 1 (expected 1)
(syn-write) wait for child 3 of 10 returned 2 (expected 2)
(syn-write) wait for child 4 of 10 returned 3 (expected 3)
(syn-write) wait for child 5 of 10 returned 4 (expected 4)
(syn-write) wait for child 6 of 10 returned 5 (expected 5)
(syn-write) wait for child 7 of 10 returned 6 (expected 6)
(syn-write) wait for child 8 of 10 returned 7 (expected 7)
(syn-write) wait for child 9 of 10 returned 8 (expected 8)
(syn-write) wait for child 10 of 10 returned 9 (expected 9)
(syn-write) open "stuff"
(syn-write) read "stuff"
(syn-write) end
EOF
pass;
