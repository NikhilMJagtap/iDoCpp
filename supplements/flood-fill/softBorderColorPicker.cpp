#include "softBorderColorPicker.h"
#include<cmath>

SoftBorderColorPicker::SoftBorderColorPicker(unsigned int width, PNG& inputimage, double tol)
{
    /* your code here */
    img = inputimage;
    tolerance = tol;
    borderwidth = width;
}

HSLAPixel SoftBorderColorPicker::operator()(point p)
{
    /* your code here */
    centre c = p.c;
    HSLAPixel *centerPixel = img.getPixel(c.x, c.y);
    HSLAPixel *currentPixel = img.getPixel(p.x, p.y);
    vector<HSLAPixel> pixels_on_border;
    vector<HSLAPixel> pixels_on_border_outside_fill;
    for (int i=0; i<img.width(); ++i) {
      for(int j=0; j<img.height(); ++j) {
        HSLAPixel *pixel = img.getPixel(i, j);
        if((i-p.x)*(i-p.x) + (j-p.y)*(j-p.y) <= borderwidth*borderwidth) {
          pixels_on_border.push_back(*pixel);
          if((i-c.x)*(i-c.x) + (j-c.y)*(j-c.y) > tolerance*tolerance) {
            pixels_on_border_outside_fill.push_back(*pixel);  
          }
        }
      }
    }
    if(pixels_on_border_outside_fill.size() == 0) {
      return *currentPixel;
    }
    double h=0.0, s=0.0, l=0.0, a=0.0;
    int count = 0;
    for(size_t i=0; i<pixels_on_border.size(); ++i) {
      h += pixels_on_border.at(i).h;
      s += pixels_on_border.at(i).s;
      l += pixels_on_border.at(i).l;
      a += pixels_on_border.at(i).a;
      count++;
    }
    return HSLAPixel(
      h/count,
      s/count,
      l/count,
      a/count
    );
}
