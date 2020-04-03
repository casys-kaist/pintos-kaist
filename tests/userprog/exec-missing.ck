# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF', <<'EOF']);
(exec-missing) begin
load: no-such-file: open failed
exec-missing: exit(-1)
EOF
(exec-missing) begin
(exec-missing) exec("no-such-file"): -1
exec-missing: exit(-1)
EOF
pass;
