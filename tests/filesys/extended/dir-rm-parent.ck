# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(dir-rm-parent) begin
(dir-rm-parent) mkdir "a"
(dir-rm-parent) chdir "a"
(dir-rm-parent) mkdir "b"
(dir-rm-parent) chdir "b"
(dir-rm-parent) remove "/a" (must fail)
(dir-rm-parent) end
EOF
pass;
