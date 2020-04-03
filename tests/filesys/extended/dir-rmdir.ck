# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(dir-rmdir) begin
(dir-rmdir) mkdir "a"
(dir-rmdir) rmdir "a"
(dir-rmdir) chdir "a" (must return false)
(dir-rmdir) end
EOF
pass;
