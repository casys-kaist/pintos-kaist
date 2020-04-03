# -*- perl -*-
use strict;
use warnings;
use tests::tests;
my ($cwd_removable) = read_text_file ("tests/filesys/extended/can-rmdir-cwd");
$cwd_removable eq 'YES' || $cwd_removable eq 'NO' or die;
check_archive ($cwd_removable eq 'YES' ? {} : {"a" => {}});
pass;
