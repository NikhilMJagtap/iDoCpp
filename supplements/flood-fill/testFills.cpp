#define CATCH_CONFIG_MAIN

#include <iostream>
#include <limits.h>
#include <sys/stat.h>
#include <vector>

#include "cs221util/HSLAPixel.h"
#include "cs221util/PNG.h"
#include "cs221util/catch.hpp"

#include "centre.h"
#include "filler.h"
#include "point.h"
#include "solidColorPicker.h"
#include "negativeColorPicker.h"
#include "mosaicColorPicker.h"
#include "softBorderColorPicker.h"

using namespace std;
using namespace cs221util;

// Whether to write solutions images or test
#define WRITESOLNIMAGES 0

#define IMAGEDIR "images/"
#define SOLNIMGDIR "soln_images/"

// use the following for color picker tests
#define FUNCTORTESTHEIGHT 64
#define FUNCTORTESTWIDTH 64
#define FUNCTORTESTIMAGE_G "originals/gradient-64x64.png"
#define FUNCTORTESTIMAGE_GL "originals/gradient_lines-64x64.png"

#define NEGATIVEX1 107
#define NEGATIVEY1 16
#define NEGATIVEX2 155
#define NEGATIVEY2 113
#define NEGATIVETOLERANCE 0.05
#define NEGATIVETESTIMAGE "originals/smw-240x125.png"
#define NEGATIVEFRAMEFREQ 200

#define MOSAICX1 87
#define MOSAICY1 107
#define MOSAICX2 171
#define MOSAICY2 131
#define MOSAICTOLERANCE 0.03
#define MOSAICWIDTH 10
#define MOSAICTESTIMAGE "originals/bdc-280x187.png"
#define MOSAICFRAMEFREQ 400

#define SOFTBORDERX 25
#define SOFTBORDERY 35
#define SOFTBORDERTOLERANCE 0.05
#define SOFTBORDERTESTIMAGE "originals/smw-240x125.png"
#define SOFTBORDERFRAMEFREQ 160
#define SOFTBORDERWIDTH 5

#define SOLIDX1 70
#define SOLIDY1 36
#define SOLIDX2 228
#define SOLIDY2 36
#define SOLIDX3 387
#define SOLIDY3 36
#define SOLIDTOLERANCE 0.015
#define SOLIDTESTIMAGE "originals/brain-476x202.png"
#define SOLIDFRAMEFREQ 480

centre getcentre(PNG &img, int x, int y)
{
    return centre(x, y, (*img.getPixel(x, y)));
}

void deleteConfig(filler::FillerConfig &config)
{
    for (size_t i = 0; i < config.pickers.size(); i++)
    {
        delete config.pickers[i];
    }
}

filler::FillerConfig setupSolidConfig()
{
    filler::FillerConfig config;
    config.img.readFromFile(SOLIDTESTIMAGE);
    config.frameFreq = SOLIDFRAMEFREQ;
    config.tolerance = SOLIDTOLERANCE;

    config.centres.push_back(getcentre(config.img, SOLIDX1, SOLIDY1));
    config.centres.push_back(getcentre(config.img, SOLIDX2, SOLIDY2));
    config.centres.push_back(getcentre(config.img, SOLIDX3, SOLIDY3));

    HSLAPixel fillColor(110, 0.9, 0.5);

    config.pickers.push_back(new SolidColorPicker(fillColor));
    config.pickers.push_back(new SolidColorPicker(fillColor));
    config.pickers.push_back(new SolidColorPicker(fillColor));

    return config;
}

void testOrWriteFill(animation anim, string base_name)
{
    PNG result = anim.write(IMAGEDIR + base_name + ".gif");

    if (WRITESOLNIMAGES == 1)
    {
        result.writeToFile(IMAGEDIR + base_name + ".png");
    }
    else
    {
        PNG expected;
        expected.readFromFile(SOLNIMGDIR + base_name + ".png");
        REQUIRE(result == expected);
    }
}

PNG testColorPicker(PNG &img, ColorPicker &picker)
{
    int x = FUNCTORTESTWIDTH / 2;
    int y = FUNCTORTESTHEIGHT / 2;
    centre ctr = getcentre(img, x, y);
    HSLAPixel px;

    for (int x = 1; x < FUNCTORTESTWIDTH; x = x + x)
    {
        for (int y = 1; y < FUNCTORTESTHEIGHT; y = y + y)
        {
            point p(x, y, ctr);
            px = picker(p);
            // these create the output useful for debugging fills
            cout << "\toperator()(" << x << ", " << y << ") = {" << px.h << ", " << px.s << ", " << px.l << "}" << endl;
        }
    }

    for (int x = 0; x < FUNCTORTESTWIDTH; x++)
    {
        for (int y = 0; y < FUNCTORTESTHEIGHT; y++)
        {
            point newpoint(x, y, ctr);
            HSLAPixel *p = img.getPixel(x, y);
            *p = picker(newpoint);
        }
    }

    return img;
}

void testOrWriteColorPicker(PNG &img, ColorPicker &picker, string base_name)
{
    PNG result = testColorPicker(img, picker);
    if (WRITESOLNIMAGES == 1)
    {
        result.writeToFile(IMAGEDIR + base_name + ".png");
    }
    else
    {
        PNG expected;
        expected.readFromFile(SOLNIMGDIR + base_name + ".png");
        REQUIRE(result == expected);
    }
}

/**
 * Test Cases
 */

TEST_CASE("colorPicker::basic solid", "[weight=0][part=colorPicker]")
{
    PNG img;
    img.readFromFile(FUNCTORTESTIMAGE_GL);
    SolidColorPicker picker(HSLAPixel(120, 0.4, 0.8));
    testOrWriteColorPicker(img, picker, "SolidColorPickerTest");
}

TEST_CASE("ColorPicker::basic negative", "[weight=1][part=colorPicker]")
{
    PNG img;
    img.readFromFile(FUNCTORTESTIMAGE_GL);
    NegativeColorPicker picker(img);
    testOrWriteColorPicker(img, picker, "NegativeColorPickerTest");
}

TEST_CASE("colorPicker::basic mosaic", "[weight=1][part=colorPicker]")
{
    PNG img;
    img.readFromFile(FUNCTORTESTIMAGE_GL);
    MosaicColorPicker picker(5, img);
    testOrWriteColorPicker(img, picker, "MosaicColorPickerTest");
}

TEST_CASE("colorPicker::basic soft border", "[weight=1][part=colorPicker]")
{
  PNG img;
  img.readFromFile(FUNCTORTESTIMAGE_GL);
  SoftBorderColorPicker picker(5, img, 0.01);
  testOrWriteColorPicker(img, picker, "SoftBorderColorPickerTest");
}

TEST_CASE("fill::solid bfs", "[weight=0][part=fill]")
{

    filler::FillerConfig config = setupSolidConfig();

    animation anim = filler::fillBFS(config);

    testOrWriteFill(anim, "bfs_solid");

    deleteConfig(config);
}

TEST_CASE("fill::solid dfs", "[weight=0][part=fill]")
{

    filler::FillerConfig config = setupSolidConfig();

    animation anim = filler::fillDFS(config);

    testOrWriteFill(anim, "dfs_solid");

    deleteConfig(config);
}

TEST_CASE("fill::negative bfs", "[weight=1][part=fill]")
{

    HSLAPixel fillColor(320.0, 0.8, 0.5);

    filler::FillerConfig config;
    config.img.readFromFile(NEGATIVETESTIMAGE);
    config.frameFreq = NEGATIVEFRAMEFREQ;
    config.tolerance = NEGATIVETOLERANCE;
    config.centres.push_back(getcentre(config.img, NEGATIVEX1, NEGATIVEY1));
    config.centres.push_back(getcentre(config.img, NEGATIVEX2, NEGATIVEY2));
    config.pickers.push_back(new NegativeColorPicker(config.img));
    config.pickers.push_back(new NegativeColorPicker(config.img));

    animation anim = filler::fillBFS(config);

    testOrWriteFill(anim, "bfs_negative");

    deleteConfig(config);
}

TEST_CASE("fill::negative dfs", "[weight=1][part=fill]")
{

    HSLAPixel fillColor(320.0, 0.8, 0.5);

    filler::FillerConfig config;
    config.img.readFromFile(NEGATIVETESTIMAGE);
    config.frameFreq = NEGATIVEFRAMEFREQ;
    config.tolerance = NEGATIVETOLERANCE;
    config.centres.push_back(getcentre(config.img, NEGATIVEX1, NEGATIVEY1));
    config.centres.push_back(getcentre(config.img, NEGATIVEX2, NEGATIVEY2));
    config.pickers.push_back(new NegativeColorPicker(config.img));
    config.pickers.push_back(new NegativeColorPicker(config.img));

    animation anim = filler::fillDFS(config);

    testOrWriteFill(anim, "dfs_negative");

    deleteConfig(config);
}

TEST_CASE("fill::mosaic bfs", "[weight=1][part=fill]")
{

    filler::FillerConfig config;
    config.img.readFromFile(MOSAICTESTIMAGE);
    config.frameFreq = MOSAICFRAMEFREQ;
    config.tolerance = MOSAICTOLERANCE;
    config.centres.push_back(getcentre(config.img, MOSAICX1, MOSAICY1));
    config.centres.push_back(getcentre(config.img, MOSAICX2, MOSAICY2));
    config.pickers.push_back(new MosaicColorPicker(MOSAICWIDTH, config.img));
    config.pickers.push_back(new MosaicColorPicker(MOSAICWIDTH, config.img));

    animation anim = filler::fillBFS(config);

    testOrWriteFill(anim, "bfs_mosaic");

    deleteConfig(config);
}

TEST_CASE("fill::mosaic dfs", "[weight=1][part=fill]")
{

    filler::FillerConfig config;
    config.img.readFromFile(MOSAICTESTIMAGE);
    config.frameFreq = MOSAICFRAMEFREQ;
    config.tolerance = MOSAICTOLERANCE;
    config.centres.push_back(getcentre(config.img, MOSAICX1, MOSAICY1));
    config.centres.push_back(getcentre(config.img, MOSAICX2, MOSAICY2));
    config.pickers.push_back(new MosaicColorPicker(MOSAICWIDTH, config.img));
    config.pickers.push_back(new MosaicColorPicker(MOSAICWIDTH, config.img));

    animation anim = filler::fillDFS(config);

    testOrWriteFill(anim, "dfs_mosaic");

    deleteConfig(config);
}

TEST_CASE("fill::soft border bfs", "[weight=1][part=fill]")
{

  filler::FillerConfig config;
  config.img.readFromFile(SOFTBORDERTESTIMAGE);
  config.frameFreq = SOFTBORDERFRAMEFREQ;
  config.tolerance = SOFTBORDERTOLERANCE;
  config.centres.push_back(getcentre(config.img, SOFTBORDERX, SOFTBORDERY));
  config.pickers.push_back(new SoftBorderColorPicker(SOFTBORDERWIDTH, config.img, config.tolerance));

  animation anim = filler::fillBFS(config);

  testOrWriteFill(anim, "bfs_softborder");

  deleteConfig(config);
}

TEST_CASE("fill::soft border dfs", "[weight=1][part=fill]")
{

  filler::FillerConfig config;
  config.img.readFromFile(SOFTBORDERTESTIMAGE);
  config.frameFreq = SOFTBORDERFRAMEFREQ;
  config.tolerance = SOFTBORDERTOLERANCE;
  config.centres.push_back(getcentre(config.img, SOFTBORDERX, SOFTBORDERY));
  config.pickers.push_back(new SoftBorderColorPicker(SOFTBORDERWIDTH, config.img, config.tolerance));

  animation anim = filler::fillDFS(config);

  testOrWriteFill(anim, "dfs_softborder");

  deleteConfig(config);
}