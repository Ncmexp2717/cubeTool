evalTcl(interp, "argc_1+2-2", HEREDOC(
seek $fp $fpOffset;
while {[gets $fp data]>=0} {
  puts stderr "Error: Wrong line.";
  exit 2;
};
)
);
