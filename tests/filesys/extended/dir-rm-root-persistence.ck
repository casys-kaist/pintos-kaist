# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_archive ({"a" => ["\0" x 243]});
pass;
