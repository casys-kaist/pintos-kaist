use strict;
use warnings;
use tests::Algorithm::Diff;
use File::Temp 'tempfile';
use Fcntl qw(SEEK_SET SEEK_CUR);

sub fail;
sub pass;

die if @ARGV != 2;
our ($test, $src_dir) = @ARGV;

my ($msg_file) = tempfile ();
select ($msg_file);

our (@prereq_tests) = ();
if ($test =~ /^(.*)-persistence$/) {
    push (@prereq_tests, $1);
}
for my $prereq_test (@prereq_tests) {
    my (@result) = read_text_file ("$prereq_test.result");
    fail "Prerequisite test $prereq_test failed.\n" if $result[0] ne 'PASS';
}


# Generic testing.

sub check_expected {
    my ($expected) = pop @_;
    my (@options) = @_;
    my (@output) = read_text_file ("$test.output");
    common_checks ("run", @output);
    compare_output ("run", @options, \@output, $expected);
}

sub common_checks {
    my ($run, @output) = @_;

    fail "\u$run produced no output at all\n" if @output == 0;

    check_for_panic ($run, @output);
    check_for_keyword ($run, "FAIL", @output);
    check_for_triple_fault ($run, @output);
    check_for_keyword ($run, "TIMEOUT", @output);

    fail "\u$run didn't start up properly: no \"Pintos booting\" message\n"
      if !grep (/Pintos booting with/, @output);
    fail "\u$run didn't start up properly: no \"Boot complete\" message\n"
      if !grep (/Boot complete/, @output);
    fail "\u$run didn't shut down properly: no \"Timer: # ticks\" message\n"
      if !grep (/Timer: \d+ ticks/, @output);
    fail "\u$run didn't shut down properly: no \"Powering off\" message\n"
      if !grep (/Powering off/, @output);
}

sub check_for_panic {
    my ($run, @output) = @_;

    my ($panic) = grep (/PANIC/, @output);
    return unless defined $panic;

    print "Kernel panic in $run: ", substr ($panic, index ($panic, "PANIC")),
      "\n";

    my (@stack_line) = grep (/Call stack:/, @output);
    if (@stack_line != 0) {
	my ($addrs) = $stack_line[0] =~ /Call stack:((?: 0x[0-9a-f]+)+)/;

	# Get and print the backtrace.
	my ($trace) = scalar (`backtrace $addrs`);
	print "Call stack:$addrs\n";
	print "Translation of call stack:\n";
	print $trace;

    }

    if ($panic =~ /sec_no \< d-\>capacity/) {
	print <<EOF;
\nThis assertion commonly fails when accessing a file via an inode that
has been closed and freed.  Freeing an inode clears all its sector
indexes to 0xcccccccc, which is not a valid sector number for disks
smaller than about 1.6 TB.
EOF
    }

    fail;
}

sub check_for_keyword {
    my ($run, $keyword, @output) = @_;
    
    my ($kw_line) = grep (/$keyword/, @output);
    return unless defined $kw_line;

    # Most output lines are prefixed by (test-name).  Eliminate this
    # from our message for brevity.
    $kw_line =~ s/^\([^\)]+\)\s+//;
    print "$run: $kw_line\n";

    fail;
}

sub check_for_triple_fault {
    my ($run, @output) = @_;

    my ($reboots) = grep (/Pintos booting/, @output) - 1;
    return unless $reboots > 0;

    print <<EOF;
\u$run spontaneously rebooted $reboots times.
This is most often caused by unhandled page faults.
Read the Triple Faults section in the Debugging chapter
of the Pintos manual for more information.
EOF

    fail;
}

# Get @output without header or trailer.
sub get_core_output {
    my ($run, @output) = @_;
    my ($p);

    my ($process);
    my ($start);
    for my $i (0...$#_) {
	$start = $i + 1, last
	  if ($process) = $output[$i] =~ /^Executing '(\S+).*':$/;
    }

    my ($end);
    for my $i ($start...$#output) {
	$end = $i - 1, last if $output[$i] =~ /^Execution of '.*' complete.$/;
    }

    fail "\u$run didn't start a thread or process\n" if !defined $start;
    fail "\u$run started '$process' but it never finished\n" if !defined $end;

    return @output[$start...$end];
}

sub compare_output {
    my ($run) = shift @_;
    my ($expected) = pop @_;
    my ($output) = pop @_;
    my (%options) = @_;

    my (@output) = get_core_output ($run, @$output);
    fail "\u$run didn't produce any output" if !@output;

    my $ignore_exit_codes = exists $options{IGNORE_EXIT_CODES};
    if ($ignore_exit_codes) {
	delete $options{IGNORE_EXIT_CODES};
	@output = grep (!/^[a-zA-Z0-9-_]+: exit\(\-?\d+\)$/, @output);
    }
    my $ignore_user_faults = exists $options{IGNORE_USER_FAULTS};
    if ($ignore_user_faults) {
	delete $options{IGNORE_USER_FAULTS};
	@output = grep (!/^Page fault at.*in user context\.$/
			&& !/: dying due to interrupt 0x0e \(.*\).$/
			&& !/^Interrupt 0x0e \(.*\) at eip=/
			&& !/^ cr2=.* error=.*/
			&& !/^ eax=.* ebx=.* ecx=.* edx=.*/
			&& !/^ esi=.* edi=.* esp=.* ebp=.*/
			&& !/^ cs=.* ds=.* es=.* ss=.*/, @output);
    }
    die "unknown option " . (keys (%options))[0] . "\n" if %options;

    my ($msg);

    # Compare actual output against each allowed output.
    if (ref ($expected) eq 'ARRAY') {
	my ($i) = 0;
	$expected = {map ((++$i => $_), @$expected)};
    }
    foreach my $key (keys %$expected) {
	my (@expected) = split ("\n", $expected->{$key});

	$msg .= "Acceptable output:\n";
	$msg .= join ('', map ("  $_\n", @expected));

	# Check whether actual and expected match.
	# If it's a perfect match, we're done.
	if ($#output == $#expected) {
	    my ($eq) = 1;
	    for (my ($i) = 0; $i <= $#expected; $i++) {
		$eq = 0 if $output[$i] ne $expected[$i];
	    }
	    return $key if $eq;
	}

	# They differ.  Output a diff.
	my (@diff) = "";
	my ($d) = Algorithm::Diff->new (\@expected, \@output);
	while ($d->Next ()) {
	    my ($ef, $el, $af, $al) = $d->Get (qw (min1 max1 min2 max2));
	    if ($d->Same ()) {
		push (@diff, map ("  $_\n", $d->Items (1)));
	    } else {
		push (@diff, map ("- $_\n", $d->Items (1))) if $d->Items (1);
		push (@diff, map ("+ $_\n", $d->Items (2))) if $d->Items (2);
	    }
	}

	$msg .= "Differences in `diff -u' format:\n";
	$msg .= join ('', @diff);
    }

    # Failed to match.  Report failure.
    $msg .= "\n(Process exit codes are excluded for matching purposes.)\n"
      if $ignore_exit_codes;
    $msg .= "\n(User fault messages are excluded for matching purposes.)\n"
      if $ignore_user_faults;
    fail "Test output failed to match any acceptable form.\n\n$msg";
}

# File system extraction.

# check_archive (\%CONTENTS)
#
# Checks that the extracted file system's contents match \%CONTENTS.
# Each key in the hash is a file name.  Each value may be:
#
#	- $FILE: Name of a host file containing the expected contents.
#
#	- [$FILE, $OFFSET, $LENGTH]: An excerpt of host file $FILE
#	  comprising the $LENGTH bytes starting at $OFFSET.
#
#	- [$CONTENTS]: The literal expected file contents, as a string.
#
#       - {SUBDIR}: A subdirectory, in the same form described here,
#         recursively.
sub check_archive {
    my ($expected_hier) = @_;

    my (@output) = read_text_file ("$test.output");
    common_checks ("file system extraction run", @output);

    @output = get_core_output ("file system extraction run", @output);
    @output = grep (!/^[a-zA-Z0-9-_]+: exit\(\d+\)$/, @output);
    fail join ("\n", "Error extracting file system:", @output) if @output;

    my ($test_base_name) = $test;
    $test_base_name =~ s%.*/%%;
    $test_base_name =~ s%-persistence$%%;
    $expected_hier->{$test_base_name} = $prereq_tests[0];
    $expected_hier->{'tar'} = 'tests/filesys/extended/tar';

    my (%expected) = normalize_fs (flatten_hierarchy ($expected_hier, ""));
    my (%actual) = read_tar ("$prereq_tests[0].tar");

    my ($errors) = 0;
    foreach my $name (sort keys %expected) {
	if (exists $actual{$name}) {
	    if (is_dir ($actual{$name}) && !is_dir ($expected{$name})) {
		print "$name is a directory but should be an ordinary file.\n";
		$errors++;
	    } elsif (!is_dir ($actual{$name}) && is_dir ($expected{$name})) {
		print "$name is an ordinary file but should be a directory.\n";
		$errors++;
	    }
	} else {
	    print "$name is missing from the file system.\n";
	    $errors++;
	}
    }
    foreach my $name (sort keys %actual) {
	if (!exists $expected{$name}) {
	    if ($name =~ /^[[:print:]]+$/) {
		print "$name exists in the file system but it should not.\n";
	    } else {
		my ($esc_name) = $name;
		$esc_name =~ s/[^[:print:]]/./g;
		print <<EOF;
$esc_name exists in the file system but should not.  (The name
of this file contains unusual characters that were printed as `.'.)
EOF
	    }
	    $errors++;
 	}
    }
    if ($errors) {
	print "\nActual contents of file system:\n";
	print_fs (%actual);
	print "\nExpected contents of file system:\n";
	print_fs (%expected);
    } else {
	foreach my $name (sort keys %expected) {
	    if (!is_dir ($expected{$name})) {
		my ($exp_file, $exp_length) = open_file ($expected{$name});
		my ($act_file, $act_length) = open_file ($actual{$name});
		$errors += !compare_files ($exp_file, $exp_length,
					   $act_file, $act_length, $name,
					   !$errors);
		close ($exp_file);
		close ($act_file);
	    }
	}
    }
    fail "Extracted file system contents are not correct.\n" if $errors;
}

# open_file ([$FILE, $OFFSET, $LENGTH])
# open_file ([$CONTENTS])
#
# Opens a file for the contents passed in, which must be in one of
# the two above forms that correspond to check_archive() arguments.
#
# Returns ($HANDLE, $LENGTH), where $HANDLE is the file's handle and
# $LENGTH is the number of bytes in the file's content.
sub open_file {
    my ($value) = @_;
    die if ref ($value) ne 'ARRAY';

    my ($file) = tempfile ();
    my ($length);
    if (@$value == 1) {
	$length = length ($value->[0]);
	$file = tempfile ();
	syswrite ($file, $value->[0]) == $length
	  or die "writing temporary file: $!\n";
	sysseek ($file, 0, SEEK_SET);
    } elsif (@$value == 3) {
	$length = $value->[2];
	open ($file, '<', $value->[0]) or die "$value->[0]: open: $!\n";
	die "$value->[0]: file is smaller than expected\n"
	  if -s $file < $value->[1] + $length;
	sysseek ($file, $value->[1], SEEK_SET);
    } else {
	die;
    }
    return ($file, $length);
}

# compare_files ($A, $A_SIZE, $B, $B_SIZE, $NAME, $VERBOSE)
#
# Compares $A_SIZE bytes in $A to $B_SIZE bytes in $B.
# ($A and $B are handles.)
# If their contents differ, prints a brief message describing
# the differences, using $NAME to identify the file.
# The message contains more detail if $VERBOSE is nonzero.
# Returns 1 if the contents are identical, 0 otherwise.
sub compare_files {
    my ($a, $a_size, $b, $b_size, $name, $verbose) = @_;
    my ($ofs) = 0;
    select(STDOUT);
    for (;;) {
	my ($a_amt) = $a_size >= 1024 ? 1024 : $a_size;
	my ($b_amt) = $b_size >= 1024 ? 1024 : $b_size;
	my ($a_data, $b_data);
	if (!defined (sysread ($a, $a_data, $a_amt))
	    || !defined (sysread ($b, $b_data, $b_amt))) {
	    die "reading $name: $!\n";
	}

	my ($a_len) = length $a_data;
	my ($b_len) = length $b_data;
	last if $a_len == 0 && $b_len == 0;

	if ($a_data ne $b_data) {
	    my ($min_len) = $a_len < $b_len ? $a_len : $b_len;
	    my ($diff_ofs);
	    for ($diff_ofs = 0; $diff_ofs < $min_len; $diff_ofs++) {
		last if (substr ($a_data, $diff_ofs, 1)
			 ne substr ($b_data, $diff_ofs, 1));
	    }

	    printf "\nFile $name differs from expected "
	      . "starting at offset 0x%x.\n", $ofs + $diff_ofs;
	    if ($verbose ) {
		print "Expected contents:\n";
		hex_dump (substr ($a_data, $diff_ofs, 64), $ofs + $diff_ofs);
		print "Actual contents:\n";
		hex_dump (substr ($b_data, $diff_ofs, 64), $ofs + $diff_ofs);
	    }
	    return 0;
	}

	$ofs += $a_len;
	$a_size -= $a_len;
	$b_size -= $b_len;
    }
    return 1;
}

# hex_dump ($DATA, $OFS)
#
# Prints $DATA in hex and text formats.
# The first byte of $DATA corresponds to logical offset $OFS
# in whatever file the data comes from.
sub hex_dump {
    my ($data, $ofs) = @_;

    if ($data eq '') {
	printf "  (File ends at offset %08x.)\n", $ofs;
	return;
    }

    my ($per_line) = 16;
    while ((my $size = length ($data)) > 0) {
	my ($start) = $ofs % $per_line;
	my ($end) = $per_line;
	$end = $start + $size if $end - $start > $size;
	my ($n) = $end - $start;

	printf "0x%08x  ", int ($ofs / $per_line) * $per_line;

	# Hex version.
	print "   " x $start;
	for my $i ($start...$end - 1) {
	    printf "%02x", ord (substr ($data, $i - $start, 1));
	    print $i == $per_line / 2 - 1 ? '-' : ' ';
	}
	print "   " x ($per_line - $end);

	# Character version.
	my ($esc_data) = substr ($data, 0, $n);
	$esc_data =~ s/[^[:print:]]/./g;
	print "|", " " x $start, $esc_data, " " x ($per_line - $end), "|";

	print "\n";

	$data = substr ($data, $n);
	$ofs += $n;
    }
}

# print_fs (%FS)
#
# Prints a list of files in %FS, which must be a file system
# as flattened by flatten_hierarchy() and normalized by
# normalize_fs().
sub print_fs {
    my (%fs) = @_;
    foreach my $name (sort keys %fs) {
	my ($esc_name) = $name;
	$esc_name =~ s/[^[:print:]]/./g;
	print "$esc_name: ";
	if (!is_dir ($fs{$name})) {
	    print +file_size ($fs{$name}), "-byte file";
	} else {
	    print "directory";
	}
	print "\n";
    }
    print "(empty)\n" if !@_;
}

# normalize_fs (%FS)
#
# Takes a file system as flattened by flatten_hierarchy().
# Returns a similar file system in which values of the form $FILE
# are replaced by those of the form [$FILE, $OFFSET, $LENGTH].
sub normalize_fs {
    my (%fs) = @_;
    foreach my $name (keys %fs) {
	my ($value) = $fs{$name};
	next if is_dir ($value) || ref ($value) ne '';
	die "can't open $value\n" if !stat $value;
	$fs{$name} = [$value, 0, -s _];
    }
    return %fs;
}

# is_dir ($VALUE)
#
# Takes a value like one in the hash returned by flatten_hierarchy()
# and returns 1 if it represents a directory, 0 otherwise.
sub is_dir {
    my ($value) = @_;
    return ref ($value) eq '' && $value eq 'directory';
}

# file_size ($VALUE)
#
# Takes a value like one in the hash returned by flatten_hierarchy()
# and returns the size of the file it represents.
sub file_size {
    my ($value) = @_;
    die if is_dir ($value);
    die if ref ($value) ne 'ARRAY';
    return @$value > 1 ? $value->[2] : length ($value->[0]);
}

# flatten_hierarchy ($HIER_FS, $PREFIX)
#
# Takes a file system in the format expected by check_archive() and
# returns a "flattened" version in which file names include all parent
# directory names and the value of directories is just "directory".
sub flatten_hierarchy {
    my (%hier_fs) = %{$_[0]};
    my ($prefix) = $_[1];
    my (%flat_fs);
    for my $name (keys %hier_fs) {
	my ($value) = $hier_fs{$name};
	if (ref $value eq 'HASH') {
	    %flat_fs = (%flat_fs, flatten_hierarchy ($value, "$prefix$name/"));
	    $flat_fs{"$prefix$name"} = 'directory';
	} else {
	    $flat_fs{"$prefix$name"} = $value;
	}
    }
    return %flat_fs;
}

# read_tar ($ARCHIVE)
#
# Reads the ustar-format tar file in $ARCHIVE
# and returns a flattened file system for it.
sub read_tar {
    my ($archive) = @_;
    my (%content);
    open (ARCHIVE, '<', $archive) or fail "$archive: open: $!\n";
    for (;;) {
	my ($header);
	if ((my $retval = sysread (ARCHIVE, $header, 512)) != 512) {
	    fail "$archive: unexpected end of file\n" if $retval >= 0;
	    fail "$archive: read: $!\n";
	}

	last if $header eq "\0" x 512;

	# Verify magic numbers.
	if (substr ($header, 257, 6) ne "ustar\0"
	    || substr ($header, 263, 2) ne '00') {
	    fail "$archive: corrupt ustar header\n";
	}

	# Verify checksum.
	my ($chksum) = oct (unpack ("Z*", substr ($header, 148, 8, ' ' x 8)));
	my ($correct_chksum) = unpack ("%32a*", $header);
	fail "$archive: bad header checksum\n" if $chksum != $correct_chksum;

	# Get file name.
	my ($name) = unpack ("Z100", $header);
	my ($prefix) = unpack ("Z*", substr ($header, 345));
	$name = "$prefix/$name" if $prefix ne '';
	fail "$archive: contains file with empty name" if $name eq '';

	# Get type.
	my ($typeflag) = substr ($header, 156, 1);
	$typeflag = '0' if $typeflag eq "\0";
	fail "unknown file type '$typeflag'\n" if $typeflag !~ /[05]/;

	# Get size.
	my ($size) = oct (unpack ("Z*", substr ($header, 124, 12)));
	fail "bad size $size\n" if $size < 0;
	$size = 0 if $typeflag eq '5';

	# Store content.
	if (exists $content{$name}) {
	    fail "$archive: contains multiple entries for $name\n";
	}
	if ($typeflag eq '5') {
	    $content{$name} = 'directory';
	} else {
	    my ($position) = sysseek (ARCHIVE, 0, SEEK_CUR);
	    $content{$name} = [$archive, $position, $size];
	    sysseek (ARCHIVE, int (($size + 511) / 512) * 512, SEEK_CUR);
	}
    }
    close (ARCHIVE);
    return %content;
}

# Utilities.

sub fail {
    finish ("FAIL", @_);
}

sub pass {
    finish ("PASS", @_);
}

sub finish {
    my ($verdict, @messages) = @_;

    seek ($msg_file, 0, 0);
    push (@messages, <$msg_file>);
    close ($msg_file);
    chomp (@messages);

    my ($result_fn) = "$test.result";
    open (RESULT, '>', $result_fn) or die "$result_fn: create: $!\n";
    print RESULT "$verdict\n";
    print RESULT "$_\n" foreach @messages;
    close (RESULT);

    if ($verdict eq 'PASS') {
	print STDOUT "pass $test\n";
    } else {
	print STDOUT "FAIL $test\n";
    }
    print STDOUT "$_\n" foreach @messages;

    exit 0;
}

sub read_text_file {
    my ($file_name) = @_;
    open (FILE, '<', $file_name) or die "$file_name: open: $!\n";
    my (@content) = <FILE>;
    chomp (@content);
    close (FILE);
    return @content;
}

1;
