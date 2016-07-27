
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

int main (int argc,char** argv){


	Mat image = imread("12.jpg");
	if(!image.data)return -1;

	Mat result(image.rows,image.cols,CV_8UC1);
	//image.copyTo(result);
	
	Vec3b vec=Vec3b(255,0,0);
	
	findColor(image,result,vec);
	int midPoint[2];
	findEndPoints(result, midPoint);
	result.at<uchar>(midPoint[0],midPoint[1]) = 255;
	cout<<midPoint[0]<<endl<<midPoint[1]<<endl;

	Mat mix(image.rows,image.cols,CV_8UC3);
	vector<Mat> planes;
	split(image,planes);
	planes[0]+=result;
	merge(planes,image);
	

	namedWindow("image");
	//threshold(result,result,128,255,THRESH_BINARY_INV);
	imshow("image",image);
	waitKey(0);

	return 0;
}
 
void findColor(const Mat &image,Mat &result, Vec3b &target){
	

	for(int i=0;i<image.rows;i++){
		for(int j=0;j<image.cols;j++){
			if(findDis(image.at<Vec3b>(i,j), target)<200){
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
	int count=0, w=0, h=0;
	
	for(int i=0;i<image.rows;i++){
		for(int j=0;j<image.cols;j++){
			if(image.at<uchar>(i,j)==255){
				count++;
				w+=i;
				h+=j;
			}
		}
	}

	result[0] = w/count;
	result[1] = h/count;

}

