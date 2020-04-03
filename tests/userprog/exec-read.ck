# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(exec-read) begin
(exec-read) open "sample.txt"
(exec-read) read "sample.txt" first 20 bytes
(child-read) begin
(child-read) open "sample.txt"
(child-read) read "sample.txt" first 20 bytes
(child-read) read "sample.txt" remainders
(child-read) Child success
(child-read) end
child-read: exit(0)
(exec-read) Parent success
(exec-read) end
exec-read: exit(0)
EOF
pass;
