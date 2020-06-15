# -*- perl -*-
use strict;
use warnings;
use tests::tests;
use tests::random;
my ($a) = random_bytes (72943);
my ($b) = random_bytes (72943);
check_archive ({
    "a" => [$a],
    "b" => [$b],
    "link_a" => [$a],
    "link_b" => [$b],
    "link_c" => [$b]
});
pass;
