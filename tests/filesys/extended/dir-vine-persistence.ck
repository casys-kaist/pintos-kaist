# -*- perl -*-
use strict;
use warnings;
use tests::tests;
# The archive should look like this:
#
# 40642 dir-vine
# 42479 tar
#     0 start
#    11 start/file0
#     0 start/dir0
#    11 start/dir0/file1
#     0 start/dir0/dir1
#    11 start/dir0/dir1/file2
#     0 start/dir0/dir1/dir2
#    11 start/dir0/dir1/dir2/file3
#     0 start/dir0/dir1/dir2/dir3
#    11 start/dir0/dir1/dir2/dir3/file4
#     0 start/dir0/dir1/dir2/dir3/dir4
#    11 start/dir0/dir1/dir2/dir3/dir4/file5
#     0 start/dir0/dir1/dir2/dir3/dir4/dir5
#    11 start/dir0/dir1/dir2/dir3/dir4/dir5/file6
#     0 start/dir0/dir1/dir2/dir3/dir4/dir5/dir6
#    11 start/dir0/dir1/dir2/dir3/dir4/dir5/dir6/file7
#     0 start/dir0/dir1/dir2/dir3/dir4/dir5/dir6/dir7
#    11 start/dir0/dir1/dir2/dir3/dir4/dir5/dir6/dir7/file8
#     0 start/dir0/dir1/dir2/dir3/dir4/dir5/dir6/dir7/dir8
#    11 start/dir0/dir1/dir2/dir3/dir4/dir5/dir6/dir7/dir8/file9
#     0 start/dir0/dir1/dir2/dir3/dir4/dir5/dir6/dir7/dir8/dir9
my ($dir) = {};
my ($root) = {"start" => $dir};
for (my ($i) = 0; $i < 10; $i++) {
    $dir->{"file$i"} = ["contents $i\n"];
    $dir = $dir->{"dir$i"} = {};
}
check_archive ($root);
pass;
