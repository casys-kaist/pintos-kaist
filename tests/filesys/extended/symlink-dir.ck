# -*- perl -*-
use strict;
use warnings;
use tests::tests;
use tests::random;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(symlink-dir) begin
(symlink-dir) mkdir "/a"
(symlink-dir) mkdir "a/b"
(symlink-dir) create symlink "a/link_b"
(symlink-dir) create "a/link_b/file"
(symlink-dir) open "file"
(symlink-dir) write "file"
(symlink-dir) close "file"
(symlink-dir) open "a/b/file" for verification
(symlink-dir) verified contents of "a/b/file"
(symlink-dir) close "a/b/file"
(symlink-dir) end
EOF
pass;
