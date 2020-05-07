# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(mmap-off) begin
(mmap-off) open "large.txt"
(mmap-off) try to mmap with offset 0x1000
(mmap-off) validate mmap.
(mmap-off) validated.
(mmap-off) write to mmap
(mmap-off) validate contents.
(mmap-off) open "large.txt"
(mmap-off) read "large.txt" Page 0
(mmap-off) validate page 0.
(mmap-off) validated.
(mmap-off) read "large.txt" Page 1
(mmap-off) validate page 1.
(mmap-off) validated.
(mmap-off) success
(mmap-off) end
mmap-off: exit(0)
EOF
pass;
