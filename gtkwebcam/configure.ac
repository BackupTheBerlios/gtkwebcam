PROJECTNAME="GtkWebcam"

#FTOK_ID

#AH_TEMPLATE(SHM_KEY, [The shared memory key defined at compile-time])
#AC_SUBST(SHM_KEY, $FTOK_ID)

AC_INIT($PROJECTNAME, 1.0, [skypher@users.sourceforge.net])
AM_INIT_AUTOMAKE(gnu dist-bzip2)
AC_CONFIG_HEADERS(config.h)

AC_ISC_POSIX
AC_PROG_CC
AM_PROG_CC_STDC
AC_HEADER_STDC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_CXXCPP
AC_PROG_LIBTOOL

AC_LANG_CPLUSPLUS

AC_CHECK_HEADERS([jpeglib.h] [png.h] [sys/ipc.h] [sys/shm.h])
AC_CHECK_FUNCS(shmget)

#PKG_CHECK_MODULES(GTKMM,[gtkmm-2.0 >= 2.1.0])

GTKMM_CFLAGS=`pkg-config gtkmm-2.0 --cflags`
GTKMM_LIBS=`pkg-config gtkmm-2.0 --libs`
GTHREAD_LIBS=`pkg-config gthread-2.0 --libs`

AC_SUBST(GTKMM_CFLAGS)
AC_SUBST(GTKMM_LIBS)
AC_SUBST(GTHREAD_LIBS)

AC_OUTPUT(
	Makefile \
	src/Makefile \
	src/control/Makefile \
	src/viewer/Makefile
	)

echo
echo "*** configure successfully finished."
echo "*** type 'make' to build."
echo
