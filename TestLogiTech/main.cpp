#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace cv;
using namespace std;

int main(int, char)
{
	VideoCapture cap(1); // open the default camera
	if (!cap.isOpened()) // check if we succeeded
		return -1;
	Mat edges;
	namedWindow("edges", 1);
	for (;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
		cvtColor(frame, edges, CV_BGR2GRAY);
		//GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		//Canny(edges, edges, 0, 30, 3);
		Mat chs[3];
		split(edges, chs);
		
		equalizeHist(chs[0], chs[0]);
		equalizeHist(chs[1], chs[1]);
		equalizeHist(chs[2], chs[2]);

		vector<Mat> temp;
		temp.push_back(chs[0]);
		temp.push_back(chs[1]);
		temp.push_back(chs[2]);

		//merge(temp, frame);

		imshow("frame", frame);
		cvtColor(frame, edges, CV_BGR2HSV);
		split(edges, chs);
		threshold(frame, edges, 150, 255, 0);
		imshow("edges", chs[0]);

		if (waitKey(30) >= 0)
			break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}