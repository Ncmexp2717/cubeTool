switch -nocase -- [lindex $argv 1] {\
  Ang {\
    set Bohr2Angstrom 0.52917721092\
  }\
  eV {\
    set Hartree2eV 27.2114\
  }\
  CU {;#Conventional Unit
    set Bohr2Angstrom 0.52917721092\
    set Hartree2eV 27.2114\
  }\
  default {\
    puts stderr "Error: Wrong arguments."\
    exit 3\
  }\
}
