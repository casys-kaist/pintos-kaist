# -*- perl -*-
use strict;
use warnings;
use tests::tests;
my ($tree);
for my $a (0...3) {
    for my $b (0...2) {
	for my $c (0...2) {
	    for my $d (0...3) {
		$tree->{$a}{$b}{$c}{$d} = [''];
	    }
	}
    }
}
check_archive ($tree);
pass;
