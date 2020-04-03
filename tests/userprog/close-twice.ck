# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF', <<'EOF']);
(close-twice) begin
(close-twice) open "sample.txt"
(close-twice) close "sample.txt"
(close-twice) close "sample.txt" again
(close-twice) end
close-twice: exit(0)
EOF
(close-twice) begin
(close-twice) open "sample.txt"
(close-twice) close "sample.txt"
(close-twice) close "sample.txt" again
close-twice: exit(-1)
EOF
pass;
