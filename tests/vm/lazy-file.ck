# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(lazy-file) begin
(lazy-file) open "small.txt"
(lazy-file) sizeof small: 10017
(lazy-file) page aligned size of small: 12288
(lazy-file) mmap "small.txt"
(lazy-file) initial pages status
(lazy-file) check if page is not loaded
(lazy-file) check if page is not loaded
(lazy-file) check if page is not loaded
(lazy-file) load pages (3)
(lazy-file) load page [0]
(lazy-file) check if page is loaded
(lazy-file) check if page is not loaded
(lazy-file) check if page is not loaded
(lazy-file) load page [1]
(lazy-file) check if page is loaded
(lazy-file) check if page is loaded
(lazy-file) check if page is not loaded
(lazy-file) load page [2]
(lazy-file) check if page is loaded
(lazy-file) check if page is loaded
(lazy-file) check if page is loaded
(lazy-file) end
EOF
pass;
