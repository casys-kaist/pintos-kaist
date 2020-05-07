# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(mmap-twice) begin
(mmap-twice) open "sample.txt" #0
(mmap-twice) mmap "sample.txt" #0 at 0x10000000
(mmap-twice) open "sample.txt" #1
(mmap-twice) mmap "sample.txt" #1 at 0x20000000
(mmap-twice) compare mmap'd file 0 against data
(mmap-twice) compare mmap'd file 1 against data
(mmap-twice) end
EOF
pass;
