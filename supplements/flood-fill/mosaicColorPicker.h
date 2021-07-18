/**
 * @file mosaicColorPicker.h
 * Definition of a mosaic color picker.
 *
 */
#ifndef _MOSAICCOLORPICKER_H_
#define _MOSAICCOLORPICKER_H_

#include "colorPicker.h"
#include "point.h"

/**
 * mosaicColorPicker: a functor that determines the color that should be used
 * given a point using a grid pattern.
 *
 */
class MosaicColorPicker : public ColorPicker
{
  public:
    /**
     * Constructs a new gridColorPicker.
     *
     * @param mosaicwidth    Width of each mosaic block in pixels.
     * @param inputimage     Original input image used to determine average color for a block
     */
    MosaicColorPicker(int mosaicwidth, PNG& inputimage);

    /**
     * Picks the color for pixel (x, y). The fill region is divided into
     * width x width square blocks, where the H/S/L/A values (x, y) will be
     * set as the average H/S/L/A values of all pixels in the block of the
     * original image where (x, y) resides.
     * Each square region has its upper left corner at a point where its
     * image coordinates are divisible by mosaicwidth.
     *
     * @param p   The point for which you're picking a color
     * @return    The color chosen for (p).
     */
    virtual HSLAPixel operator()(point p);

  private:
    int width;      // width of a mosaic block in pixels.
    PNG img;        // Original image used in flood fill algorithm
    PNG mosaicimg;  // full mosaic of the original image, computed once
};

#endif
