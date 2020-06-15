# -*- perl -*-
use strict;
use warnings;
use tests::tests;
use tests::random;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(symlink-link) begin
(symlink-link) create symlink "link_a"
(symlink-link) create symlink "link_b"
(symlink-link) create symlink "link_c"
(symlink-link) create "file"
(symlink-link) open "link_c"
(symlink-link) write "link_c"
(symlink-link) close "link_c"
(symlink-link) open "file" for verification
(symlink-link) verified contents of "file"
(symlink-link) close "file"
(symlink-link) open "link_a" for verification
(symlink-link) verified contents of "link_a"
(symlink-link) close "link_a"
(symlink-link) open "link_b" for verification
(symlink-link) verified contents of "link_b"
(symlink-link) close "link_b"
(symlink-link) open "link_c" for verification
(symlink-link) verified contents of "link_c"
(symlink-link) close "link_c"
(symlink-link) end
EOF
pass;
