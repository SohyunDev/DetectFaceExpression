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

class FaceDetection
{
protected:
	Mat grayImg;
	String FACE_CASCADE;
	vector<Rect> facePosition;
	CascadeClassifier face;

public:
	FaceDetection();
	FaceDetection(String, Mat);
	vector<Rect> findFaces();
};