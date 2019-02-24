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
        Mat imgOriginal;
		cap.grab();

		if (!cap.grab()) {
			printf("failed to grab from camera\n");
			break;
		}
		cap >> imgOriginal;



  
  imshow("Original", imgOriginal); //show the original image


	  


        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
            break; 
       }
    }

   return 0;

}
*/

#include "opencv2/opencv.hpp"
using namespace cv;
int main(int, char**)
{
VideoCapture cap(0); // open the default camera
if(!cap.isOpened())  // check if we succeeded
return -1;
Mat original;
namedWindow("original",1);
namedWindow("step1", 1);
namedWindow("step2", 1);
namedWindow("originalz", 1);
for(;;)
{
Mat frame;
cap >> frame; // get a new frame from camera
imshow("originalz", frame);

//cvtColor(frame, original, COLOR_BGR2GRAY);
//imshow("original", original);
//GaussianBlur(original, original, Size(7,7), 1.5, 1.5);
//imshow("step1", original);
//Canny(original, original, 0, 30, 3);
//imshow("step2", original);
if(waitKey(30) >= 0) break;
}
// the camera will be deinitialized automatically in VideoCapture destructor
return 0;
}
Mat& ScanImageAndReduceC(Mat& I, const uchar* const table)
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
}