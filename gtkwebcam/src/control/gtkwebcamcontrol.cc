// generated 2003/1/7 19:34:04 CET by sky@dreadnought.(none)
// using glademm V1.1.3c_cvs
//
// newer (non customized) versions of this file go to gtkwebcamcontrol.cc_new

// This file is for your program, I won't touch it again!

#include <gtkmm/main.h>

#include "ControlWindow.hh"

int main(int argc, char **argv)
{  
   
   Gtk::Main m(&argc, &argv);

ControlWindow *ControlWindow = new class ControlWindow();
   m.run(*ControlWindow);
delete ControlWindow;
   return 0;
}
