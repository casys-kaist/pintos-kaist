# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(mount-easy) begin
(mount-easy) mkdir "/a"
(mount-easy) mount the second disk at "/a"
Formatting file system...done.
(mount-easy) chdir "/a"
(mount-easy) mkdir "/a/b"
(mount-easy) chdir "/a/b"
(mount-easy) pop back to "/"
(mount-easy) unmount the second disk from "/a"
(mount-easy) chdir to unmounted directory (must fail)
(mount-easy) mount the second disk at "/a"
(mount-easy) chdir to re-mounted directory
(mount-easy) end
EOF
pass;
