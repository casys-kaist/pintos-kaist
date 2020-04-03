# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF', <<'EOF']);
(dir-open) begin
(dir-open) mkdir "xyzzy"
(dir-open) open "xyzzy"
(dir-open) write "xyzzy"
(dir-open) write "xyzzy" (must return -1, actually -1)
(dir-open) end
dir-open: exit(0)
EOF
(dir-open) begin
(dir-open) mkdir "xyzzy"
(dir-open) open "xyzzy"
(dir-open) write "xyzzy"
dir-open: exit(-1)
EOF
pass;
