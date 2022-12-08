#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <"utils.h">

using namespace cv;
using namespace std;

// template <typename T>
// struct Point{
//     T x;
//     T y;
// };


Mat hsvTransform(Mat& original){
    Mat imageHSV, maskHSV, resultHSV, gray, blurImage, edge;
    cvtColor(original, imageHSV, COLOR_BGR2HSV);
    // Mat channels;
    // split(img, channels)
	Scalar minHSV, maxHSV;
    minHSV = Scalar(0, 0, 120);
	maxHSV = Scalar(33, 41, 255);

    inRange(imageHSV, minHSV, maxHSV, maskHSV);
    resultHSV = Mat::zeros(original.rows, original.cols, CV_8UC3);
    bitwise_and(original, original, resultHSV, maskHSV);

    

    // edge detection
    int edgeThresh1{10}, edgeThresh2{223};
    cvtColor(resultHSV, gray, COLOR_BGR2GRAY);
    blur(gray, blurImage, Size(7,7));
    // Run the edge detector on grayscale
    Canny(blurImage, edge, edgeThresh1, edgeThresh2, 3);
    imshow("SelectHSV", imageHSV);
    waitKey(0);
    imshow("SelectHSV", edge);
    
    waitKey(0);
    return edge;
}

vector<Vec4i> drawLines(Mat& dst, vector<Vec4i>& lines){
    vector<Vec4i> new_lines;
    return new_lines;
}


vector<Vec4i>  houghTransform(Mat& original, Mat& dst, const int rho = 3, const int deg = 1, const int thres=40, const int min_line_len=300, const int max_gap=50){
    vector<Vec4i> lines;
    HoughLinesP(dst, lines, rho, (deg*CV_PI)/180, thres, min_line_len, max_gap);
    for( size_t i = 0; i < lines.size(); i++ )
    {
        line(original, Point(lines[i][0], lines[i][1]),
        Point( lines[i][2], lines[i][3]), Scalar(255,0,0), 3, 20 );
    }
    imshow( "Detected Lines", original );
    waitKey(0);

    return lines;
}

void weightedImg(){

}

void getAdjustment(Mat& image){
}
 

int main()
{   
    Mat original = imread("/Users/siddharthdas/cv_works/sw5.jpeg");
    Mat img;
    img = hsvTransform(original);
    houghTransform(original, img);
    return 0;
}