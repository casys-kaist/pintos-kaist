# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(cow-simple) begin
(cow-simple) check data consistency
(cow-simple) check data consistency
(cow-simple) two phys addrs should be the same.
(cow-simple) check data change
(cow-simple) two phys addrs should not be the same.
(cow-simple) end
(cow-simple) two phys addrs should be the same.
(cow-simple) check data consistency
(cow-simple) end
EOF
pass;
