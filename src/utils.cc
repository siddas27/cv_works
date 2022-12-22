#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string>
// #include <"utils.h">

using namespace cv;
using namespace std;


Mat hsvTransform(Mat& original){
    Mat imageHSV, maskHSV, resultHSV, gray, blurImage, edge;
    cvtColor(original, imageHSV, COLOR_BGR2HSV);
    // int up_width = 640;
    // int up_height = 480;
    //resize up
    // resize(original, original, Size(up_width, up_height), INTER_LINEAR);
    // Mat channels;
    // split(img, channels)
	Scalar minHSV, maxHSV;
    minHSV = Scalar(0, 0, 90);
	maxHSV = Scalar(156, 64, 255);
    inRange(imageHSV, minHSV, maxHSV, maskHSV);
    resultHSV = Mat::zeros(original.rows, original.cols, CV_8UC3);
    bitwise_and(original, original, resultHSV, maskHSV);

    

    // edge detection
    int edgeThresh1{10}, edgeThresh2{223};
    cvtColor(resultHSV, gray, COLOR_BGR2GRAY);
    blur(gray, blurImage, Size(7,7));
    // Run the edge detector on grayscale
    Canny(blurImage, edge, edgeThresh1, edgeThresh2, 3);
    // imshow("SelectHSV", resultHSV);
    // waitKey(0);
    // imshow("SelectHSV", edge);
    
    // waitKey(0);
    return edge;
}

vector<Vec4i> drawLines(Mat& dst, vector<Vec4i>& lines){
    vector<Vec4i> new_lines;
    return new_lines;
}

double det(Point a, Point b){
    return a.x * b.y - a.y * b.x;
}
    

Point line_intersection(Point lp1, Point lp2, Point rp1, Point rp2){
    Point xdiff = Point(lp1.x - lp2.x, rp1.x - rp2.x);
    Point ydiff = Point(lp1.y - lp2.y, rp1.y - rp2.y);



    double div = det(xdiff, ydiff);
    if(div != 0.0){
        Point d = Point(det(lp1,lp2), det(rp1,rp2));
        double x = det(d, xdiff) / div;
        double y = det(d, ydiff) / div;
        return Point(x, y);
    }
    else{
        return Point (0,0);
    }   
}

vector<Vec4i>  houghTransform(Mat& original, Mat& dst, const int rho = 3, const int deg = 1, const int thres=30, const int min_line_len=100, const int max_gap=30){
    vector<Vec4i> lines;
    HoughLinesP(dst, lines, rho, (deg*CV_PI)/180, thres, min_line_len, max_gap);
    double right_slope = 0.3;
    Point lpt1, lpt2, rpt1,rpt2;
    double left_slope=-0.1;
    for( size_t i = 0; i < lines.size(); i++ )
    {
        Point pt1 = Point(lines[i][0], lines[i][1]);
        Point pt2 = Point(lines[i][2], lines[i][3]);
        double slope = double(pt1.y-pt2.y)/double(pt1.x-pt2.x);
        // std::fixed;
        std::setprecision(4);
        // cout<<slope<<endl;
        if(slope>0.31 && slope<4.0 && slope>right_slope ){
            right_slope =slope;
            rpt1=pt1; 
            rpt2=pt2;
            // line(original, pt1, pt2, Scalar(0,255,0), 3, 20 );
            
        } 
        if(slope>-3.0 && slope<-0.2 && slope<left_slope){
            left_slope =slope;
            lpt1=pt1; 
            lpt2=pt2;
            // line(original, pt1, Point(200,500), Scalar(0,0,255), 3, 20 );
        } 
    }

    Point intr = line_intersection(lpt1, lpt2, rpt1,rpt2);

    int lc = int(intr.y)-left_slope*int(intr.x);
    int rc = int(intr.y)-right_slope*int(intr.x);
    int lx = (480-lc)/left_slope;
    int rx = (480-rc)/right_slope;
    // lpt1.y<lpt2.y ? lpt1=intr:lpt2=intr;
    // rpt1.y<rpt2.y ? rpt1=intr:rpt2=intr;

    double a = left_slope+right_slope;
    double b=1-left_slope*right_slope;

    double s2 = a/(b-sqrt(pow(a,2)+pow(b,2)));
    int c = int(intr.y)-s2*int(intr.x);
    int x = (480-c)/s2;
    Point sw_center = Point(x,480);
    line(original, intr, sw_center, Scalar(255,255,0), 3, 20 );
    line(original, intr, Point(320,480), Scalar(0,255,255), 3, 20 );

    line(original, intr, Point(lx,480), Scalar(255,0,0), 3, 20 );
    line(original, intr, Point(rx,480), Scalar(255,0,0), 3, 20 );
    // imshow( "Detected Lines", original );
    // waitKey(0);

    return lines;
}



void weightedImg(){

}

void getAdjustment(Mat& image){
}

int video(int argc, char* argv[]){
    //Open the default video camera
    VideoCapture cap(0);
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);

    // if not success, exit program
    // if (cap.isOpened() == false){
    // cout << "Cannot open the video camera" << endl;
    // cin.get(CAP_PROP_FRAME_WIDTH); //wait for any key press
    // return -1;
    // } 

    // double dWidth = cap.get(CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    // double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    // cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;

    string window_name = "Camera";
    namedWindow(window_name); //create a window called "My Camera Feed"
    
    while (true){
        Mat frame, img;
        bool bSuccess = cap.read(frame); // read a new frame from video 

        //Breaking the while loop if the frames cannot be captured
        if (bSuccess == false) {
            cout << "Video camera is disconnected" << endl;
            cin.get(); //Wait for any key press
            break;
        }
        // else{
        //     cout << "Video camera is connected" << endl;
        // }
        // Mat original = imread("/Users/siddharthdas/cv_works/data/sw3.png");
        Mat original = frame;
        img = hsvTransform(original);
        houghTransform(original, img);
        //show the frame in the created window
        imshow(window_name, original);

        //wait for for 10 ms until any key is pressed.  
        //If the 'Esc' key is pressed, break the while loop.
        //If the any other key is pressed, continue the loop 
        //If any key is not pressed withing 10 ms, continue the loop 
        if (waitKey(10) == 27){
        cout << "Esc key is pressed by user. Stoppig the video" << endl;
        break;
        }
    }

    return 0;
 }

 int main(){
    Mat img;
    Mat original = imread("/Users/siddharthdas/cv_works/data/sw6.jpg");
    img = hsvTransform(original);
    houghTransform(original, img);
    //show the frame in the created window
    // imshow(window_name, original);
    imwrite("res6.jpeg", original);

 }