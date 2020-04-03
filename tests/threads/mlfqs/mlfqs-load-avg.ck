# -*- perl -*-
use strict;
use warnings;
use tests::tests;
use tests::threads::mlfqs;

our ($test);
my (@output) = read_text_file ("$test.output");

common_checks ("run", @output);
@output = get_core_output ("run", @output);

# Get actual values.
local ($_);
my (@actual);
foreach (@output) {
    my ($t, $load_avg) = /After (\d+) seconds, load average=(\d+\.\d+)\./
      or next;
    $actual[$t] = $load_avg;
}

# Calculate expected values.
my ($load_avg) = 0;
my ($recent) = 0;
my (@expected);
for (my ($t) = 0; $t < 180; $t++) {
    my ($ready) = $t < 60 ? $t : $t < 120 ? 120 - $t : 0;
    $load_avg = (59/60) * $load_avg + (1/60) * $ready;
    $expected[$t] = $load_avg;
}

mlfqs_compare ("time", "%.2f", \@actual, \@expected, 2.5, [2, 178, 2],
	       "Some load average values were missing or "
	       . "differed from those expected "
	       . "by more than 2.5.");
pass;
