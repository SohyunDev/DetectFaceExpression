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

class EyeContour 
{
protected:
	Mat eyeRegion;
	Mat binaryEyeRegion;
	Rect eyePosition;
	double threshold;
	Point up, down, left, right;
	int eyeHeight, eyeWidth;
	vector<vector<Point>> eyeContours;
	vector<vector<Point>> eyeContour;

	double averageIntensity();
	void makeBinaryImg();
	int getLargestContourIndex();
	void makeContourPoints(int);
	void setUpDownLeftRightPosition();

public:
	EyeContour() {};
	EyeContour(Mat, Rect);
	vector<vector<Point>> getEyeContour();
	Point getUp();
	Point getDown();
	Point getLeft();
	Point getRight();
	int getEyeHeight();
	int getEyeWidth();



};