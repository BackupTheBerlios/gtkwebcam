#define DEBUG(x) cout << (x) << endl; 

#include <assert.h>

#include <gtkmm/box.h>
#include <gtkmm/button.h>

#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/eventbox.h>
#include <gtkmm/menu.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/menu_elems.h>
#include <gtkmm/separatormenuitem.h>
#include <gtkmm/image.h>
#include <gtkmm/stock.h>

#include <gdkmm/drawable.h>
#include <gdkmm/colormap.h>
#include <gdkmm/window.h>
#include <gdkmm/rectangle.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <linux/videodev.h>
#include <sys/ioctl.h>
#include "pwc-ioctl.h"
#include "ccvt.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class OptionMenu : public Gtk::Menu
{
	public:
		OptionMenu();

		inline void setzoom05() { _zoomfactor = 0.5; return; }
		inline void setzoom10() { _zoomfactor = 1.0; return; }
		inline void setzoom20() { _zoomfactor = 2.0; return; }

		inline float getZoomFactor() { return(_zoomfactor); }

	protected:


	private:
		float _zoomfactor;
		Gtk::Menu _zoommenu, _resmenu;
		Gtk::SeparatorMenuItem _separator;
};


class ViewArea : public Gtk::DrawingArea
{
	public:
		ViewArea();
		~ViewArea();

		bool on_button_press_event(GdkEventButton* event);
		void readImage();
		bool update(bool invalidate);
		void redraw();

		void updateVideoWin();

	protected:
		void on_realize();
		bool on_expose_event(GdkEventExpose* e);

	private:
		void allocBuffers();
		void clearBuffers();

		OptionMenu _options;
		Glib::RefPtr<Gdk::Drawable> _drawable;
		Glib::RefPtr<Gdk::Colormap> _colormap;
		Glib::RefPtr<Gdk::Window> _window;
		Glib::RefPtr<Gdk::GC> _gc;
		Gdk::Color _black;

		int _camfd;
		struct video_window _vwin;
		long _bufsize, _buf24size;
		unsigned char* _readbuf, *_buf24;
};
