
#include "stdlib.h"
#include "iostream"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int findDis(Vec3b color, Vec3b target);
void findColor(const Mat &image,Mat &result, Vec3b &target);

int main (int argc,char** argv){


	Mat image = imread("tama1.png");
	if(!image.data)return -1;

	Mat result;
	image.copyTo(result);
	Vec3b vec=Vec3b(0,0,200);


	findColor(image,result,vec);

	namedWindow("image");
	imshow("image",result);
	waitKey(0);

	return 0;
}

void findColor(const Mat &image,Mat &result, Vec3b &target){
	

	for(int i=0;i<image.rows;i++){
		for(int j=0;j<image.cols;j++){
			if(findDis(image.at<Vec3b>(i,j), target)<180){
				result.at<Vec3b>(i,j)[0]=0;
				result.at<Vec3b>(i,j)[1]=0;
				result.at<Vec3b>(i,j)[2]=0;
			}else{
				result.at<Vec3b>(i,j)[0]=255;
				result.at<Vec3b>(i,j)[1]=255;
				result.at<Vec3b>(i,j)[2]=255;
			}
		}
	}
}

int findDis(Vec3b color, Vec3b target){
	return abs(color[0]-target[0])+abs(color[1]-target[1])+abs(color[2]-target[2]);
}
