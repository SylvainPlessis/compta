# SYNOPSIS
#
#   Test for Compta
#
#   AX_PATH_COMPTA( <Minimum Required Version>, <package-required=yes/no> )
#
# DESCRIPTION
#
#   Provides a --with-compta=DIR option. Searches --with-compta,
#   $COMPTA_DIR, and the usual places for COMPTA headers and libraries.
#
#   On success, sets COMPTA_CPPFLAGS, COMPTA_LIBS, and #defines HAVE_COMPTA.
#   Also defines automake conditional COMPTA_ENABLED.  Assumes package
#   is optional unless overridden with $2=yes.
#
# LAST MODIFICATION
#
#   $Id: compta.m4 37037 2013-02-16 01:03:09Z pbauman $
#
# COPYLEFT
#
#   Copyright (c) 2013 Sylvain Plessis <sylvain.plessis@gmail.com>
#   Copyright (c) 2013 Roy H. Stogner <roystgnr@ices.utexas.edu>
#   Copyright (c) 2013 Paul T. Bauman <pbauman@ices.utexas.edu>
#   Copyright (c) 2010 Karl W. Schulz <karl@ices.utexas.edu>
#   Copyright (c) 2009 Rhys Ulerich <rhys.ulerich@gmail.com>
#   Copyright (c) 2008 Thomas Porschberg <thomas@randspringer.de>
#   Copyright (c) 2008 Caolan McNamara <caolan@skynet.ie>
#   Copyright (c) 2008 Alexandre Duret-Lutz <adl@gnu.org>
#   Copyright (c) 2008 Matthew Mueller <donut@azstarnet.com>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved.

AC_DEFUN([AX_PATH_COMPTA],
[

AC_ARG_VAR(COMPTA_DIR,[root directory of Compta installation])

AC_ARG_WITH(compta,
  [AS_HELP_STRING([--with-compta[=DIR]],[root directory of Compta installation (default = COMPTA_DIR)])],
  [with_compta=$withval
if test "${with_compta}" != yes; then
    COMPTA_PREFIX=$withval
fi
],[
with_compta=$withval
if test "x${COMPTA_DIR}" != "x"; then
   COMPTA_PREFIX=${COMPTA_DIR}
fi
])

# package requirement; if not specified, the default is to assume that
# the package is optional

is_package_required=ifelse([$2], ,no, $2 )

HAVE_COMPTA=0

# logic change: if the user called the macro, check for package,
# decide what to do based on whether the package is required or not.

# if test "${with_compta}" != no ; then

    if test -d "${COMPTA_PREFIX}/lib" ; then
       COMPTA_LDFLAGS="-L${COMPTA_PREFIX}/lib -Wl,-rpath,${COMPTA_PREFIX}/lib"
       COMPTA_LIBS="-lcompta"
    fi

    if test -d "${COMPTA_PREFIX}/include" ; then
       COMPTA_CPPFLAGS="-I${COMPTA_PREFIX}/include -I${COMPTA_PREFIX}/src"
    fi

    ac_COMPTA_save_CPPFLAGS="$CPPFLAGS"
    ac_COMPTA_save_LDFLAGS="$LDFLAGS"
    ac_COMPTA_save_LIBS="$LIBS"

    CPPFLAGS="${COMPTA_CPPFLAGS} ${CPPFLAGS}"
    LDFLAGS="${COMPTA_LDFLAGS} ${LDFLAGS}"
    LIBS="${COMPTA_LIBS} ${LIBS}"

    AC_LANG_PUSH([C++])
    AC_CHECK_HEADER([compta/compta_version.h],[found_header=yes],[found_header=no])
    AC_LANG_POP([C++])

    #-----------------------
    # Minimum version check
    #----------------------

    min_compta_version=ifelse([$1], ,0.0.0, $1)

    # looking for major.minor.micro style versioning

    MAJOR_VER=`echo $min_compta_version | sed 's/^\([[0-9]]*\).*/\1/'`
    if test "x${MAJOR_VER}" = "x" ; then
       MAJOR_VER=0
    fi

    MINOR_VER=`echo $min_compta_version | sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\2/'`
    if test "x${MINOR_VER}" = "x" ; then
       MINOR_VER=0
    fi

    MICRO_VER=`echo $min_compta_version | sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\3/'`
    if test "x${MICRO_VER}" = "x" ; then
       MICRO_VER=0
    fi

    # begin additional test(s) if header if available

    if test "x${found_header}" = "xyes" ; then

        AC_MSG_CHECKING(for compta - version >= $min_compta_version)
        version_succeeded=no

	AC_LANG_PUSH([C++])
        AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
        @%:@include "compta/compta_version.h"
            ]], [[
            #if COMPTA_MAJOR_VERSION > $MAJOR_VER
            /* Sweet nibblets */
            #elif (COMPTA_MAJOR_VERSION >= $MAJOR_VER) && (COMPTA_MINOR_VERSION > $MINOR_VER)
            /* Winner winner, chicken dinner */
            #elif (COMPTA_MAJOR_VERSION >= $MAJOR_VER) && (COMPTA_MINOR_VERSION >= $MINOR_VER) && (COMPTA_MICRO_VERSION >= $MICRO_VER)
            /* I feel like chicken tonight, like chicken tonight? */
            #else
            #  error version is too old
            #endif
        ]])],[
            AC_MSG_RESULT(yes)
            version_succeeded=yes
        ],[
            AC_MSG_RESULT(no)
        ])
	AC_LANG_POP([C++])

    if test "$version_succeeded" != "yes";then
       if test "$is_package_required" = yes; then
          AC_MSG_ERROR([

   Your Compta version does not meet the minimum versioning
   requirements ($min_compta_version).  Please use --with-compta to specify the location
   of an updated installation or consider upgrading the system version.

          ])
       fi
    fi

    fi   dnl end test if header if available

    CPPFLAGS="$ac_COMPTA_save_CPPFLAGS"
    LDFLAGS="$ac_COMPTA_save_LDFLAGS"
    LIBS="$ac_COMPTA_save_LIBS"

    succeeded=no
    if test "$found_header" = yes; then
        if test "$version_succeeded" = yes; then
              succeeded=yes
        fi
    fi

    if test "$succeeded" = no; then
       if test "$is_package_required" = yes; then
          AC_MSG_ERROR([Compta not found.  Try either --with-compta or setting COMPTA_DIR.])
       else
          AC_MSG_NOTICE([optional Compta library not found])
          COMPTA_CPPFLAGS=""   # COMPTA_CFLAGS empty on failure
          COMPTA_LDFLAGS=""    # COMPTA_LDFLAGS empty on failure
          COMPTA_LIBS=""       # COMPTA_LIBS empty on failure
       fi
    else
        HAVE_COMPTA=1
        AC_DEFINE(HAVE_COMPTA,1,[Define if Compta is available])
        AC_SUBST(COMPTA_CPPFLAGS)
        AC_SUBST(COMPTA_LDFLAGS)
        AC_SUBST(COMPTA_LIBS)
        AC_SUBST(COMPTA_PREFIX)
    fi

    AC_SUBST(HAVE_COMPTA)

# fi

AM_CONDITIONAL(COMPTA_ENABLED,test x$HAVE_COMPTA = x1)

])
