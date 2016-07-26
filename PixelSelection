
#include "stdlib.h"
#include "iostream"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void salt(Mat &image,int n);
void colorReduce(Mat &image,int div);

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
	
	//Note: to take effect on a different image, use Mat imageC = image.clone()
	colorReduce(image,64);

	imshow("image",image);
	waitKey(0);

	return 0;
}

//function to add random white pixels to the image
void salt(Mat &image,int n){
	for(int i=0;i<n;i++){
		int j =rand()%image.cols;
		int k =rand()%image.rows;
		//check channel, if gray
		if(image.channels() ==1)
			image.at<uchar>(k,j)=255;
		//For color images, channels = 3. So we need a tuple Vec3b to store 3 numbers BGR.	
		//Mat can store elements of any datatype, so it is necessary to specify element's data type <Vec3b> when selecting pixels.
		if(image.channels()==3)
			image.at<Vec3b>(k,j)[0]=255;
			image.at<Vec3b>(k,j)[1]=255;
			image.at<Vec3b>(k,j)[2]=255;
	}
}

void colorReduce(Mat &image,int div){
	int row = image.rows;
	//num of data per row
	int numData = image.cols*image.channels();
	for(int i=0;i<row;i++){
		//for each data, divide by div then multiply div to truncate some numbers to reduce number of different colors 
		//return the first address of the row i
		uchar* data = image.ptr<uchar>(i);
		for(int j=0;j<numData;j++){
		data[j] = data[j]/div*div;
		}
	}
}
