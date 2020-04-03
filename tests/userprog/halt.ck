# -*- perl -*-
use strict;
use warnings;
use tests::tests;

our ($test);
my (@output) = read_text_file ("$test.output");

common_checks ("run", @output);

fail "missing 'begin' message\n"
  if !grep ($_ eq '(halt) begin', @output);
fail "found 'fail' message--halt didn't really halt\n"
  if grep ($_ eq '(halt) fail', @output);
pass;
