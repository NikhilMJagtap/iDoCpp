/**
 * @file negativeColorPicker.h
 * Definition of a negative color picker.
 *
 */
#ifndef _NEGATIVECOLORPICKER_H_
#define _NEGATIVECOLORPICKER_H_

#include <cmath>

#include "cs221util/HSLAPixel.h"

#include "colorPicker.h"
#include "point.h"

using namespace std;

/**
 * NegativeColorPicker: a functor that determines the color that should be used
 * given a point containing both an x and a y coordinate.
 * The final hue and luminance of the (x, y) point has inverted hue and luminance
 * values of the (x, y) point of the original image.
 *
 */
class NegativeColorPicker : public ColorPicker
{
  public:
    /**
     * Constructs a new NegativeColorPicker.
     */
    NegativeColorPicker(PNG& inputimg);

    /**
     * Picks the color for pixel (x, y), which is a member of point p.
     * The new color consists of components h, s, and l.
     * The saturation s is unchanged from the original color.
     * 
     * The hue and luminance are inverted from the original image. Refer to HSLA documentation
     * to determine an "appropriate" meaning for hue/luminance inversion/negation.
     * 
     * @return    The color chosen for (p).
     */
    virtual HSLAPixel operator()(point p);

  private:
    PNG img;                  // Original image used in flood fill algorithm
};

#endif
