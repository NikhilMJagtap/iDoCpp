#ifndef _CENTRE_H_
#define _CENTRE_H_

#include "cs221util/HSLAPixel.h"

using namespace cs221util;

/* A collection of centres is used to initiate the fill.
 *
 * A centre consists of a location on an image, together with a color.
 */
struct centre
{
    int x;
    int y;
    HSLAPixel color;

    centre(int x, int y, HSLAPixel color)
    {
        this->x = x;
        this->y = y;
        this->color = color;
    }

    centre()
    {
        x = 0;
        y = 0;
        color = HSLAPixel(240, 1., 0.5);
    } // default color is blue
};

#endif
