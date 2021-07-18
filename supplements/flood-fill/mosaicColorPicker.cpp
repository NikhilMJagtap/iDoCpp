#include "mosaicColorPicker.h"

MosaicColorPicker::MosaicColorPicker(int mosaicwidth, PNG& inputimage)
{
  /* your code here */
  img = inputimage;
  width = mosaicwidth;
}

HSLAPixel MosaicColorPicker::operator()(point p)
{
  /* your code here */
  int block_no = p.x / width;
  int pixel_to_start_x = block_no * width;
  int block_no_y = p.y / width;
  int pixel_to_start_y = block_no_y * width;
  double h=0.0, s=0.0, l=0.0, a=0.0;
  int count = 0;
  for (int i = pixel_to_start_x; i<pixel_to_start_x + width && i < img.width(); ++i) {
    for(int j = pixel_to_start_y; j<pixel_to_start_y + width && j < img.height(); ++j) {
      h += img.getPixel(i, j)->h;
      s += img.getPixel(i, j)->s;
      l += img.getPixel(i, j)->l;
      a += img.getPixel(i, j)->a;
      count++;
    }
  }
  return HSLAPixel(
    h/count,
    s/count,
    l/count,
    a/count
  );
}
