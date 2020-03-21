# -*- perl -*-
use strict;
use warnings;
use tests::tests;

our ($test);
my (@output) = read_text_file ("$test.output");

common_checks ("run", @output);

@output = get_core_output ("run", @output);
fail "missing PASS in output"
  unless grep ($_ eq '(mlfqs-load-1) PASS', @output);

pass;
