bin_PROGRAMS = gtkwc_viewer

gtkwc_viewer_SOURCES = \
	ccvt_c.c \
	viewer.cxx \
	jpegwriter.cxx

noinst_HEADERS = \
	jpegwriter.hxx \
	ccvt.h \
	viewer.hxx

AM_CXXFLAGS = @CXXFLAGS@ @GTKMM_CFLAGS@

gtkwc_viewer_LDADD = @LIBS@ @GTKMM_LIBS@ -lz -lpng -ljpeg
