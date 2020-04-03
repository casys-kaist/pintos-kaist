# -*- perl -*-
use strict;
use warnings;
use tests::tests;
use tests::random;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(grow-root-sm) begin
(grow-root-sm) creating and checking "file0"
(grow-root-sm) creating and checking "file1"
(grow-root-sm) creating and checking "file2"
(grow-root-sm) creating and checking "file3"
(grow-root-sm) creating and checking "file4"
(grow-root-sm) creating and checking "file5"
(grow-root-sm) creating and checking "file6"
(grow-root-sm) creating and checking "file7"
(grow-root-sm) creating and checking "file8"
(grow-root-sm) creating and checking "file9"
(grow-root-sm) creating and checking "file10"
(grow-root-sm) creating and checking "file11"
(grow-root-sm) creating and checking "file12"
(grow-root-sm) creating and checking "file13"
(grow-root-sm) creating and checking "file14"
(grow-root-sm) creating and checking "file15"
(grow-root-sm) creating and checking "file16"
(grow-root-sm) creating and checking "file17"
(grow-root-sm) creating and checking "file18"
(grow-root-sm) creating and checking "file19"
(grow-root-sm) end
EOF
pass;
