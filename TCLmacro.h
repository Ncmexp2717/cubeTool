#define HEREDOC(...) #__VA_ARGS__

#define LINKTCLINT(varname) \
    static char *varname ## Tcl=#varname; \
    int varname; \
    Tcl_LinkVar(interp, varname ## Tcl, (char *)&varname, TCL_LINK_INT);

#define LINKTCLDOUBLE(varname) \
    static char *varname ## Tcl=#varname; \
    double varname; \
    Tcl_LinkVar(interp, varname ## Tcl, (char *)&varname, TCL_LINK_DOUBLE);

#define LINKTCLWIDEINT(varname) \
    static char *varname ## Tcl=#varname; \
    Tcl_WideInt varname; \
    Tcl_LinkVar(interp, varname ## Tcl, (char *)&varname, TCL_LINK_WIDE_INT);

#define LINKTCLSTRING(varname) \
    static char *varname ## Tcl=#varname; \
    char *varname; \
    varname=Tcl_Alloc(1024); \
    Tcl_LinkVar(interp, varname ## Tcl, (char *)&varname, TCL_LINK_STRING);
