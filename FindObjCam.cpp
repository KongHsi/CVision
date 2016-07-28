#include "stdlib.h"
#include "iostream"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int findDis(Vec3b color, Vec3b target);
void findColor(const Mat &image,Mat &result, Vec3b &target);
void findEndPoints(const Mat &image, int* result);
void combineImgs(const Mat &image, Mat &result);
void erodeImg(Mat &image);
void dilateImg(Mat &image);

int main (int argc,char** argv){
	//Open the Camera
	VideoCapture cap(0);
	if(!cap.isOpened())return -1;

	for(;;){
		//a frame
		Mat image;
		cap>>image;
		if(image.empty())break;
		//new B/W img
		Mat result(image.rows,image.cols,CV_8UC1);
		image.copyTo(result);
		cvtColor(result,result, COLOR_BGR2GRAY);
		//Set desired color
		Vec3b vec=Vec3b(0,0,0);
		findColor(image,result,vec);
		//get rid of unwanted discrete pixels
		dilateImg(result);dilateImg(result);
		//add processed img with original img
		combineImgs(image,result);
		namedWindow("image",1);
		//find coordinators of the object
		int ptr[2]={0};
		findEndPoints(result,ptr);
		if(ptr[0] == 0 && ptr[1] ==0)
			cout<<"Not find"<<endl;
		else{
			cout<<"X: "<<ptr[0]<<" Y:"<<ptr[1]<<endl;
			cout<<"DX: "<<image.cols/2-ptr[0]<<" DY: "<<image.rows/2-ptr[1]<<endl;
		}

		imshow("image",image);
		waitKey(100);
	}
	return 0;
}
 
void findColor(const Mat &image,Mat &result, Vec3b &target){
	

	for(int i=0;i<image.rows;i++){
		for(int j=0;j<image.cols;j++){
			if(findDis(image.at<Vec3b>(i,j), target)<150){
				result.at<uchar>(i,j)=0;
				
			}else{
				result.at<uchar>(i,j)=255;
			}
		}
	}
}
int findDis(Vec3b color, Vec3b target){
	return abs(color[0]-target[0])+abs(color[1]-target[1])+abs(color[2]-target[2]);
}
void findEndPoints(const Mat &image, int* result){
	int count=0, x=0, y=0;
	
	for(int i=0;i<image.rows;i++){
		for(int j=0;j<image.cols;j++){
			if(image.at<uchar>(i,j)==0){
				count++;
				x+=j;
				y+=i;
			}
		}
	}
	if(count==0)return;
	result[0] = x/count;
	result[1] = y/count;

}
void combineImgs(const Mat &image, Mat &result){
	Mat mix(image.rows,image.cols,CV_8UC3);
	vector<Mat> planes;
	split(image,planes);
	planes[0]+=result*0.3;
	planes[1]+=result*0.3;
	planes[2]+=result*0.3;
	merge(planes,image);
}
void erodeImg(Mat &image){
	erode(image,image,Mat());
}
void dilateImg(Mat &image){
	dilate(image,image,Mat());
}
