#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>



using namespace std;
using namespace cv;

int main(void){
	Mat zi = imread("zi.png");
	Mat lv = imread("lv.png");

	float zitrainingdata[2500][3] = {0};
	int count=0;
	for(int i=0;i<50;i++){
		for(int j=0;j<50;j++){
			zitrainingdata[count][0] = zi.at<Vec3b>(i,j)[0];
			zitrainingdata[count][1] = zi.at<Vec3b>(i,j)[1];
			zitrainingdata[count][2] = zi.at<Vec3b>(i,j)[2];
			count++;		
		}}

	float lvtrainingdata[2500][3] = {0};
	count=0;
	for(int i=0;i<50;i++){
		for(int j=0;j<50;j++){
			lvtrainingdata[count][0] = lv.at<Vec3b>(i,j)[0];
			lvtrainingdata[count][1] = lv.at<Vec3b>(i,j)[1];
			lvtrainingdata[count][2] = lv.at<Vec3b>(i,j)[2];
			count++;		
		}}




	Mat zitrainingDataMat(2500,3,CV_32FC1,zitrainingdata);
	Mat lvtrainingDataMat(2500,3,CV_32FC1,lvtrainingdata);
	float zilabels[2500] = {1.0};
	Mat ziLabelsMat(2500,1,CV_32FC1,zilabels);
	float lvlabels[2500] = {-1.0};
	Mat lvLabelsMat(2500,1,CV_32FC1,lvlabels);


	CvSVMParams params;  
	params.svm_type = CvSVM::C_SVC;  
	params.kernel_type = CvSVM::LINEAR;  
	params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);  

	CvSVM SVM;  
	SVM.train(zitrainingDataMat, ziLabelsMat, Mat(), Mat(), params);  
	SVM.train(lvtrainingDataMat, lvLabelsMat, Mat(), Mat(), params);  




	 Mat sampleMat = (Mat_<float>(1,3) << 255,0,0);
	  float response = SVM.predict(sampleMat);  
	  cout<<response;
	  system("pause");
	  return 0;

}
