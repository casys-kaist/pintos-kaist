# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF', <<'EOF']);
(open-null) begin
(open-null) end
open-null: exit(0)
EOF
(open-null) begin
open-null: exit(-1)
EOF
pass;
