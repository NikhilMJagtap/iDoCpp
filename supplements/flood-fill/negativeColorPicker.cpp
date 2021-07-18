#include "negativeColorPicker.h"

NegativeColorPicker::NegativeColorPicker(PNG& inputimg)
{
  /* your code here */
  img = inputimg;
}

HSLAPixel NegativeColorPicker::operator()(point p)
{
  /* your code here */
  HSLAPixel *old = img.getPixel(p.x, p.y);
  return HSLAPixel(
    old->h > 180.0 ? old->h - 180.0 :  old->h + 180.0,
    old->s,
    1.0 - old->l,
    old->a
  );
}
