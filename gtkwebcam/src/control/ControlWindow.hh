// generated 2002/12/18 12:48:10 CET by sky@dreadnought.(none)
// using glademm V1.1.3c_cvs
//
// newer (non customized) versions of this file go to ControlWindow.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _CONTROLWINDOW_HH
#define _CONTROLWINDOW_HH

using namespace std;

#include "ControlWindow_glade.hh"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <linux/videodev.h>
#include <sys/ioctl.h>
#include "pwc-ioctl.h"

#include <iostream>
#include <sstream>
#include <vector>

#ifdef HAVE_STAT_H
#	include <sys/stat.h>
#endif

/*#ifdef HAVE_PNG_H
#	include <png.h>
#endif

#ifdef HAVE_JPEGLIB_H
#	include "jpegwriter.hxx"
#endif*/

/*
string itos(int i)
{
	ostringstream out;

	out << i;

	return(out.str());
}
*/


class ControlWindow : public ControlWindow_glade
{
		public:
			ControlWindow();

        protected:
			void on_brightness_changed();
			void on_contrast_changed();
			void on_color_changed();
			void on_hue_changed();
			void on_gamma_changed();

			void on_backlightcomp_toggled();
			void on_flickercomp_toggled();

			void on_dynnoise_none_activate();
			void on_dynnoise_low_activate();
			void on_dynnoise_medium_activate();
			void on_dynnoise_high_activate();

			void on_50p_activate();
			void on_100p_activate();
			void on_200p_activate();

			void on_compression_level_none_activate();
			void on_compression_level_low_activate();
			void on_compression_level_medium_activate();
			void on_compression_level_high_activate();

			void on_menu_resolution_preview_changed();
			void on_menu_resolution_snapshot_changed();
			void on_snapshotbutton_clicked();
			void cb_save_user_settings();
			void cb_restore_user_settings();
			void cb_restore_factory_defaults();
			void gtk_main_quit();

		private:
			int _camfd;
			struct video_window _vwin;
};
#endif
