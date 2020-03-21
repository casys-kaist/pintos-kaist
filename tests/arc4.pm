use strict;
use warnings;

sub arc4_init {
    my ($key) = @_;
    my (@s) = 0...255;
    my ($j) = 0;
    for my $i (0...255) {
	$j = ($j + $s[$i] + ord (substr ($key, $i % length ($key), 1))) & 0xff;
	@s[$i, $j] = @s[$j, $i];
    }
    return (0, 0, @s);
}

sub arc4_crypt {
    my ($arc4, $buf) = @_;
    my ($i, $j, @s) = @$arc4;
    my ($out) = "";
    for my $c (split (//, $buf)) {
	$i = ($i + 1) & 0xff;
	$j = ($j + $s[$i]) & 0xff;
	@s[$i, $j] = @s[$j, $i];
	$out .= chr (ord ($c) ^ $s[($s[$i] + $s[$j]) & 0xff]);
    }
    @$arc4 = ($i, $j, @s);
    return $out;
}

1;
