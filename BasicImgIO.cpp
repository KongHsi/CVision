#include "stdlib.h"
#include "iostream"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main (int argc,char** argv){

	/*
	Mat is the basic data structure to store matrix data such as images.
	It by default to be initialized to the size of 0, but we can also determine it.
	cv::Mat ima(240,320,CV_8U,cv::Scalar(100);
	CV_8U represents 8 bits unsigned data. For colored images, we need CV_8UC3. 3 for three colors. 
	Note: like many objects, assign one obj to another variable only assign the reference. To get a complete new copy, use img.copyTo(Mat imgNew).
	*/



	//initialize an image
	cv::Mat image;
	cout<<"Image height: "<<image.size().height <<" Image width: "<< image.size().width<<endl;
	//read an img to Mat image
	image = imread("tama1.png");
	if(!image.data)return -1;//return -1 if it can't be opened

	//initialize a new window
	namedWindow("image");
	//flip img to a new Mat. 1 for horizontal flip, 0 for verticle and -1 for both.
	Mat flipImg;
	flip(image,flipImg,-1);
	//show flipImg to the opened window 
	imshow("image",flipImg);

  	imwrite("out.png",flipImg);
	//wait until user press a key
	waitKey(0);
	
	return 0;
}
