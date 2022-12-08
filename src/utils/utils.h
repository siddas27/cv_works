#if !defined(UTILS_H)
#define UTILS_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

void hsvTransform(Mat& );

vector<Vec4i> drawLines(Mat& dst, vector<Vec4i>& lines);

vector<Vec4i>  houghTransform(Mat& original, Mat& dst, const int rho = 3, const int deg = 1, const int thres=40, const int min_line_len=300, const int max_gap=50);

void weightedImg();

void getAdjustment(Mat& image);

#endif // UTILS_H
