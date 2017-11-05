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

class EyeDetection
{
protected:
	Mat faceRegion;
	String EYE_CASCADE;
	vector<Rect> eyePosition;
	CascadeClassifier eye;

	void detectRealEyes(vector<Rect>);
	Rect facePosition;




public:
	EyeDetection();
	EyeDetection(String, Mat, Rect);
	vector<Rect> findEyes();
};