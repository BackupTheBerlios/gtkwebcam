/* TODO:
	- Improve buffer (de)allocation
	- add scaling algorithm(s)
	- adjust timeout func to frame rate reported by ioctl()
	- add shm ipc to get text string from controller app
	*/

#include "viewer.hxx"

int main(int argc, char** argv)
{
	Gtk::Main viewer(argc, argv);

	ViewArea _view;
	Gtk::EventBox _eventbox;
	Gtk::Window _viewwin;
	
	_eventbox.signal_button_press_event().connect(SigC::slot(_view, &ViewArea::on_button_press_event));
	_eventbox.add(_view);

	_viewwin.add(_eventbox);
	_viewwin.set_resizable(false);
	_viewwin.set_title("Webcam output on (insert modelname here)");
	_viewwin.show_all();

	viewer.run(_viewwin);

	return(0);
}

ViewArea::ViewArea()
{
	_camfd = open("/dev/video0", O_RDONLY);

	if (!_camfd)
	{
		cout << "couldn't open camera device" << endl ;
		abort();
	}
	
	_colormap = get_default_colormap();
	_black = Gdk::Color("black");
	_colormap->alloc_color(_black);

	Glib::signal_timeout().connect(SigC::bind(SigC::slot(*this, &ViewArea::update), true), 1000 / 24);

	this->allocBuffers();
	
	return;
}


ViewArea::~ViewArea()
{
	close(_camfd);

	return;
}


bool ViewArea::update(bool invalidate = true)
{
	this->updateVideoWin();

	if (_readbuf != NULL && _buf24 != NULL)
	{
		this->clearBuffers();
	}

	this->allocBuffers();	
	
	this->readImage();

	if (invalidate == true)
	{
		this->queue_draw_area(0, 0, _vwin.width, _vwin.height);
	}

	this->redraw();

	return(true);
}

void ViewArea::on_realize()
{
	Gtk::DrawingArea::on_realize();

	_window = get_window();
	assert(_window != NULL && _window != 0);
	_drawable = _window;
	assert(_drawable != NULL);
	_gc = Gdk::GC::create(_drawable);

	this->update(false);

	_window->set_background(_black);
	_window->clear();

	return;
}


bool ViewArea::on_button_press_event(GdkEventButton* event)
{
	if ((event->type == GDK_BUTTON_PRESS) && (event->button == 3))
	{
		_options.popup(event->button, event->time);
		return(true);
	}
	else
	{
		return(false);
	}
}


void ViewArea::readImage()
{
	assert(_readbuf != NULL && _buf24 != NULL);

	long bytesread = read(_camfd, _readbuf, _bufsize);
	if (bytesread == (-1))
	{
		cout << endl ;
		perror("read()");
		abort();
	}
	//cout << "got " << bytesread << " bytes" << endl ;

	unsigned char* ybuffer = _readbuf;
	unsigned char* ubuffer = (_readbuf + (_vwin.width * _vwin.height));
	unsigned char* vbuffer = (ubuffer + ((_vwin.width * _vwin.height) / 4));
	ccvt_420p_rgb24(_vwin.width, _vwin.height, ybuffer, ubuffer, vbuffer, _buf24);

	return;
}


void ViewArea::redraw()
{
	assert(_buf24 != NULL);
	assert(_drawable != NULL);
	_drawable->draw_rgb_image(_gc, 0, 0, _vwin.width, (_vwin.height - 1), Gdk::RGB_DITHER_MAX, _buf24, (_vwin.width * 3));

	return;
}

bool ViewArea::on_expose_event(GdkEventExpose* e)
{
	this->update();

	return(true);
}

void ViewArea::updateVideoWin()
{
	int retval = ioctl(_camfd, VIDIOCGWIN, &_vwin);
	if (retval == (-1))
	{
		perror("VIDIOCGWIN");
		abort();
	}
	//cout << "camera resolution: " << _vwin.width << "x" << _vwin.height << " pixels" << endl ;

	this->get_toplevel()->set_size_request(_vwin.width, _vwin.height);

	return;
}

void ViewArea::allocBuffers()
{
	this->updateVideoWin();

	_bufsize = 1.5 * _vwin.width * _vwin.height;
	_buf24size = 3 * _vwin.width * _vwin.height;

	//cout << "new buffer size is " << _bufsize << " (" << _buf24size << ") bytes." << endl ;

	_readbuf = new unsigned char[_bufsize];
	_buf24 = new unsigned char[_buf24size];

	return;
}

void ViewArea::clearBuffers()
{
	delete []_readbuf;
	delete []_buf24;

	return;
}


OptionMenu::OptionMenu()
{
	//_zoommenu.set_title("_Zoom");
	/*Gtk::Menu::MenuList& zoomitems = _zoommenu.items();
	zoomitems.push_back(Gtk::Menu_Helpers::MenuElem("x 0.5", SigC::slot(*this, &OptionMenu::setzoom05)));
	zoomitems.push_back(Gtk::Menu_Helpers::MenuElem("x 1.0", SigC::slot(*this, &OptionMenu::setzoom10)));
	zoomitems.push_back(Gtk::Menu_Helpers::MenuElem("x 2.0", SigC::slot(*this, &OptionMenu::setzoom20)));*/

	Gtk::Menu::MenuList& optionitems = this->items();
	optionitems.push_back(Gtk::Menu_Helpers::SeparatorElem());
	
	//optionitems.push_back(Gtk::Menu_Helpers::MenuElem("_Zoom", _zoommenu));
	optionitems.push_back(Gtk::Menu_Helpers::MenuElem("_Quit", Gtk::Main::quit));

	return;
}