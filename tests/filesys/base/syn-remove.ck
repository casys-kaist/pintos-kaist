# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(syn-remove) begin
(syn-remove) create "deleteme"
(syn-remove) open "deleteme"
(syn-remove) remove "deleteme"
(syn-remove) write "deleteme"
(syn-remove) seek "deleteme" to 0
(syn-remove) read "deleteme"
(syn-remove) close "deleteme"
(syn-remove) end
EOF
pass;
