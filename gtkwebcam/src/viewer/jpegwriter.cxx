#include "jpegwriter.hxx"

extern "C"
{

typedef struct
{
	struct jpeg_destination_mgr pub;
	ofstream* outfile;
	JOCTET* buffer;
} stl_destmgr;

typedef stl_destmgr* stl_destptr;


METHODDEF(void) init_destination(j_compress_ptr cinfo)
{
	stl_destptr dest = (stl_destptr)cinfo->dest;

	dest->buffer = new JOCTET[OUTPUT_BUF_SIZE];

	dest->pub.next_output_byte = dest->buffer;
	dest->pub.free_in_buffer = OUTPUT_BUF_SIZE;

	return;
}


METHODDEF(boolean) empty_output_buffer(j_compress_ptr cinfo)
{
  stl_destptr dest = (stl_destptr)cinfo->dest;

  dest->outfile->write(reinterpret_cast<const char *>(dest->buffer), OUTPUT_BUF_SIZE); //FIXME: error checking

  dest->pub.next_output_byte = dest->buffer;
  dest->pub.free_in_buffer = OUTPUT_BUF_SIZE;

  return TRUE;
}


METHODDEF(void) term_destination(j_compress_ptr cinfo)
{
	stl_destptr dest = (stl_destptr)cinfo->dest;
	size_t datacount = OUTPUT_BUF_SIZE - dest->pub.free_in_buffer;

	if (datacount > 0)
	{
		dest->outfile->write(reinterpret_cast<const char *>(dest->buffer), datacount); //FIXME: error checking
	}
	//dest->outfile->sync();

	//FIXME: error checking

	return;
}


GLOBAL(void) jpeg_stl_dest(j_compress_ptr cinfo, ofstream* outfile)
{
	stl_destptr dest;

	if (cinfo->dest == NULL)
	{
		cinfo->dest = reinterpret_cast<jpeg_destination_mgr *>(new stl_destmgr);
	}

	dest = (stl_destptr)cinfo->dest;
	dest->pub.init_destination = init_destination;
	dest->pub.empty_output_buffer = empty_output_buffer;
	dest->pub.term_destination = term_destination;
	dest->outfile = outfile;

	return;
}

} /* extern "C" */

void ImageWriter::JPEG::write()
{

	unsigned short output_format = 0; //jpeg
	string filename = "snapshot.jpg";
	/*struct stat s;
	unsigned int i = 1;

	// first of all find an apt filename
	while (stat((filename.replace("%n", itos(i))).c_str, &s) == 0)
	{
		cout << "tried filename " << filename.replace("%n", itos(i)) << "..." << endl ;
		i++;
	}
	cout << "ok, using this filename." << endl ;*/

	ofstream out;

	out.open(filename.c_str(), ios::out);
	if (!out.is_open())
	{
		cout << "unable to open file." << endl ;
		return;
	}

	char* _buf24s = reinterpret_cast<char*>(_view._buf24);

	int quality = 75; //FIXME
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	JSAMPROW row_pointer[1];
	int row_stride;

	cinfo.err = jpeg_std_error(&jerr);

	jpeg_create_compress(&cinfo);

	jpeg_stl_dest(&cinfo, &out);

	cinfo.image_width = _view._vwin.width;
	cinfo.image_height = _view._vwin.height;
	cinfo.input_components = 3;
	cinfo.in_color_space = JCS_RGB;

	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values );

	jpeg_start_compress(&cinfo, TRUE);
	row_stride = cinfo.image_width * 3;

	while (cinfo.next_scanline < cinfo.image_height)
	{
		row_pointer[0] = reinterpret_cast<JSAMPLE *>(&_buf24s[cinfo.next_scanline * row_stride]);
		jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);

	out.close();

	cout << "image saved." << endl ;

	return;
}
