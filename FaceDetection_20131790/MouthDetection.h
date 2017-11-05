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

class MouthDetection
{
protected:
	Mat faceRegion;
	String MOUTH_CASCADE;
	vector<Rect> mouthPosition;
	CascadeClassifier mouth;

	void detectRealMouth(vector<Rect>);
	Rect facePosition;
	Rect nosePosition;

public:
	MouthDetection();
	MouthDetection(String, Mat, Rect, Rect);
	vector<Rect> findMouth();
};