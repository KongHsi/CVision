#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

using namespace std;
using namespace cv;

int main(void){
	//read two source img for the training data
	Mat color1 = imread("zi.png");
	Mat color2 = imread("lv.png");

	//mark 0-2499 to label 1 and 2500-5000 to label -1
	float labels[5000] = {1.0};
	for(int c=2500;c<5000;c++){
		labels[c] = -1.0;
	}
	Mat LabelsMat(5000,1,CV_32FC1,labels);
	

	//get 5000 pixels training data
	float trainingdata[5000][3] = {{0,0,0}};
	int count=0;
	for(int i=0;i<50;i++){
		for(int j=0;j<50;j++){
			trainingdata[count][0] = (float)color1.at<Vec3b>(i,j)[0];
			trainingdata[count][1] = (float)color1.at<Vec3b>(i,j)[1];
			trainingdata[count][2] = (float)color1.at<Vec3b>(i,j)[2];
			cout<<trainingdata[count][0]<<","<<trainingdata[count][1]<<","<<trainingdata[count][2]<<endl;
			count++;	
		}}

	cout<<"green"<<endl;
	for(int i=0;i<50;i++){
		for(int j=0;j<50;j++){
			trainingdata[count][0] =(float)color2.at<Vec3b>(i,j)[0];
			trainingdata[count][1] =(float)color2.at<Vec3b>(i,j)[1];
			trainingdata[count][2] =(float)color2.at<Vec3b>(i,j)[2];
			cout<<trainingdata[count][0]<<","<<trainingdata[count][1]<<","<<trainingdata[count][2]<<endl;
			count++;		
		}}
	Mat trainingDataMat(5000,3,CV_32FC1,trainingdata);
	
	//sets SVM Parameters
	CvSVMParams params;  
	params.svm_type = CvSVM::C_SVC;  
	params.kernel_type = CvSVM::LINEAR;  
	params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);  

	//train the SVM
	CvSVM SVM;  
	SVM.train(trainingDataMat, LabelsMat, Mat(), Mat(), params);  
	
	//here's a quick test case
	Mat sampleMat = (Mat_<float>(1,3) << 70,43,65);
    cout<<(float)SVM.predict(sampleMat);
	system("pause");
	
	//set up the full testcase
	Mat testcase = imread("zi.png");
	if(!testcase.data)system("pause");
	cout<<"testcase"<<endl;
	float testdata[900][3] = {{0,0,0}};
	count =0;
	for(int i=0;i<30;i++){
		for(int j=0;j<30;j++){
			testdata[count][0]=(float)testcase.at<Vec3b>(i,j)[0];
			testdata[count][1]=(float)testcase.at<Vec3b>(i,j)[1];
			testdata[count][2]=(float)testcase.at<Vec3b>(i,j)[2];
			cout<<testdata[count][0]<<","<<testdata[count][1]<<","<<testdata[count][2]<<endl;
			count++;
		}}
	
	
	//test the testcase
	for(int i=0;i<900;i++){
	float temp[3] = {50,50,50};
	Mat sampleMat(1,3,CV_32FC1,temp);
	cout<< SVM.predict(sampleMat)<<endl;
	}


	system("pause");
	return 0;
}
