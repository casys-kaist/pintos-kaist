# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(bc-easy) begin
(bc-easy) create "data"
(bc-easy) open "data"
(bc-easy) write "data"
(bc-easy) check read_cnt
(bc-easy) check write_cnt
(bc-easy) close "data"
(bc-easy) end
EOF
pass;
