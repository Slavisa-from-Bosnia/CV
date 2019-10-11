#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;


Mat& FindEdges (Mat& I)
{
	// accept only char type matrices
	CV_Assert(I.depth() == CV_8U);

	int channels = I.channels();

	int nRows = I.rows;
	int nCols = I.cols * channels;
	int step = 1*3;
	

	/*if (I.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}
	*/


	int i, j;
	uchar bref, gref, rref;
	uchar diffcolor = 77;
	bref = 1;
	gref = 1;
	rref = 1;

	for (i = 0; i < nRows; i=i+1) {

	uchar* p = I.ptr<uchar>(i);
		for (j = 0; j < nCols; j=j+step) {
			 uchar *p2 = p;

			if ((((p2[0] - bref )> diffcolor)|| ((bref -p2[0])> diffcolor)) || (((p2[1] - gref)> diffcolor) || ((gref - p2[1])> diffcolor)) || (((p2[2] - rref)> diffcolor) || ((rref - p2[2])> diffcolor))) {
				 //bref = p2[0];
				p2[0] = 255;
				p2[1] = 255;
				p2[2] = 255;
			 }
			 else {
				 p2[0] = 1;
				 p2[1] = 1;
				 p2[2] = 1;
			 }
			 
			//gref = p2[1] + 10;
			//rref = p2[2] + 10;

			 
			//p2[0] = bref;
			//p2[1] = gref;
			//p2[2] = rref;

			
			p += 3*step;
		}
	}
	
	return I;
}

int main(int, char**)
{
VideoCapture cap(0); // open the default camera
if(!cap.isOpened())  // check if we succeeded
return -1;
Mat frame, step1;

namedWindow("Iinal",1);
namedWindow("AfterEdges", 1);

for(;;)
{
	
cap >> frame; // get a new frame from camera


imshow("Iinal", frame);
step1 = FindEdges (frame);

imshow("AfterEdges", step1);



if(waitKey(30) >= 0) break;
}
// the camera will be deinitialized automatically in VideoCapture destructor
return 0;
}

