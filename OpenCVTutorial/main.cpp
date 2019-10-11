#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

/* int main( int argc, char** argv )
 {
    VideoCapture cap(0); //capture the video from web cam

    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the web cam" << endl;
         return -1;
    }

    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"


    while (true)
    {
        Mat imgIinal;
		cap.grab();

		if (!cap.grab()) {
			printf("failed to grab from camera\n");
			break;
		}
		cap >> imgIinal;



  
  imshow("Iinal", imgIinal); //show the Iinal image


	  


        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
            break; 
       }
    }

   return 0;

}
*/

/*#include "opencv2/opencv.hpp"
using namespace cv;

void filter1(Mat& I, Mat& S) {

	int channels = I.channels();

	int nRows = I.rows;
	int nCols = I.cols * channels;

	int i, j;
	uchar* p;
	uchar* s;

	
	
}

*/
/*Mat& ScanImageAndReduceC(Mat& I, const uchar* const table)
{
	// accept only char type matrices
	CV_Assert(I.depth() == CV_8U);

	int channels = I.channels();

	int nRows = I.rows;
	int nCols = I.cols * channels;

	if (I.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}

	int i, j;
	uchar* p;
	for (i = 0; i < nRows; ++i)
	{
		p = I.ptr<uchar>(i);
		for (j = 0; j < nCols; ++j)
		{
			p[j] = table[p[j]];
		}
	}
	return I;
}*/

Mat& FindEdges (Mat& I)
{
	// accept only char type matrices
	CV_Assert(I.depth() == CV_8U);

	int channels = I.channels();

	int nRows = I.rows;
	int nCols = I.cols * channels;
	int step = 1;
	

	/*if (I.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}
	*/


	int i, j;
	int bref, gref, rref;

	for (i = 0; i < nRows; i=i+step)
	{
	uchar* p = I.ptr<uchar>(i);
		for (j = 0; j < nCols; j=j+step)
		{
			 uchar *p2 = p;

			p2[0] = p2[0] + 10;
			p2[1] = p2[1] + 10;
			p2[2] = p2[2] + 10;
			
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

