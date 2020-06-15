# -*- perl -*-
use strict;
use warnings;
use tests::tests;
use tests::random;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(symlink-file) begin
(symlink-file) create "a"
(symlink-file) create "b"
(symlink-file) create symlink "link_a"
(symlink-file) create symlink "link_b"
(symlink-file) create symlink "link_c"
(symlink-file) open "link_a"
(symlink-file) open "link_b"
(symlink-file) open "link_c"
(symlink-file) write "link_a" and "link_b" alternately
(symlink-file) close "link_a"
(symlink-file) close "link_b"
(symlink-file) close "link_c"
(symlink-file) open "a" for verification
(symlink-file) verified contents of "a"
(symlink-file) close "a"
(symlink-file) open "b" for verification
(symlink-file) verified contents of "b"
(symlink-file) close "b"
(symlink-file) end
EOF
pass;
