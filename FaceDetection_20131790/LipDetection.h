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

class LipDetection
{
protected:
	Mat lipRegion;
	Mat binaryLipRegion;
	double threshold;
	Rect mouthPosition;
	Point up, down, left, right;
	int lipHeight, lipWidth;
	vector<vector<Point>> lipContours;
	vector<vector<Point>> lipContour;

	double averageIntensityCr();
	void makeBinaryImg();
	int getLargestContourIndex();
	void makeContourPoints(int);
	void setUpDownLeftRightPosition();

public:
	LipDetection() {};
	LipDetection(Mat, Rect);
	vector<vector<Point>> getLipContour();
	Point getUp();
	Point getDown();
	Point getLeft();
	Point getRight();
	int getLipHeight();
	int getLipWidth();
};