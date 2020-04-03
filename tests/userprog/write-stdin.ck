# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF', <<'EOF']);
(write-stdin) begin
(write-stdin) end
write-stdin: exit(0)
EOF
(write-stdin) begin
write-stdin: exit(-1)
EOF
pass;
