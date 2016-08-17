#include<iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <stdio.h>

using namespace std;
using namespace cv;

Mat img;
Mat imgGray;
int thresh = 200;

void CHfunction(int, void *);

int main(void){

    img = imread("/home/richard/Desktop/toys/160.jpg");
    cvtColor(img,imgGray,CV_BGR2GRAY);

    namedWindow("window",2);

    createTrackbar("Threshold: ","window",&thresh, 255, CHfunction);
    imshow("window",img);

    CHfunction(0,0);
    waitKey(0);
    return 0;

}

void CHfunction(int,void*){
    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.04;

    Mat result;

    cornerHarris(imgGray,result, blockSize,apertureSize,k,BORDER_DEFAULT);
    Mat resultNorm;
    normalize(result,resultNorm,0,255,NORM_MINMAX,CV_32FC1,Mat());
    Mat resultScaled;
    convertScaleAbs(resultNorm,resultScaled);

    for( int j = 0; j < resultNorm.rows ; j++ )
        { for( int i = 0; i < resultNorm.cols; i++ )
             {
               if( (int) resultNorm.at<float>(j,i) > thresh )
                 {
                  circle( resultScaled, Point( i, j ), 5,  Scalar(0), 2, 8, 0 );
                 }
             }
        }

    namedWindow("Nwindow",2);
    imshow("Nwindow",resultScaled);

}

