# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_archive ({'a' => {'b' => ["\0" x 512]}});
pass;
