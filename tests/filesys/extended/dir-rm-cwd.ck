# -*- perl -*-
use strict;
use warnings;
use tests::tests;
my ($cwd_removable) = check_expected (IGNORE_EXIT_CODES => 1,
				      {NO => <<'EOF', YES => <<'EOF'});
(dir-rm-cwd) begin
(dir-rm-cwd) open "/"
(dir-rm-cwd) mkdir "a"
(dir-rm-cwd) open "/a"
(dir-rm-cwd) verify "/a" is empty
(dir-rm-cwd) "/" and "/a" must have different inumbers
(dir-rm-cwd) chdir "a"
(dir-rm-cwd) try to remove "/a"
(dir-rm-cwd) remove failed
(dir-rm-cwd) try to remove "../a" (must fail)
(dir-rm-cwd) try to remove ".././a" (must fail)
(dir-rm-cwd) try to remove "/./a" (must fail)
(dir-rm-cwd) open "/a"
(dir-rm-cwd) open "."
(dir-rm-cwd) "/a" and "." must have same inumber
(dir-rm-cwd) "/" and "/a" must have different inumbers
(dir-rm-cwd) chdir "/a"
(dir-rm-cwd) open "."
(dir-rm-cwd) "." must have same inumber as before
(dir-rm-cwd) chdir "/"
(dir-rm-cwd) try to remove "a" (must fail: still open)
(dir-rm-cwd) verify "/a" is empty
(dir-rm-cwd) end
EOF
(dir-rm-cwd) begin
(dir-rm-cwd) open "/"
(dir-rm-cwd) mkdir "a"
(dir-rm-cwd) open "/a"
(dir-rm-cwd) verify "/a" is empty
(dir-rm-cwd) "/" and "/a" must have different inumbers
(dir-rm-cwd) chdir "a"
(dir-rm-cwd) try to remove "/a"
(dir-rm-cwd) remove successful
(dir-rm-cwd) open "/a" (must fail)
(dir-rm-cwd) open "." (must fail)
(dir-rm-cwd) open ".." (must fail)
(dir-rm-cwd) create "x" (must fail)
(dir-rm-cwd) verify "/a" is empty
(dir-rm-cwd) end
EOF
open (CAN_RMDIR_CWD, ">tests/filesys/extended/can-rmdir-cwd")
  or die "tests/filesys/extended/can-rmdir-cwd: create: $!\n";
print CAN_RMDIR_CWD "$cwd_removable";
close (CAN_RMDIR_CWD);
pass;
