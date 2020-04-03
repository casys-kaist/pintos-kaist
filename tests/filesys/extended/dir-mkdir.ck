# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(dir-mkdir) begin
(dir-mkdir) mkdir "a"
(dir-mkdir) create "a/b"
(dir-mkdir) chdir "a"
(dir-mkdir) open "b"
(dir-mkdir) end
EOF
pass;
