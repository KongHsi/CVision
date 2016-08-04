#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int findDis(Vec3b color, Vec3b target);
void findColor(const Mat &image,Mat &result, Vec3b &target);
void findEndPoints(const Mat &image, int* result);
void combineImgs(const Mat &image, Mat &result);
void erodeImg(Mat &image);
void dilateImg(Mat &image);
void findRegionColor(Mat& result,int color,int regions[]);
void findRegionColorMain();

int main (int argc,char** argv){
			/*
			Mat image = imread("1.jpg");
			if(!image.data)system("pause");
			cvtColor(image,image,COLOR_BGR2HSV);
			cout<<(int)image.at<Vec3b>(image.rows-10,10)[0]<<endl;
			
			system("pause");
			return 0;*/


			Mat image = imread("1.jpg");
			if(!image.data)system("pause");
			vector<Mat> planes;
			split(image,planes);
			for(int k=0;k<3;k++){
				int max = 0;
				int min = 255;
				for(int i=0;i<planes[k].rows;i++){
					for(int j=0;j<planes[k].cols;j++){
						if(planes[k].at<uchar>(i,j)>max)max=planes[k].at<uchar>(i,j);
						if(planes[k].at<uchar>(i,j)<min)min=planes[k].at<uchar>(i,j);
						
					}
				}
				namedWindow("1");
				imshow("1",planes[k]);
				

				for(int i=0;i<planes[k].rows;i++){
					for(int j=0;j<planes[k].cols;j++){
						planes[k].at<uchar>(i,j)=((double)(planes[k].at<uchar>(i,j)-min)/(max-min))*255;
						
					}}
				
				
			}
			merge(planes,image);
			
			
			imwrite("2.png",image);
			waitKey(10);
}
