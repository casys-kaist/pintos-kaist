sub check_alarm {
    my ($iterations) = @_;
    our ($test);

    @output = read_text_file ("$test.output");
    common_checks ("run", @output);

    my (@products);
    for (my ($i) = 0; $i < $iterations; $i++) {
	for (my ($t) = 0; $t < 5; $t++) {
	    push (@products, ($i + 1) * ($t + 1) * 10);
	}
    }
    @products = sort {$a <=> $b} @products;

    local ($_);
    foreach (@output) {
	fail $_ if /out of order/i;

	my ($p) = /product=(\d+)$/;
	next if !defined $p;

	my ($q) = shift (@products);
	fail "Too many wakeups.\n" if !defined $q;
	fail "Out of order wakeups ($p vs. $q).\n" if $p != $q; # FIXME
    }
    fail scalar (@products) . " fewer wakeups than expected.\n"
      if @products != 0;
    pass;
}

1;
