# cubeTool
Analysis Tool for Gaussian Cube Files

Copyright (C), 2016, Naoya Yamaguchi

## Log:
- 2016/12/04 ver.1.0 Released by Naoya Yamaguchi (based on 'wf.tcl' ('wf.c'))
- 2016/12/07 ver.1.0.1 Modified by Naoya Yamaguchi (with the modification of *.h)
- 2016/12/08 ver.1.0.1.1 Modified by Naoya Yamaguchi (only the modification of *.h and argc_2.tcl)

## Usage:
- AVERAGE mode; UNIT=Ang, eV, or CU (=both Ang and eV))
  - (./)cubeTool (CUBE file)
  - (./)cubeTool (CUBE file) (UNIT)
- (CUBE mode; OPERATOR=+, -, *, or norm)
  - (./)cubeTool (CUBE file 1) (CUBE file 2) (OPERATOR)

## Description:
The results are written to the standard output.
