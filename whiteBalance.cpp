#include "stdlib.h"
#include "iostream"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <algorithm>


using namespace std;
using namespace cv;



int main (int argc,char** argv){
	 
	Mat image = imread("3.jpg");
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
	bStart = b[b.size()*0.02];
	bEnd = b[b.size() - b.size()*0.02];
	gStart = g[g.size()*0.02];
	gEnd = g[g.size() - g.size()*0.02];
	rStart = r[r.size()*0.02];
	rEnd = r[r.size() - r.size()*0.02];


	for(int i=0;i<image.rows;i++){
		for(int j=0;j<image.cols;j++){
			image.at<Vec3b>(i,j)[0] = (double)(image.at<Vec3b>(i,j)[0]-bStart)/(bEnd-bStart)*255<0 ?image.at<Vec3b>(i,j)[0]:(double)(image.at<Vec3b>(i,j)[0]-bStart)/(bEnd-bStart)*255;
			image.at<Vec3b>(i,j)[1] = (double)(image.at<Vec3b>(i,j)[1]-gStart)/(gEnd-gStart)*255<0 ?image.at<Vec3b>(i,j)[1]:(double)(image.at<Vec3b>(i,j)[1]-gStart)/(gEnd-gStart)*255;
			image.at<Vec3b>(i,j)[2] = (double)(image.at<Vec3b>(i,j)[2]-bStart)/(rEnd-rStart)*255<0 ?image.at<Vec3b>(i,j)[2]:(double)(image.at<Vec3b>(i,j)[2]-rStart)/(rEnd-rStart)*255;
		}
	}

	namedWindow("newImg",2);
	imshow("newImg",image);
	waitKey(0);

	system("pause");
	return 0;
}
 
