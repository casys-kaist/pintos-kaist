use strict;
use warnings;

use tests::arc4;

my (@arc4);

sub random_init {
    if (@arc4 == 0) {
	my ($seed) = @_;
	$seed = 0 if !defined $seed;
	@arc4 = arc4_init (pack ("V", $seed));
    }
}

sub random_bytes {
    random_init ();
    my ($n) = @_;
    return arc4_crypt (\@arc4, "\0" x $n);
}

sub random_ulong {
    random_init ();
    return unpack ("V", random_bytes (4));
}

1;
