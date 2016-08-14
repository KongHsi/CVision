#include "stdlib.h"
#include "iostream"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <algorithm>


using namespace std;
using namespace cv;



int main (int argc,char** argv){
	 
	Mat image = imread("1.jpg");
	if(!image.data)system("pause");

	vector<int> b;
	vector<int> g;
	vector<int> r;
	
	for(int i=0;i<image.rows;i++){
		for(int j=0;j<image.cols;j++){
			b.push_back(image.at<Vec3b>(i,j)[0]);
			g.push_back(image.at<Vec3b>(i,j)[1]);
			r.push_back(image.at<Vec3b>(i,j)[2]);
		}
	}
	sort(b.begin(),b.end());
	sort(g.begin(),g.end());
	sort(r.begin(),r.end());

	int bStart,bEnd,gStart,gEnd,rStart,rEnd;
	bStart = b.size()*0.05;
	bEnd = b.size() - b.size()*0.02;
	gStart = g.size()*0.05;
	gEnd = g.size() - g.size()*0.02;
	rStart = r.size()*0.05;
	rEnd = r.size() - r.size()*0.02;


	for(int i=0;i<image.rows;i++){
		for(int j=0;j<image.cols;j++){
			image.at<Vec3b>(i,j)[0] = (double)(image.at<Vec3b>(i,j)[0])*(i*j-bStart)/(bEnd-bStart)<0 ?0:(double)(image.at<Vec3b>(i,j)[0])*(i*j)/(bEnd-bStart);
			image.at<Vec3b>(i,j)[1] = (double)(image.at<Vec3b>(i,j)[1])*(i*j-gStart)/(gEnd-gStart)<0 ?0:(double)(image.at<Vec3b>(i,j)[1])*(i*j)/(gEnd-gStart);
			image.at<Vec3b>(i,j)[2] = (double)(image.at<Vec3b>(i,j)[2])*(i*j-rStart)/(rEnd-rStart)<0 ?0:(double)(image.at<Vec3b>(i,j)[2])*(i*j)/(rEnd-rStart);
		}
	}

	namedWindow("newImg",2);
	imshow("newImg",image);
	waitKey(0);

	system("pause");
	return 0;
}
 
