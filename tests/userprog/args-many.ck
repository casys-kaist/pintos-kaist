# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(args) begin
(args) argc = 23
(args) argv[0] = 'args-many'
(args) argv[1] = 'a'
(args) argv[2] = 'b'
(args) argv[3] = 'c'
(args) argv[4] = 'd'
(args) argv[5] = 'e'
(args) argv[6] = 'f'
(args) argv[7] = 'g'
(args) argv[8] = 'h'
(args) argv[9] = 'i'
(args) argv[10] = 'j'
(args) argv[11] = 'k'
(args) argv[12] = 'l'
(args) argv[13] = 'm'
(args) argv[14] = 'n'
(args) argv[15] = 'o'
(args) argv[16] = 'p'
(args) argv[17] = 'q'
(args) argv[18] = 'r'
(args) argv[19] = 's'
(args) argv[20] = 't'
(args) argv[21] = 'u'
(args) argv[22] = 'v'
(args) argv[23] = null
(args) end
args-many: exit(0)
EOF
pass;
