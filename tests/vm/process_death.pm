# -*- perl -*-
use strict;
use warnings;
use tests::tests;

sub check_process_death {
    my ($proc_name) = @_;
    our ($test);
    my (@output) = read_text_file ("$test.output");

    common_checks ("run", @output);
    @output = get_core_output ("run", @output);
    fail "First line of output is not `($proc_name) begin' message.\n"
      if $output[0] ne "($proc_name) begin";
    fail "Output missing '$proc_name: exit(-1)' message.\n"
      if !grep ("$proc_name: exit(-1)" eq $_, @output);
    fail "Output contains '($proc_name) end' message.\n"
      if grep (/\($proc_name\) end/, @output);
    pass;
}

1;
