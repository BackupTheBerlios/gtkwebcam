bin_PROGRAMS = gtkwc_control

gtkwc_control_SOURCES = \
	ControlWindow.cc \
	ControlWindow_glade.cc \
	gtkwebcamcontrol.cc

noinst_HEADERS = \
	ControlWindow.hh
	ControlWindow_glade.hh
	gtkwebcamcontrol.hh


AM_CXXFLAGS = @CXXFLAGS@ @GTKMM_CFLAGS@

gtkwc_control_LDADD = @LIBS@ @GTKMM_LIBS@ -lz -lpng -ljpeg
