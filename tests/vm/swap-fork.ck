# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 0, [<<'EOF']);
(swap-fork) begin
(child-swap) begin
(child-swap) begin
(child-swap) begin
(child-swap) begin
(child-swap) begin
(child-swap) begin
(child-swap) begin
(child-swap) begin
(child-swap) begin
(child-swap) begin
(swap-fork) end
EOF
pass;
