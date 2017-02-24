//@(#)
//@(#) cubeTool.c ver.1.0 - analysis tool for Gaussian cube file
//@(#) Copyright (C), 2016, Naoya Yamaguchi
//@(#)
//@(#) Log:
//@(#)    2016/12/04 ver.1.0 Released by Naoya Yamaguchi (based on 'wf.tcl' ('wf.c'))
//@(#)    2016/12/07 ver.1.0.1 Modified by Naoya Yamaguchi (with the modification of *.h)
//@(#)    2016/12/08 ver.1.0.1.1 Modified by Naoya Yamaguchi (only the modification of *.h and argc_2.tcl)
//@(#)
//@(#) Usage:
//@(#)
//@(#)    (AVERAGE mode; UNIT=Ang, eV, or CU (=both Ang and eV))
//@(#)    (./)cubeTool (CUBE file)
//@(#)    (./)cubeTool (CUBE file) (UNIT)
//@(#)
//@(#)
//@(#)    (CUBE mode; OPERATOR=+, -, *, or norm)
//@(#)    (./)cubeTool (CUBE file 1) (CUBE file 2) (OPERATOR)
//@(#)
//@(#)
//@(#)    Description:
//@(#)    The results are written to the standard output.
//@(#)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tcl.h>
#include "TCLMacro.h"

void evalTclFile(Tcl_Interp *interp, const char *filename){
  int code=Tcl_EvalFile(interp, filename);
  if (code!=TCL_OK){
    char *result=Tcl_GetString(Tcl_GetObjResult(interp));
    fprintf(stderr, "%s\n", result);
  } else {
    fprintf(stderr, "<%s> OK\n", filename);
  }
}
void evalTcl(Tcl_Interp *interp, const char *filename, const char *command){
  int code=Tcl_Eval(interp, command);
  if (code!=TCL_OK){
    char *result=Tcl_GetString(Tcl_GetObjResult(interp));
    fprintf(stderr, "<%s> Error\n", filename);
    fprintf(stderr, "%s\n", result);
    exit(1);
  } else {
    fprintf(stderr, "<%s> OK\n", filename);
  }
}

int main(int argc, char *argv[]){
  Tcl_Interp *interp;
  Tcl_Channel channel;
  int argcTcl=argc-1;
  char *argvTcl, *p;
  int m, size=0;
  for (m=1; m<=argcTcl; m++){
    size+=strlen(argv[m]);
  }
  argvTcl=(char *)malloc(size+argcTcl);
  if (argcTcl==1){
    sprintf(argvTcl, "%s", argv[1]);
  } else if (argcTcl==2){
    sprintf(argvTcl, "%s %s", argv[1], argv[2]);
  } else {
    sprintf(argvTcl, "%s %s %s", argv[1], argv[2], argv[3]);
  }

  Tcl_FindExecutable(argv[0]);
  interp=Tcl_CreateInterp();
  channel=Tcl_GetStdChannel(TCL_STDOUT);
  Tcl_SetVar(interp, "argv", argvTcl, TCL_GLOBAL_ONLY);
  LINKTCLINT(numLine);
  LINKTCLINT(numRest);
  LINKTCLDOUBLE(Hartree2eV);
  LINKTCLDOUBLE(Bohr2Angstrom);
  LINKTCLDOUBLE(lenGtvA);

#include "init.h"

  if (argcTcl==2){

#include "argc_2.h"

  }

  if (argcTcl==1 || argcTcl==2){
    FILE *fp=fopen(argv[1], "rb");
    LINKTCLWIDEINT(fpOffset);
    LINKTCLINT(numXGrid);
    LINKTCLINT(numYGrid);
    LINKTCLINT(numGridArea);

#include "argc_1+2-1.h"

    double val[6];
    int i, j, k, l;
    fsetpos(fp, (fpos_t *)&fpOffset);
    for (k=0; k<numXGrid; k++) {
      double sum=0.0;
      for (j=0; j<numYGrid; j++) {
	for (i=0; i<numLine; i++) {
	  int dataLen= i!=numLine-1 ? 6 : numRest;
	  for (l=0; l<dataLen; l++){
	    fscanf(fp, "%lf", &val[l]);
	    sum+=val[l];
	  }
	  fgetc(fp);
	}
      }
      printf("%9.6e   %9.6e\n", Bohr2Angstrom*lenGtvA*k, Hartree2eV*sum/numGridArea);
    }
    fgetpos(fp, (fpos_t *)&fpOffset);

#include "argc_1+2-2.h"

  } else if (argcTcl==3){
    FILE *fp1=fopen(argv[1], "rb");
    FILE *fp2=fopen(argv[2], "rb");
    LINKTCLINT(numXGrid1);
    LINKTCLINT(numYGrid1);
    LINKTCLWIDEINT(fp1Offset);
    LINKTCLWIDEINT(fp2Offset);

#include "argc_3-1.h"

    double val1[6], val2[6];
    int i, j, k, l;
    LINKTCLSTRING(data1);
    LINKTCLSTRING(data2);
    fsetpos(fp1, (fpos_t *)&fp1Offset);
    fsetpos(fp2, (fpos_t *)&fp2Offset);
    for (k=0; k<numXGrid1; k++) {
      for (j=0; j<numYGrid1; j++) {
	for (i=0; i<numLine; i++) {
	  int data1Len= i!=numLine-1 ? 6 : numRest;
	  for (l=0; l<data1Len; l++){
	    fscanf(fp1, "%lf", &val1[l]);
	    fscanf(fp2, "%lf", &val2[l]);
	    if (!strcmp(argv[3], "+")) {
	      printf("%13.3E", val1[l]+val2[l]);
	    } else if (!strcmp(argv[3], "-")) {
	      printf("%13.3E", val1[l]-val2[l]);
	    } else if (!strcmp(argv[3], "*")) {
	      printf("%13.3E", val1[l]*val2[l]);
	    }  else if (!strcmp(argv[3], "norm")) {
	      printf("%13.3E", val1[l]*val1[l]+val2[l]*val2[l]);
	    }
	  }
	  fgetc(fp1);
	  fgetc(fp2);
	  puts("");
	}
      }
    }
    fgetpos(fp1, (fpos_t *)&fp1Offset);
    fgetpos(fp2, (fpos_t *)&fp2Offset);

#include "argc_3-2.h"

  } else {

#include "argc_d.h"

  }
  return 0;
}
