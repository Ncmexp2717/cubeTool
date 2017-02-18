set fp [open [lindex $argv 0] r]
gets $fp data
gets $fp data
gets $fp data
set numAtom [lindex $data 0]
gets $fp data
set numXGrid [lindex $data 0]
set ax [lindex $data 1]
set ay [lindex $data 2]
set az [lindex $data 3]
set lenGtvA [expr sqrt($ax*$ax+$ay*$ay+$az*$az)]
gets $fp data
set numYGrid [lindex $data 0]
gets $fp data
set numZGrid [lindex $data 0]
for {set i 0} {$i<$numAtom} {incr i} {
  gets $fp data
}
set numLine [expr $numZGrid/6+1]
set numRest [expr $numZGrid%6]
set numGridArea [expr $numZGrid*$numYGrid]
set fpOffset [tell $fp]
