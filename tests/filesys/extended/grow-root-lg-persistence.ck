# -*- perl -*-
use strict;
use warnings;
use tests::tests;
use tests::random;
my ($fs);
$fs->{"file$_"} = [random_bytes (512)] foreach 0...49;
check_archive ($fs);
pass;
