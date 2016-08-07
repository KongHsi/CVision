#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <vector>
using namespace std;
using namespace cv;



#include <Windows.h>
#include <Commdlg.h>


void operation(int,void*);



//read new image
Mat img;
//image name
String imgName;
//two variables adjustable on GUI
int lightnesslvl =50;
int button =0;
int R =0;
int G =0;
int B =0;
//a flag for new image
bool stateFlag = true;

int main(void){
	

 img = imread("1.jpg");
 if( !img.data ){ return -1; }

 /// Create window
 namedWindow("window", 2 );
 resizeWindow("window", 800, 600);

 /// Create Trackbar to select kernel type
 createTrackbar( "Lightness:\n 0-100", "window",
                 &lightnesslvl, 100,
                 operation);
 createTrackbar( "Add Img", "window",
                 &button, 1,
                 operation);
 createTrackbar( "R", "window",
                 &R, 255,
                 operation);
 createTrackbar( "G", "window",
                 &G, 255,
                 operation);
 createTrackbar( "B", "window",
                 &B, 255,
                 operation);
operation(0,0);
 waitKey(0);
 
}

void operation(int,void*){
	
	//the normal state
	if(button == 0){
		Mat temp = 0.01*lightnesslvl*img;
		imshow("window",temp);
		stateFlag = true;
	}
	//to read a new image
	if(button == 1 && stateFlag == true){
		//open a window dialog
		OPENFILENAMEA ofn;       
		char szFile[260];       
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFile;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = "*.png";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = 0;
		GetOpenFileNameA(&ofn);
		imgName = ofn.lpstrFile;
		img = imread(imgName);
		imshow("window",img);
		stateFlag = false;
	}
}
