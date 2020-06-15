# -*- perl -*-
use strict;
use warnings;
use tests::tests;
use tests::random;
my ($file) = random_bytes (72943);
check_archive ({
    "a" => {
        "b" => {"file" => [$file]},
	    "link_b" => {"file" => [$file]}
    }
});
pass;
