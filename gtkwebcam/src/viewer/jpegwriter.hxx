#include <fstream>

using namespace std;

extern "C"
{
	#include <jpeglib.h>
	#include <jerror.h>

	const unsigned short OUTPUT_BUF_SIZE = 4096;

	METHODDEF(void) init_destination(j_compress_ptr cinfo);
	METHODDEF(boolean) empty_output_buffer(j_compress_ptr cinfo);
	METHODDEF(void) term_destination(j_compress_ptr cinfo);
	GLOBAL(void) jpeg_stl_dest(j_compress_ptr cinfo, ofstream* outfile);
}

namespace ImageWriter
{

	class ImageWriter
	{
		protected:
			virtual bool find_filename() = 0;
			virtual void write(char* data, int x, int y) = 0;
		
			string _filename;
	};
	
	class JPEG : public ImageWriter
	{
		public:
			JPEG();
			~JPEG();
			void write(char* data, int x, int y, int quality);
	};
	
	class PNG : public ImageWriter
	{
		public:
			PNG();
			~PNG();
	};

} /* namespace ImageWriter */