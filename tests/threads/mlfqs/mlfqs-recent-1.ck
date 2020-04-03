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
    my ($t, $recent_cpu) = /After (\d+) seconds, recent_cpu is (\d+\.\d+),/
      or next;
    $actual[$t] = $recent_cpu;
}

# Calculate expected values.
my ($expected_load_avg, $expected_recent_cpu)
  = mlfqs_expected_load ([(1) x 180], [(100) x 180]);
my (@expected) = @$expected_recent_cpu;

# Compare actual and expected values.
mlfqs_compare ("time", "%.2f", \@actual, \@expected, 2.5, [2, 178, 2],
	       "Some recent_cpu values were missing or "
	       . "differed from those expected "
	       . "by more than 2.5.");
pass;
