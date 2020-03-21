# -*- perl -*-
use strict;
use warnings;
use tests::tests;
use tests::threads::mlfqs;

check_mlfqs_fair ([(0) x 20], 20);
