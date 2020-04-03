# -*- perl -*-
use strict;
use warnings;
use tests::tests;
use tests::random;
my ($a) = random_bytes (8143);
my ($b) = random_bytes (8143);
check_archive ({"a" => [$a], "b" => [$b]});
pass;
