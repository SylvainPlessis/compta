 dnl                                               -*- Autoconf -*-
dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([compta], [1.0.2], [sylvain.plessis@gmail.com], [compta])
PACKAGE_DESCRIPTION="personnal terminal-based program for comptability"
AC_SUBST([PACKAGE_DESCRIPTION])
PACKAGE_URL="https://code.google.com/p/comptabilite/"
AC_SUBST([PACKAGE_URL])
AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_HEADER(compta_config.h.tmp)
dnl Prefixes everything in the temporary file with COMPTA_
AX_PREFIX_CONFIG_H(compta_config.h,COMPTA,compta_config.h.tmp)

AC_CONFIG_AUX_DIR([build-aux])
AC_CANONICAL_TARGET()
AM_INIT_AUTOMAKE([dist-bzip2 tar-ustar 1.11 no-define color-tests parallel-tests])
AM_SILENT_RULES(yes)  # use silent rules where available - automake 1.11

LT_PREREQ([2.5.2])
LT_INIT

dnl Release versioning
AX_SPLIT_VERSION
GENERIC_MAJOR_VERSION=$AX_MAJOR_VERSION
GENERIC_MINOR_VERSION=$AX_MINOR_VERSION
GENERIC_MICRO_VERSION=$AX_POINT_VERSION
GENERIC_LIBRARY_NAME=compta

dnl shared library versioning

PACKAGE=$GENERIC_LIBRARY_NAME
GENERIC_VERSION=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION.$GENERIC_MICRO_VERSION
GENERIC_RELEASE=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION

dnl AC_SUBST(GENERIC_LIBRARY_VERSION)
dnl AC_SUBST(GENERIC_LIBRARY_NAME)

AC_SUBST(GENERIC_VERSION)
AC_SUBST(GENERIC_RELEASE)
AC_SUBST(GENERIC_MAJOR_VERSION)
AC_SUBST(GENERIC_MINOR_VERSION)
AC_SUBST(GENERIC_MICRO_VERSION)

AC_DEFINE_UNQUOTED([MAJOR_VERSION],$GENERIC_MAJOR_VERSION,[Major version])
AC_DEFINE_UNQUOTED([MINOR_VERSION],$GENERIC_MINOR_VERSION,[Minor version])
AC_DEFINE_UNQUOTED([MICRO_VERSION],$GENERIC_MICRO_VERSION,[Micro version])


dnl------------------------------
dnl Checks for compilers
dnl------------------------------

AC_PROG_CC
AC_PROG_CXX

dnl Added for AX_CODE_COVERAGE macro to work correctly, even though there's no Fortran here.
AC_PROG_FC

dnl -Wall warnings, -Wall the time.
AX_CXXFLAGS_WARN_ALL


dnl--------------------------
dnl Checks for code coverage
dnl--------------------------
AX_CODE_COVERAGE

dnl---------------------------------
dnl Query configuration environment
dnl Must be done *before* Doxygen to
dnl get some happy variables defined.
dnl---------------------------------
AX_SUMMARIZE_ENV

dnl------------------------------------------
dnl            Doxygen support
dnl------------------------------------------

DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(OFF)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(OFF)
DX_PS_FEATURE(OFF)

DX_INIT_DOXYGEN(compta, doxygen/compta.dox, docs/doxygen)

dnl-----------------------------------------------
dnl Generate files for unit and regression testing
dnl-----------------------------------------------
#AC_CONFIG_FILES(test/kinetics_unit_air_5sp.sh,           [chmod +x test/kinetics_unit_air_5sp.sh])

dnl-----------------------------------------------
dnl Generate header files
dnl-----------------------------------------------
AC_CONFIG_FILES(src/utilities/include/compta/compta_version.hpp)

dnl-----------------------------------------------
dnl Generate Makefiles and other templated things
dnl-----------------------------------------------
AC_CONFIG_FILES([
  compta.pc
  doxygen/Makefile
  doxygen/compta.dox
  Makefile
  src/Makefile
  test/Makefile
])

dnl-----------------------------------------------
dnl Collect files for "header stamping" here
dnl brutally copy/pasted from Antioch
dnl-----------------------------------------------

# PB: Although the documentation says that ac_top_srcdir should be defined,
#     it doesn't get activated until _AC_SRCDIRS gets called
#     (used to be _AC_SRCPATHS), according to this thread:
#     http://lists.gnu.org/archive/html/autoconf-patches/2003-02/msg00003.html
#     My own hacking revealed that we could also do the following:
#     TOP_SEARCH_DIR=$ac_pwd/$srcdir
#     I'm not sure which will be more "future proof", but this is the alternative
#     to using $(shell) calls in the Makefile.am which 1. requires
#     GNU Make and 2. Causes automake to issue a warning
_AC_SRCDIRS(.)
TOP_SEARCH_DIR=$ac_abs_top_srcdir

# We have to do this by subdirectory because otherwise distcheck
# breaks as we start picking up files in the directories
# that it uses.
COMPTA_STAMPED_FILES=$(find $TOP_SEARCH_DIR/{src,test} -name "*.hpp" -or -name "*.cpp" | tr "\n" " ")
AC_SUBST(COMPTA_STAMPED_FILES)

# Must still call AC_OUTPUT() after generating all the files
AC_OUTPUT()

dnl------------------------------
dnl Final summary
dnl------------------------------
AX_SUMMARIZE_CONFIG
