# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(create-exists) begin
(create-exists) create quux.dat
(create-exists) create warble.dat
(create-exists) try to re-create quux.dat
(create-exists) create baffle.dat
(create-exists) try to re-create quux.dat
(create-exists) end
create-exists: exit(0)
EOF
pass;
