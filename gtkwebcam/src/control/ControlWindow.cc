#ifdef HAVE_CONFIG_H
#	include "config.h"
#endif

#include "ControlWindow.hh"


ControlWindow::ControlWindow()
{
	return;
}

/*void ControlWindow::do_update()
{


	while(1)
	{
		usleep(1000000 / 20);
		{
			_view.update(true);
		}
	}

	return;
}*/

void ControlWindow::on_menu_resolution_preview_changed()
{

	std::vector <struct video_window> resolutions;
	struct video_window res;

	res.width = 128; res.height = 96;
	resolutions.push_back(res);
	res.width = 160; res.height = 120;
	resolutions.push_back(res);
	res.width = 176; res.height = 144;
	resolutions.push_back(res);
	res.width = 320; res.height = 240;
	resolutions.push_back(res);
	res.width = 352; res.height = 288;
	resolutions.push_back(res);
	res.width = 640; res.height = 480;
	resolutions.push_back(res);

	std::cout << "getting choice..." << std::endl ;
	int choice = this->menu_resolution_preview->get_history();

	std::cout << "new resolution is " << choice << "(" << resolutions[choice].width << "x" << resolutions[choice].height << ")" << std::endl ;

	_vwin.width = resolutions[choice].width;
	_vwin.height = resolutions[choice].height;

	ioctl(_camfd, VIDIOCSWIN, &_vwin);
	ioctl(_camfd, VIDIOCGWIN, &_vwin);

	return;
}


void ControlWindow::on_menu_resolution_snapshot_changed()
{

}

void ControlWindow::cb_save_user_settings()
{
}

void ControlWindow::cb_restore_user_settings()
{
}

void ControlWindow::cb_restore_factory_defaults()
{
}

void ControlWindow::gtk_main_quit()
{
	Gtk::Main::quit();

	return;
}

void ControlWindow::on_compression_level_none_activate()
{
	return;
	ioctl(_camfd, VIDIOCPWCSCQUAL, 0);

	return;
}

void ControlWindow::on_compression_level_low_activate()
{
	ioctl(_camfd, VIDIOCPWCSCQUAL, 1);

	return;
}

void ControlWindow::on_compression_level_medium_activate()
{
	ioctl(_camfd, VIDIOCPWCSCQUAL, 2);

	return;
}

void ControlWindow::on_compression_level_high_activate()
{
	ioctl(_camfd, VIDIOCPWCSCQUAL, 3);

	return;
}


void ControlWindow::on_brightness_changed()
{
	struct video_picture vpic;

	ioctl(_camfd, VIDIOCGPICT, &vpic);

	cout << "current brightness value is " << vpic.brightness << endl ;

	cout << "setting brightness to " << static_cast<int>(this->brightness->get_value()) << endl ;

	vpic.brightness = static_cast<int>(this->brightness->get_value());

	ioctl(_camfd, VIDIOCSPICT, &vpic);

	return;
}

void ControlWindow::on_contrast_changed()
{
}

void ControlWindow::on_color_changed()
{
}

void ControlWindow::on_hue_changed()
{
}

void ControlWindow::on_gamma_changed()
{
}

void ControlWindow::on_backlightcomp_toggled()
{
	ioctl(_camfd, VIDIOCPWCSBACKLIGHT, (dynamic_cast<ControlWindow_glade *>(this)->backlightcompensation->get_active() == true));

	return;
}

void ControlWindow::on_flickercomp_toggled()
{
	ioctl(_camfd, VIDIOCPWCSFLICKER, (dynamic_cast<ControlWindow_glade *>(this)->flickercompensation->get_active() == true));

	return;
}

void ControlWindow::on_dynnoise_none_activate()
{
	ioctl(_camfd, VIDIOCPWCSDYNNOISE, 0);

	return;
}

void ControlWindow::on_dynnoise_low_activate()
{
	ioctl(_camfd, VIDIOCPWCSDYNNOISE, 1);

	return;
}

void ControlWindow::on_dynnoise_medium_activate()
{
	ioctl(_camfd, VIDIOCPWCSDYNNOISE, 2);

	return;
}

void ControlWindow::on_dynnoise_high_activate()
{
	ioctl(_camfd, VIDIOCPWCSDYNNOISE, 3);

	return;
}


void ControlWindow::on_50p_activate()
{
}

void ControlWindow::on_100p_activate()
{
}

void ControlWindow::on_200p_activate()
{
}
