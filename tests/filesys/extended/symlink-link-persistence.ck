# -*- perl -*-
use strict;
use warnings;
use tests::tests;
use tests::random;
my ($file) = random_bytes (72943);
check_archive ({
    "file" => [$file],
    "link_a" => [$file],
    "link_b" => [$file],
    "link_c" => [$file],
});
pass;
