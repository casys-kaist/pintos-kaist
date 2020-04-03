# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(multi-recurse) begin 15
(multi-recurse) exec("multi-recurse 14")
(multi-recurse) begin 14
(multi-recurse) exec("multi-recurse 13")
(multi-recurse) begin 13
(multi-recurse) exec("multi-recurse 12")
(multi-recurse) begin 12
(multi-recurse) exec("multi-recurse 11")
(multi-recurse) begin 11
(multi-recurse) exec("multi-recurse 10")
(multi-recurse) begin 10
(multi-recurse) exec("multi-recurse 9")
(multi-recurse) begin 9
(multi-recurse) exec("multi-recurse 8")
(multi-recurse) begin 8
(multi-recurse) exec("multi-recurse 7")
(multi-recurse) begin 7
(multi-recurse) exec("multi-recurse 6")
(multi-recurse) begin 6
(multi-recurse) exec("multi-recurse 5")
(multi-recurse) begin 5
(multi-recurse) exec("multi-recurse 4")
(multi-recurse) begin 4
(multi-recurse) exec("multi-recurse 3")
(multi-recurse) begin 3
(multi-recurse) exec("multi-recurse 2")
(multi-recurse) begin 2
(multi-recurse) exec("multi-recurse 1")
(multi-recurse) begin 1
(multi-recurse) exec("multi-recurse 0")
(multi-recurse) begin 0
(multi-recurse) end 0
multi-recurse: exit(0)
(multi-recurse) end 1
multi-recurse: exit(1)
(multi-recurse) end 2
multi-recurse: exit(2)
(multi-recurse) end 3
multi-recurse: exit(3)
(multi-recurse) end 4
multi-recurse: exit(4)
(multi-recurse) end 5
multi-recurse: exit(5)
(multi-recurse) end 6
multi-recurse: exit(6)
(multi-recurse) end 7
multi-recurse: exit(7)
(multi-recurse) end 8
multi-recurse: exit(8)
(multi-recurse) end 9
multi-recurse: exit(9)
(multi-recurse) end 10
multi-recurse: exit(10)
(multi-recurse) end 11
multi-recurse: exit(11)
(multi-recurse) end 12
multi-recurse: exit(12)
(multi-recurse) end 13
multi-recurse: exit(13)
(multi-recurse) end 14
multi-recurse: exit(14)
(multi-recurse) end 15
multi-recurse: exit(15)
EOF
pass;
