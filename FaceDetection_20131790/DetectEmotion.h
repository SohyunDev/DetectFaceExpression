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
#include "EyeContour.h"
#include "LipDetection.h"
#include "EyebrowDetection.h"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

class DetectEmotion
{
protected:
	Mat faceRegion;
	EyeContour leftEye;
	EyeContour rightEye;
	LipDetection lip;
	EyebrowDetection leftEyebrow;
	EyebrowDetection rightEyebrow;
	String emotion;
	
	double eyeRatio;
	double mouthEdgeRatio;
	double mouthRatio;

	void calculateEyeRatio();
	void calculateMouthEdgeRatio();
	void calculateMouthRatio();

	bool isAngryEyebrow();
	bool isEyeBig();
	bool isEyeSmall();
	bool isSmileMouth();
	bool isSadOrAngryMouth();
	bool isSurprizedMouth();
	bool isHappy();
	bool isAngry();
	bool isSad();
	bool isSurprised();
	void estimateEmotion();
	

public:
	DetectEmotion() {};
	DetectEmotion(Mat, EyeContour, EyeContour, LipDetection, EyebrowDetection, EyebrowDetection);
	String getEmotion();
	double getEyeSize();
};