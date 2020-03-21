use strict;
use warnings;

use tests::random;

sub shuffle {
    my ($in, $cnt, $sz) = @_;
    $cnt * $sz == length $in or die;
    my (@a) = 0...$cnt - 1;
    for my $i (0...$cnt - 1) {
	my ($j) = $i + random_ulong () % ($cnt - $i);
	@a[$i, $j] = @a[$j, $i];
    }
    my ($out) = "";
    $out .= substr ($in, $_ * $sz, $sz) foreach @a;
    return $out;
}

1;
