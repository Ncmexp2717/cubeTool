set fp1 [open [lindex $argv 0] r]
set fp2 [open [lindex $argv 1] r]
set operator [lindex $argv 2]
gets $fp1 data1
gets $fp2 data2
checkMatching $data1 $data2
gets $fp1 data1
gets $fp2 data2
checkMatching $data1 $data2
gets $fp1 data1
gets $fp2 data2
checkMatching $data1 $data2
set numAtom1 [lindex $data1 0]
set numAtom2 [lindex $data2 0]
gets $fp1 data1
gets $fp2 data2
checkMatching $data1 $data2
set numXGrid1 [lindex $data1 0]
set numXGrid2 [lindex $data2 0]
gets $fp1 data1
gets $fp2 data2
checkMatching $data1 $data2
set numYGrid1 [lindex $data1 0]
set numYGrid2 [lindex $data2 0]
gets $fp1 data1
gets $fp2 data2
checkMatching $data1 $data2
set numZGrid1 [lindex $data1 0]
set numZGrid2 [lindex $data2 1]
for {set i 0} {$i<$numAtom1} {incr i} {
  gets $fp1 data1
  gets $fp2 data2
  checkMatching $data1 $data2
}
set numLine [expr $numZGrid1/6+1]
set numRest [expr $numZGrid1%6]
set fp1Offset [tell $fp1]
set fp2Offset [tell $fp2]
