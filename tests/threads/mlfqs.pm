# -*- perl -*-
use strict;
use warnings;

sub mlfqs_expected_load {
    my ($ready, $recent_delta) = @_;
    my (@load_avg) = 0;
    my (@recent_cpu) = 0;
    my ($load_avg) = 0;
    my ($recent_cpu) = 0;
    for my $i (0...$#$ready) {
	$load_avg = (59/60) * $load_avg + (1/60) * $ready->[$i];
	push (@load_avg, $load_avg);

	if (defined $recent_delta->[$i]) {
	    my ($twice_load) = $load_avg * 2;
	    my ($load_factor) = $twice_load / ($twice_load + 1);
	    $recent_cpu = ($recent_cpu + $recent_delta->[$i]) * $load_factor;
	    push (@recent_cpu, $recent_cpu);
	}
    }
    return (\@load_avg, \@recent_cpu);
}

sub mlfqs_expected_ticks {
    my (@nice) = @_;
    my ($thread_cnt) = scalar (@nice);
    my (@recent_cpu) = (0) x $thread_cnt;
    my (@slices) = (0) x $thread_cnt;
    my (@fifo) = (0) x $thread_cnt;
    my ($next_fifo) = 1;
    my ($load_avg) = 0;
    for my $i (1...750) {
	if ($i % 25 == 0) {
	    # Update load average.
	    $load_avg = (59/60) * $load_avg + (1/60) * $thread_cnt;

	    # Update recent_cpu.
	    my ($twice_load) = $load_avg * 2;
	    my ($load_factor) = $twice_load / ($twice_load + 1);
	    $recent_cpu[$_] = $recent_cpu[$_] * $load_factor + $nice[$_]
	      foreach 0...($thread_cnt - 1);
	}

	# Update priorities.
	my (@priority);
	foreach my $j (0...($thread_cnt - 1)) {
	    my ($priority) = int ($recent_cpu[$j] / 4 + $nice[$j] * 2);
	    $priority = 0 if $priority < 0;
	    $priority = 63 if $priority > 63;
	    push (@priority, $priority);
	}

	# Choose thread to run.
	my $max = 0;
	for my $j (1...$#priority) {
	    if ($priority[$j] < $priority[$max]
		|| ($priority[$j] == $priority[$max]
		    && $fifo[$j] < $fifo[$max])) {
		$max = $j;
	    }
	}
	$fifo[$max] = $next_fifo++;

	# Run thread.
	$recent_cpu[$max] += 4;
	$slices[$max] += 4;
    }
    return @slices;
}

sub check_mlfqs_fair {
    my ($nice, $maxdiff) = @_;
    our ($test);
    my (@output) = read_text_file ("$test.output");
    common_checks ("run", @output);
    @output = get_core_output ("run", @output);

    my (@actual);
    local ($_);
    foreach (@output) {
	my ($id, $count) = /Thread (\d+) received (\d+) ticks\./ or next;
        $actual[$id] = $count;
    }

    my (@expected) = mlfqs_expected_ticks (@$nice);
    mlfqs_compare ("thread", "%d",
		   \@actual, \@expected, $maxdiff, [0, $#$nice, 1],
		   "Some tick counts were missing or differed from those "
		   . "expected by more than $maxdiff.");
    pass;
}

sub mlfqs_compare {
    my ($indep_var, $format,
	$actual_ref, $expected_ref, $maxdiff, $t_range, $message) = @_;
    my ($t_min, $t_max, $t_step) = @$t_range;

    my ($ok) = 1;
    for (my ($t) = $t_min; $t <= $t_max; $t += $t_step) {
	my ($actual) = $actual_ref->[$t];
	my ($expected) = $expected_ref->[$t];
	$ok = 0, last
	  if !defined ($actual) || abs ($actual - $expected) > $maxdiff + .01;
    }
    return if $ok;

    print "$message\n";
    mlfqs_row ($indep_var, "actual", "<->", "expected", "explanation");
    mlfqs_row ("------", "--------", "---", "--------", '-' x 40);
    for (my ($t) = $t_min; $t <= $t_max; $t += $t_step) {
	my ($actual) = $actual_ref->[$t];
	my ($expected) = $expected_ref->[$t];
	my ($diff, $rationale);
	if (!defined $actual) {
	    $actual = 'undef' ;
	    $diff = '';
	    $rationale = 'Missing value.';
	} else {
	    my ($delta) = abs ($actual - $expected);
	    if ($delta > $maxdiff + .01) {
		my ($excess) = $delta - $maxdiff;
		if ($actual > $expected) {
		    $diff = '>>>';
		    $rationale = sprintf "Too big, by $format.", $excess;
		} else {
		    $diff = '<<<';
		    $rationale = sprintf "Too small, by $format.", $excess;
		}
	    } else {
		$diff = ' = ';
		$rationale = '';
	    }
	    $actual = sprintf ($format, $actual);
	}
	$expected = sprintf ($format, $expected);
	mlfqs_row ($t, $actual, $diff, $expected, $rationale);
    }
    fail;
}

sub mlfqs_row {
    printf "%6s %8s %3s %-8s %s\n", @_;
}

1;
