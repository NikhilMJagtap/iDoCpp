#ifndef _POINT_H_
#define _POINT_H_

#include "centre.h"

/* Every point in the fill is associated with a location on the image,
 * and with a centre. The centre information is instantiated during the
 * fill. This is necessary because we need to pass centre color information
 * to the color picker.
 */

struct point
{
    unsigned int x;
    unsigned int y;

    centre c;

    point()
    {
        c = centre();
        x = 0;
        y = 0;
    }

    point(centre ctr)
    {
        c = ctr;
        x = ctr.x;
        y = ctr.y;
    }

    point(int newx, int newy, centre ctr)
    {
        c = ctr;
        x = newx;
        y = newy;
    }
};

#endif
