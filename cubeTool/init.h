evalTcl(interp, "init", HEREDOC(
proc checkMatching {data1 data2} {
  if {![string equal $data1 $data2]} {
    puts stderr "Error: Unmatched files.";
    exit 1;
  } else {
    puts $data1;
  };
};
set Bohr2Angstrom 1;
set Hartree2eV 1;
)
);
