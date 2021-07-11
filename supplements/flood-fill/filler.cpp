/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace.
 *
 */

/**
 * Performs a multi-point flood fill using breadth first search.
 *
 * @param config      FillerConfig struct to setup the fill
 * @return animation  object illustrating progression of flood fill algorithm
 */
animation filler::fillBFS(FillerConfig &config)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill.
     */
    return fill<Queue>(config);
}

/**
 * Performs a multi-point flood fill using depth first search.
 *
 * @param config      FillerConfig struct to setup the fill
 * @return animation  object illustrating progression of flood fill algorithm
 */
animation filler::fillDFS(FillerConfig &config)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill.
     */
    return fill<Stack>(config);
}

bool filler::checkTolerance(HSLAPixel old_pixel, double tolerance, HSLAPixel* new_pixel){
    return old_pixel.dist(*new_pixel) <= tolerance;
}

void filler::sendFrame(int k, int frameFreq, animation& ai,PNG& img){
    if((k % frameFreq) == 0){
        ai.addFrame(img);
    }
}

/**
 * Run a multi-point flood fill on an image
 *
 * @param  config     FillerConfig struct with data for flood fill of image
 * @return animation  object illustrating progression of flood fill algorithm
 */
template <template <class T> class OrderingStructure> animation filler::fill(FillerConfig &config)
{
    animation ani;

    int k=0;

    int frameFreq = config.frameFreq;
    float tolerance = config.tolerance;
    PNG img = config.img;
    vector<centre> centres = config.centres;
    vector<ColorPicker *> pickers = config.pickers;
    bool done[img.width()][img.height()];
    for (int i=0; i<img.width(); ++i)
        for (int j=0; j<img.height(); ++j)
            done[i][j] = false;

    for (size_t i = 0; i < centres.size(); ++i) 
    {
        OrderingStructure<point> os;
        centre c = centres.at(i);
        ColorPicker *colorPicker = pickers.at(i);

        point start_point = point(c);

        HSLAPixel* first = img.getPixel(c.x, c.y);
        HSLAPixel unchangedfirst = *first;
        *first = (*colorPicker)(start_point);

        
        if(c.x < img.width() && c.y < img.height())
        {
            done[c.x][c.y] = true;
            os.add(start_point);
            k++;
            sendFrame(k, frameFreq, ani, img);
        }

        while(!os.isEmpty())
        {

            point removepixelxy;
            
            removepixelxy = os.remove();
 

            HSLAPixel* up = img.getPixel(removepixelxy.x, removepixelxy.y ? removepixelxy.y-1 : removepixelxy.y);

            point vup = point(removepixelxy.x, removepixelxy.y ? removepixelxy.y-1 : removepixelxy.y, c);

            
            HSLAPixel* left = img.getPixel(removepixelxy.x ? removepixelxy.x-1 : removepixelxy.x, removepixelxy.y);

            point vleft = point(removepixelxy.x ? removepixelxy.x-1 : removepixelxy.x, removepixelxy.y, c);
            
            HSLAPixel* down = img.getPixel(removepixelxy.x, removepixelxy.y+1 >= img.height() ? removepixelxy.y : removepixelxy.y + 1);

            point vdown = point(removepixelxy.x, removepixelxy.y+1 >= img.height() ? removepixelxy.y : removepixelxy.y + 1, c);
            
            HSLAPixel* right = img.getPixel(removepixelxy.x+1 >= img.width() ? removepixelxy.x : removepixelxy.x+1, removepixelxy.y);

            point vright = point(removepixelxy.x+1 >= img.width() ? removepixelxy.x : removepixelxy.x+1, removepixelxy.y, c);

            if(checkTolerance(unchangedfirst,tolerance,up) && !(done[vup.x][vup.y])){
                if(vup.x < img.width() && vup.y < img.height()){
                    *up = (*colorPicker)(vup);
                    os.add(vup);
                    done[vup.x][vup.y] = true;
                    k++;
                    sendFrame(k,frameFreq,ani,img);
                }
            }

            if(checkTolerance(unchangedfirst,tolerance,right) && !(done[vright.x][vright.y])){
                if(vright.x < img.width() && vright.y < img.height()){
                    *right = (*colorPicker)(vright);
                    os.add(vright);
                    done[vright.x][vright.y] = true;
                    k++;
                    sendFrame(k,frameFreq,ani,img);
                }
            }

            if(checkTolerance(unchangedfirst,tolerance,down) && !(done[vdown.x][vdown.y])){
                if(vdown.x < img.width() && vdown.y < img.height()){
                    *down =  (*colorPicker)(vdown);
                    os.add(vdown);
                    done[vdown.x][vdown.y] = true;
                    k++;
                    sendFrame(k,frameFreq,ani,img);
                }
            }

            if(checkTolerance(unchangedfirst,tolerance,left) && !(done[vleft.x][vleft.y])){
                if(vleft.x < img.width() && vleft.y < img.height()){
                    *left = (*colorPicker)(vleft);
                    os.add(vleft);
                    done[vleft.x][vleft.y] = true;
                    k++;
                    sendFrame(k,frameFreq,ani,img);
                }
            }

        }

    }
    ani.addFrame(img);
    return ani;
    /**
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. To begin the algorithm, you simply place the
     * given point in the ordering structure, marking it processed
     * (the way you mark it is a design decision you'll make yourself).
     * We have a choice to either change the color, if appropriate, when we
     * add the point to the OS, or when we take it off. In our test cases,
     * we have assumed that you will change the color when a point is added
     * to the structure.
     * Until the structure is empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure, and then...
     *
     *        1.    add its unprocessed neighbors whose color values are
     *              within (or equal to) tolerance distance from the center,
     *              to the ordering structure, and
     *              mark them as processed.
     *        2.    if it is an appropriate frame, send the current PNG to the
     *              animation (as described below).
     *
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! The order you should put
     *        neighboring pixels **ONTO** the queue or stack is as follows:
     *        ** UP(-y), RIGHT(+x), DOWN(+y), LEFT(-x). IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.** To reiterate, when you are exploring (filling out)
     *        from a given pixel, you must first try to fill the pixel UP
     *        from it, then the one to its RIGHT, then DOWN from it and
     *        finally to its LEFT. If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     *        Because we are doing a multi-point flood fill you will repeat the flood
     *        fill from several locations stored in the `centres` variable of FillerConfig
     *        struct. Initial fill points should be visited in the order they stored in the
     *        `centres` vector. If a pixel lies in the fill region of multiple start points,
     *        it should only be updated by the first fill. To repeat, pixels should only
     *        be modified the first time they are visited by the filler algorithm.
     *
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     *
     * 4.     Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and
     *        it will be the one we test against.
     *
     */
}
