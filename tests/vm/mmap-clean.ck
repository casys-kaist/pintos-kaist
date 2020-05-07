# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(mmap-clean) begin
(mmap-clean) open "sample.txt"
(mmap-clean) mmap "sample.txt"
(mmap-clean) write "sample.txt"
(mmap-clean) munmap "sample.txt"
(mmap-clean) seek "sample.txt"
(mmap-clean) read "sample.txt"
(mmap-clean) file change was retained after munmap
(mmap-clean) end
EOF
pass;
