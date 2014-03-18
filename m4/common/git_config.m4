# SYNOPSIS
#
#   Queries configuration environment.
#
#   AX_SUMMARIZE_GIT_ENV([, ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]])
#
# DESCRIPTION
#
#   Queries compile environment and git hash and tag for use in configure summary 
#   and pre-processing macros.
#
# LAST MODIFICATION
#
#   23/02/2014
#
# COPYLEFT
#
#   Copyright (c) 2014 Sylvain Plessis <sylvain.plessis@gmail.com>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved.

AC_DEFUN([AX_SUMMARIZE_GIT_ENV],
[

AC_CANONICAL_HOST

BUILD_USER=${USER}
BUILD_ARCH=${host}
BUILD_HOST=${ac_hostname}
BUILD_DATE=`date +'%F %H:%M'`

# Determine method for querying Source code revisioning (for git)

AC_PATH_PROG(gitquery,git)

# check for .git folder
if test -d $srcdir/.git  ; then
   GIT_TAG="${gitquery} describe --abbrev=0 "
   GIT_HASH="${gitquery} rev-parse --short HEAD"
   GIT_CHECKOUT=true
   BUILD_DEVSTATUS="Development Build"
else
   GIT_TAG="External Release"
   GIT_HASH="cat $srcdir/dist_version"
   GIT_CHECKOUT=false
   BUILD_DEVSTATUS="External Release"
fi


AC_SUBST(GIT_HASH)
AC_SUBST(GIT_TAG)
AC_SUBST(BUILD_DEVSTATUS)
AM_CONDITIONAL(GIT_CHECKOUT,test x${GIT_CHECKOUT} = xtrue )

# Query current version.

BUILD_VERSION=`${GIT_HASH}`
if test "x${GIT_TAG}" = "xExternal Release" ; then
   BUILD_TAG=${GIT_TAG}
else
   BUILD_TAG=`${GIT_TAG}`
fi

# Versioning info - check local developer version (if checked out)

AC_DEFINE_UNQUOTED([BUILD_USER],     "${BUILD_USER}",     [The fine user who built the package])
AC_DEFINE_UNQUOTED([BUILD_ARCH],     "${BUILD_ARCH}",     [Architecture of the build host])
AC_DEFINE_UNQUOTED([BUILD_HOST],     "${BUILD_HOST}",     [Build host name])
AC_DEFINE_UNQUOTED([BUILD_VERSION],  "${BUILD_VERSION}",  [git hash])
AC_DEFINE_UNQUOTED([BUILD_TAG],      "${BUILD_TAG}",      [git tag])
AC_DEFINE_UNQUOTED([BUILD_DEVSTATUS],"${BUILD_DEVSTATUS}",[Dev/Release build])
AC_DEFINE(         [BUILD_DATE],     __DATE__" "__TIME__, [Build date])

AC_SUBST(BUILD_USER)
AC_SUBST(BUILD_ARCH)
AC_SUBST(BUILD_HOST)
AC_SUBST(BUILD_DATE)
AC_SUBST(BUILD_VERSION)
AC_SUBST(BUILD_TAG)

])
