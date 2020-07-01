#include <iostream>
#include<string>
#include<cmath>
#include<vector>
#include<algorithm>
#include "opencv2/opencv.hpp"

// operator for sorting contours, taken from OpenCV forum
struct contour_sorter // 'less' for contours
{
    bool operator ()(const std::vector<cv::Point> &a, const std::vector<cv::Point> &b)
    {
        cv::Rect ra(boundingRect(a));
        cv::Rect rb(boundingRect(b));
        return ((ra.x + 1000 * ra.y) < (rb.x + 1000 * rb.y));
    }
};


void show_image(cv::Mat, std::string);
void get_contours(cv::Mat, std::vector<std::vector<cv::Point> > &);
void draw_contour(cv::Mat &, std::vector<cv::Point>, double, double);
void calculate_scales(std::vector<cv::Point>, double &, double &);

int main(int argc, char** argv )
{
    std::string IMG_PATH = "./../../img.jpg";
    std::string WINDOW_NAME = "Window";
    double AREA_THRESHOLD = 150.0;
    double scaleX, scaleY;

    std::vector<std::vector<cv::Point> > contours;
    cv::Mat img;
    img = cv::imread(IMG_PATH, cv::IMREAD_COLOR);
    cv::Mat img_copy = img;
    // reading image
    if(!img.data)
    {
        std::cout << "Could not open the image!";
        return -1;
    }
    // preparing image for contours
    // converting 3 channel to single channel
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
    // using Gaussian Blur
    cv::GaussianBlur(img, img, cv::Size(5, 5), 0, 0);
    // using Canny edge detection
    cv::Canny(img, img, 0, 200);
    // getting contours
    get_contours(img, contours);
    // calculating length per pixels i.e scale values
    calculate_scales(contours[0], scaleX, scaleY);
    std::cout << scaleX << " " << scaleY;
    // drawing contours with area bigger than threshold
    for(int i=0; i<contours.size(); ++i)
        if(cv::contourArea(cv::Mat(contours.at(i))) > AREA_THRESHOLD)
            draw_contour(img_copy, contours.at(i), scaleX, scaleY); 
    show_image(img_copy, WINDOW_NAME);
    return 0;
}

void get_contours(cv::Mat img, std::vector<std::vector<cv::Point> >& contours)
{
    // img, contours array, external, chain approx simple
    cv::findContours(img, contours, 0, 2);
    // sorting the contours, left to right and top to bottom
    std::sort(contours.begin(), contours.end(), contour_sorter());
    return;
}

void show_image(cv::Mat image, std::string window_name)
{
    cv::namedWindow(window_name);
    cv::imshow(window_name, image);
    cv::waitKey(0);
    return;
}

void calculate_scales(std::vector<cv::Point> cnt, double &scaleX, double &scaleY)
{
    cv::RotatedRect rect = cv::minAreaRect(cnt);
    cv::Point2f vertices[4];
    rect.points(vertices);
    scaleX = sqrt(pow(vertices[0].x - vertices[3].x, 2) + pow(vertices[0].y - vertices[3].y, 2)) / 2;
    scaleY = sqrt(pow(vertices[2].x - vertices[3].x, 2) + pow(vertices[2].y - vertices[3].y, 2)) / 2;
    return;
}

void draw_contour(cv::Mat &img, std::vector<cv::Point> cnt, double scaleX, double scaleY)
{
    cv::RotatedRect rect = cv::minAreaRect(cnt);
    cv::Point2f vertices[4];
    rect.points(vertices);
    for (int i = 0; i < 4; i++)
        cv::line(img, vertices[i], vertices[(i+1)%4], cv::Scalar(0, 255, 0), 2);
    double lenX = sqrt(pow(vertices[0].x - vertices[3].x, 2) + pow(vertices[0].y - vertices[3].y, 2)) / scaleX;
    double lenY = sqrt(pow(vertices[2].x - vertices[3].x, 2) + pow(vertices[2].y - vertices[3].y, 2)) / scaleX;
    int hori_x = (vertices[0].x + vertices[3].x) / 2,
        hori_y = (vertices[0].y + vertices[3].y) / 2,
        vert_x = (vertices[2].x + vertices[3].x) / 2,
        vert_y = (vertices[2].y + vertices[3].y) / 2;
    std::string hori_len = std::to_string(lenX) + " cm";
    std::string vert_len = std::to_string(lenY) + " cm";
    cv::putText(img, hori_len, cv::Point(hori_x, hori_y+10), cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(0, 255, 0));
    cv::putText(img, vert_len, cv::Point(vert_x+10, vert_y), cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(0, 255, 0));
    return;
}