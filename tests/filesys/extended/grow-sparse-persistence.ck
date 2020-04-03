# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_archive ({"testfile" => ["\0" x 76543]});
pass;
