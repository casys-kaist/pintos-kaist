# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(lazy-anon) begin
(lazy-anon) initial pages status
(lazy-anon) check if page is not loaded
(lazy-anon) check if page is not loaded
(lazy-anon) check if page is not loaded
(lazy-anon) load pages
(lazy-anon) load page [0]
(lazy-anon) check if page is loaded
(lazy-anon) check memory content
(lazy-anon) check if page is not loaded
(lazy-anon) check if page is not loaded
(lazy-anon) load page [1]
(lazy-anon) check if page is loaded
(lazy-anon) check memory content
(lazy-anon) check if page is loaded
(lazy-anon) check memory content
(lazy-anon) check if page is not loaded
(lazy-anon) load page [2]
(lazy-anon) check if page is loaded
(lazy-anon) check memory content
(lazy-anon) check if page is loaded
(lazy-anon) check memory content
(lazy-anon) check if page is loaded
(lazy-anon) check memory content
(lazy-anon) end
EOF
pass;
