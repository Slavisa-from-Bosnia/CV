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
	
	/*if (I.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}
	*/

	int i, j;

	uchar diffcolor =86;

	for (i = 0; i < nRows; i=i+1) {

	uchar* p = I.ptr<uchar>(i);

		for (j = 0; j < nCols-6; j=j+3) {
			uchar *p2 = p;

			if (
				(
				((p2[3] - p2[0]) > diffcolor || (p2[0] - p2[3]) > diffcolor) && 
				((p2[6] - p2[0]) > diffcolor || (p2[0] - p2[6]) > diffcolor) && 
				((p2[9] - p2[0]) > diffcolor || (p2[0] - p2[9]) > diffcolor) &&
				((p2[12] - p2[0]) > diffcolor || (p2[0] - p2[12]) > diffcolor) &&
				((p2[15] - p2[0]) > diffcolor || (p2[0] - p2[15]) > diffcolor) &&
				((p2[18] - p2[0]) > diffcolor || (p2[0] - p2[18]) > diffcolor)
					)

				||

				(
				((p2[4] - p2[1]) > diffcolor || (p2[1] - p2[4]) > diffcolor) &&
				((p2[7] - p2[1]) > diffcolor || (p2[1] - p2[7]) > diffcolor) &&
				((p2[10] - p2[1]) > diffcolor || (p2[1] - p2[10]) > diffcolor) &&
					((p2[13] - p2[1]) > diffcolor || (p2[1] - p2[13]) > diffcolor) &&
					((p2[16] - p2[1]) > diffcolor || (p2[1] - p2[16]) > diffcolor) &&
					((p2[19] - p2[1]) > diffcolor || (p2[1] - p2[19]) > diffcolor) 
					)

				||

				(
				((p2[5] - p2[2]) > diffcolor || (p2[2] - p2[5]) > diffcolor) &&
				((p2[8] - p2[2]) > diffcolor || (p2[2] - p2[8]) > diffcolor) &&
				((p2[11] - p2[2]) > diffcolor || (p2[2] - p2[11]) > diffcolor) &&
					((p2[14] - p2[2]) > diffcolor || (p2[2] - p2[14]) > diffcolor) &&
					((p2[17] - p2[2]) > diffcolor || (p2[2] - p2[17]) > diffcolor) &&
					((p2[20] - p2[2]) > diffcolor || (p2[2] - p2[20]) > diffcolor) 
					)
				
				) {

				p2[0] = p2[3];
				p2[1] = p2[4];
				p2[2] = p2[5];
				
			}
			else {
				p2[0] = 1;
				p2[1] = 1;
				p2[2] = 1;
			}
			
			p += 3;
		}
	}
	
	return I;
}


int main(int, char**)
{
VideoCapture cap(0); // open the default camera
if(!cap.isOpened())  // check if we succeeded
return -1;

Mat fr1, fr2 ;

namedWindow("Initial", 1);
namedWindow("FindEdges", 1);
//namedWindow("AfterEdges", 1);

for(;;){
	
	cap >> fr1;

		//  new frame from camera

		//
imshow("Initial", fr1);




//cvtColor(frame, step1, COLOR_BGR2HSV);
fr2 = FindEdges (fr1);
//imshow("HSV", step1)
//imshow("AfterEdges", step2);
imshow("FindEdges", fr2);




if(waitKey(30) >= 0) break;
}
// the camera will be deinitialized automatically in VideoCapture destructor
return 0;
}

