/**
 * @file softBorderColorPicker.h
 * Definition of a soft border color picker.
 *
 */
#ifndef _SOFTBORDERCOLORPICKER_H_
#define _SOFTBORDERCOLORPICKER_H_

#include "colorPicker.h"
#include "point.h"

/**
 * SoftBorderColorPicker: a functor that determines the color that should be used
 * given an `point`. If the given position is near a border of
 * the fill, then it should be colored with the required color. Otherwise, its color
 * should not change.
 *
 * The following criteria should be used to determine if a position p is near
 * a border: if p is within distance `borderwidth` of any cell that will be outside the
 * fill, then the pixel at position p should be colored with the average colour of
 * pixels of the original image within `borderwidth` pixels of p.
 *
 * You will use Euclidian distance to judge proximity. That means if p is at
 * location (x,y), its distance to a point at location (a,b) is
 * squareRoot([(x-a)^2 + (y-b)^2]). Note that you should not ever have to
 * compute the square root to solve this problem.
 *
 **/
class SoftBorderColorPicker : public ColorPicker
{
  public:
    /**
     * Constructs a new SoftBorderColorPicker.
     *
     * @param width  Number of pixels to color around border
     * @param inputimage   Image for referencing original image colors.
     * @param tol          Tolerance used to determine the border of the fill.
     */
    SoftBorderColorPicker(unsigned int width, PNG& inputimage, double tol);

    /**
     * Picks the color for pixel at point. If the x or y coordinate is
     * at or within an Euclidean radius of borderwidth pixels from the border of
     * the fill region, it will be colored with the average H/S/L/A values of
     * pixels within a radius of borderwidth pixels from (x, y).
     * Otherwise, its color will not be changed.
     *
     * @param p   The point for which you're picking a color.
     * @return    The color chosen for (p).
     */
    virtual HSLAPixel operator()(point);

  private:
    unsigned int borderwidth; // Number of pixels to use for border
    PNG img;                  // Original image used in flood fill algorithm
    double tolerance;         // Tolerance used in flood fill algorithm
};

#endif
