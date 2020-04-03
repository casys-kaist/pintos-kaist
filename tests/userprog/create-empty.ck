# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF', <<'EOF']);
(create-empty) begin
(create-empty) create(""): 0
(create-empty) end
create-empty: exit(0)
EOF
(create-empty) begin
create-empty: exit(-1)
EOF
pass;
