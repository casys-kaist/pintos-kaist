# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(rox-multichild) begin
(rox-multichild) open "child-rox"
(rox-multichild) read "child-rox"
(rox-multichild) write "child-rox"
(rox-multichild) exec "child-rox 5"
(child-rox) begin
(child-rox) try to write "child-rox"
(child-rox) exec "child-rox 4"
(child-rox) begin
(child-rox) try to write "child-rox"
(child-rox) exec "child-rox 3"
(child-rox) begin
(child-rox) try to write "child-rox"
(child-rox) exec "child-rox 2"
(child-rox) begin
(child-rox) try to write "child-rox"
(child-rox) exec "child-rox 1"
(child-rox) begin
(child-rox) try to write "child-rox"
(child-rox) try to write "child-rox"
(child-rox) end
child-rox: exit(12)
(child-rox) try to write "child-rox"
(child-rox) end
child-rox: exit(12)
(child-rox) try to write "child-rox"
(child-rox) end
child-rox: exit(12)
(child-rox) try to write "child-rox"
(child-rox) end
child-rox: exit(12)
(child-rox) try to write "child-rox"
(child-rox) end
child-rox: exit(12)
(rox-multichild) write "child-rox"
(rox-multichild) end
rox-multichild: exit(0)
EOF
pass;
