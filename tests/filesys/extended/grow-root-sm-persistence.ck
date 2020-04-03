# -*- perl -*-
use strict;
use warnings;
use tests::tests;
use tests::random;
my ($fs);
$fs->{"file$_"} = [random_bytes (512)] foreach 0...19;
check_archive ($fs);
pass;
