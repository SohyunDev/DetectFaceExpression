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
#include "FaceDetection.h"
#include "EyeDetection.h"
#include "MouthDetection.h"
#include "EyebrowDetection.h"
#include "LipDetection.h"
#include "EyeContour.h"
#include "DetectEmotion.h"
#include <cstring>

using namespace std;
using namespace cv;

#define CAM_WIDTH 640
#define CAM_HEIGHT 360
Mat checkRectangled(Mat image, vector<Rect> checkPoints, Scalar color);
Mat drawContour(Mat image, vector<Point> contour, Scalar color);

String FACE_CASCADE = "C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml";
String EYE_CASCADE = "C:/opencv/sources/data/haarcascades/haarcascade_eye.xml";
String NOSE_CASCADE = "C:/opencv/sources/data/haarcascades/haarcascade_nose.xml";
String MOUTH_CASCADE = "C:/opencv/sources/data/haarcascades/Mouth.xml";

CascadeClassifier face;
CascadeClassifier eye;
CascadeClassifier mouth;
String WINDOW_NAME = "Face Detection";




int main(int argc, char**argv) {
	VideoCapture vc(0);
	if (!vc.isOpened()) return 0;

	if (!face.load(FACE_CASCADE)||!eye.load(EYE_CASCADE)||!mouth.load(MOUTH_CASCADE)) {
		printf("Error loading face/eye cascade \n");
		return -1;
	}

	Mat img;
	Mat imgOriginal;
	Mat grayImg;
	while (1) {
		vc >> img;
		if (img.empty()) { break; }
		flip(img, img, 1);
		imgOriginal = img;
		cvtColor(img, grayImg, CV_RGB2GRAY);
		vector<Rect> facePosition;
		FaceDetection faceDetection = FaceDetection(FACE_CASCADE, grayImg);
		facePosition = faceDetection.findFaces();
//		img = checkRectangled(img, facePosition, Scalar(255,0,0));

		if(facePosition.size()>0){
			for (int i = 0; i < facePosition.size(); i++) {
				vector <Rect> eyePosition;
				Mat faceRegion = grayImg(facePosition[i]);
				Rect eyePositionArea = Rect(facePosition[i].x, facePosition[i].y, facePosition[i].width, facePosition[i].height / 2);
				Mat eyeRegion = grayImg(eyePositionArea);
				EyeDetection eyeDetection = EyeDetection(EYE_CASCADE, eyeRegion, facePosition[i]);
				eyePosition = eyeDetection.findEyes();
//				img = checkRectangled(img, eyePosition, Scalar(0, 255, 0));

				if (eyePosition.size() > 1) {
					Rect leftEyePosition = eyePosition[0];
					Mat leftEyeRegion = imgOriginal(leftEyePosition);
					Rect rightEyePosition = eyePosition[1];
					Mat rightEyeRegion = imgOriginal(rightEyePosition);
					EyeContour leftEyeContour = EyeContour(leftEyeRegion, leftEyePosition);
					EyeContour rightEyeContour = EyeContour(rightEyeRegion, rightEyePosition);
					vector<vector<Point>> leftEyeContourPoints = leftEyeContour.getEyeContour();
					for (int eyeSize = 0; eyeSize < leftEyeContourPoints.size(); eyeSize++) {
				//				drawContours(img, leftEyeContourPoints, eyeSize, Scalar(255,0 , 0), 2);
					}
//					circle(img, leftEyeContour.getDown(), 1, Scalar(0, 255, 255), 2);
//					circle(img, leftEyeContour.getUp(), 1, Scalar(0, 255, 255), 2);
//					circle(img, leftEyeContour.getLeft(), 1, Scalar(0, 255, 255), 2);
//					circle(img, leftEyeContour.getRight(), 1, Scalar(0, 255, 255), 2);

					vector<vector<Point>> rightEyeContourPoints = rightEyeContour.getEyeContour();
					for (int eyeSize = 0; eyeSize < rightEyeContourPoints.size(); eyeSize++) {
						//	drawContours(img, rightEyeContourPoints, eyeSize, Scalar(255, 0, 0), 2);
					}
//					circle(img, rightEyeContour.getDown(), 1, Scalar(0, 255, 255), 2);
//					circle(img, rightEyeContour.getUp(), 1, Scalar(0, 255, 255), 2);
//					circle(img, rightEyeContour.getLeft(), 1, Scalar(0, 255, 255), 2);
//					circle(img, rightEyeContour.getRight(), 1, Scalar(0, 255, 255), 2);

					Rect eyebrowPositionArea1 = Rect(eyePosition[0].x - eyePosition[0].width*0.3, eyePosition[0].y - eyePosition[0].height*0.6, round((double)eyePosition[0].width*1.5), eyePosition[0].height*1.1);
					Rect eyebrowPositionArea2 = Rect(eyePosition[1].x - eyePosition[1].width*0.3, eyePosition[1].y - eyePosition[1].height*0.6, round((double)eyePosition[1].width*1.5), eyePosition[1].height*1.1);
					Mat eyebrowRegion1 = imgOriginal(eyebrowPositionArea1);
					Mat eyebrowRegion2 = imgOriginal(eyebrowPositionArea2);
					vector<Rect> temp;
					temp.push_back(eyebrowPositionArea1);
					temp.push_back(eyebrowPositionArea2);
	//				img = checkRectangled(img, temp, Scalar(255, 255, 0));

					EyebrowDetection firstEyebrow = EyebrowDetection(eyebrowRegion1, eyebrowPositionArea1);
					EyebrowDetection secondEyebrow = EyebrowDetection(eyebrowRegion2, eyebrowPositionArea2);
					vector<vector<Point>> firstEyebrowContour = firstEyebrow.getEyebrowContour();
					vector<vector<Point>> secondEyebrowContour = secondEyebrow.getEyebrowContour();
		//			drawContours(img, firstEyebrowContour, 0, Scalar(0, 255, 255), 2);
		//			drawContours(img, secondEyebrowContour, 0, Scalar(0, 255, 255), 2);

					/*
					circle(img, firstEyebrow.getDown(), 1, Scalar(0, 255, 0), 2);
					circle(img, firstEyebrow.getUp(), 1, Scalar(0, 255, 0), 2);
					circle(img, firstEyebrow.getLeft(), 1, Scalar(0, 255, 0), 2);
					circle(img, firstEyebrow.getRight(), 1, Scalar(0, 255, 0), 2);
					circle(img, secondEyebrow.getDown(), 1, Scalar(0, 255, 0), 2);
					circle(img, secondEyebrow.getUp(), 1, Scalar(0, 255, 0), 2);
					circle(img, secondEyebrow.getLeft(), 1, Scalar(0, 255, 0), 2);
					circle(img, secondEyebrow.getRight(), 1, Scalar(0, 255, 0), 2);
					*/
	

					Rect mouthPositionArea = Rect(facePosition[i].x, facePosition[i].y + (facePosition[i].height*0.7), facePosition[i].width, facePosition[i].height*0.3);
					vector<Rect> test;
					test.push_back(mouthPositionArea);
//					img = checkRectangled(img, test, Scalar(144, 144, 0));
					Mat mouthRegion = grayImg(mouthPositionArea);
					vector<Rect> mouthPosition;
					MouthDetection mouthDetection = MouthDetection(MOUTH_CASCADE, mouthRegion, facePosition[i], eyePosition[0]);
					mouthPosition = mouthDetection.findMouth();
					if (mouthPosition.size() > 0) {
						mouthPosition[0] = Rect(mouthPosition[0].x - mouthPosition[0].width * 0.2, mouthPosition[0].y - mouthPosition[0].height*0.2, mouthPosition[0].width*1.4, mouthPosition[0].height *1.4);
			//			img = checkRectangled(img, mouthPosition, Scalar(0, 0, 255));

						Mat lipRegion = imgOriginal(mouthPosition[0]);
						LipDetection lip = LipDetection(lipRegion, mouthPosition[0]);
						vector<vector<Point>> lipContour = lip.getLipContour();
						for (int lipSize = 0; lipSize < lipContour.size(); lipSize++) {
							//drawContours(img, lipContour, lipSize, Scalar(150, 150, 0), 2);
						}
						/*
						
						circle(img, lip.getDown(), 1, Scalar(0, 0, 255), 2);
						circle(img, lip.getUp(), 1, Scalar(0, 0, 255), 2);
						circle(img, lip.getLeft(), 1, Scalar(0, 0, 255), 2);
						circle(img, lip.getRight(), 1, Scalar(0, 0, 255), 2);
						*/
						// Detect emotion
						if (lipContour.size() > 0) {
							DetectEmotion emotion = DetectEmotion(imgOriginal(facePosition[i]), leftEyeContour, rightEyeContour, lip, firstEyebrow, secondEyebrow);
							String emotionText = emotion.getEmotion();
							double eyeRatio = emotion.getEyeSize();
							String e =  to_string(eyeRatio);
							putText(img, emotionText, Point(10, 30), 2, 1.2, Scalar(255, 0, 255), 2);
						}
					}

				}
			
			}
		}



		imshow("Test", img);
		if (waitKey(10) == 27) break;

	}
	destroyAllWindows();
	return 0;
	
}

Mat checkRectangled(Mat image, vector<Rect> checkPoints, Scalar color) {
	Mat checked = image.clone();
	for (int i = 0; i < checkPoints.size(); i++) {
		rectangle(checked, checkPoints[i], color, 2);
	}
	return checked;
}

