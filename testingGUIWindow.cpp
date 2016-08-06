#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;
using namespace cv;

void operation(int,void*);

Mat src;
int lightnesslvl =50;
int main(void){


  /// Load an image
 src = imread("1.jpg");
 if( !src.data ){ return -1; }

 /// Create window
 namedWindow("window", 2 );
 resizeWindow("window", 800, 600);

 /// Create Trackbar to select kernel type
 createTrackbar( "Lightness:\n 0-100", "window",
                 &lightnesslvl, 100,
                 operation);

	operation(0,0);
	waitKey(0);
 
}

void operation(int,void*){
	
	Mat temp = 0.01*lightnesslvl*src;
	imshow("window",temp);

}
