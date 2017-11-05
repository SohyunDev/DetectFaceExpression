#pragma once
#ifdef _DEBUG
#pragma comment(lib,"opencv_world320d.lib")
#else
#pragma comment(lib, "opencv_world320.lib")
#endif

#include "opencv2\objdetect.hpp"
#include "opencv2\videoio.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

class EyebrowDetection
{
protected:
	Mat eyebrowRegion;
	Mat binaryEyebrowRegion;
	Rect eyebrowPosition;
	double threshold;
	Rect eyePosition;
	vector<vector<Point>> eyebrowContours;
	vector<vector<Point>> eyebrowContour;
	Point up, down, left, right;
	int eyebrowHeight, eyebrowWidth;

	double averageIntensity();
	void makeBinaryImg();
	int getLargestContourIndex();
	void makeContourPoints(int);
	void setUpDownLeftRightPosition();

public:
	EyebrowDetection() {};
	EyebrowDetection(Mat, Rect);
	vector<vector<Point>> getEyebrowContour();
	Point getUp();
	Point getDown();
	Point getLeft();
	Point getRight();

};