seek $fp1 $fp1Offset
seek $fp2 $fp2Offset
if {[gets $fp1 data1]>=0 || [gets $fp2 data2]>=0} {
  puts stderr "Error: Wrong line."
  exit 2
}
