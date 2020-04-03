# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF', <<'EOF']);
(read-stdout) begin
(read-stdout) end
read-stdout: exit(0)
EOF
(read-stdout) begin
read-stdout: exit(-1)
EOF
pass;
