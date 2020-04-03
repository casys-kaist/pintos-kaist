# -*- perl -*-
use strict;
use warnings;
use tests::tests;
use tests::random;
check_archive ({"child-syn-rw" => "tests/filesys/extended/child-syn-rw",
		"logfile" => [random_bytes (8 * 512)]});
pass;
