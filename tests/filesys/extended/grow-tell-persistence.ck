# -*- perl -*-
use strict;
use warnings;
use tests::tests;
use tests::random;
check_archive ({"foobar" => [random_bytes (2134)]});
pass;
