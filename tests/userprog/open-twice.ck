# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(open-twice) begin
(open-twice) open "sample.txt" once
(open-twice) open "sample.txt" again
(open-twice) end
open-twice: exit(0)
EOF
pass;
