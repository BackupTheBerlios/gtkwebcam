// generated 2002/12/18 13:23:29 CET by sky@dreadnought.(none)
// using glademm V1.1.3c_cvs
//
// newer (non customized) versions of this file go to gtkwebcam.cc_new

// This file is for your program, I won't touch it again!

#include <gtkmm/main.h>

#include "ControlWindow.hh"

int main(int argc, char **argv)
{
	Glib::thread_init();
	Gtk::Main m(&argc, &argv);

	ControlWindow *ControlWindow = new class ControlWindow();
	m.run(*ControlWindow);
	delete ControlWindow;

	return(0);
}
