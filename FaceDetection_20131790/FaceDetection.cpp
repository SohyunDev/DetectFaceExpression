#include "FaceDetection.h"


FaceDetection::FaceDetection() {

}

FaceDetection::FaceDetection(String FACE_CASCADE, Mat grayImg) {
	this->FACE_CASCADE = FACE_CASCADE;
	this->grayImg = grayImg;



}

vector<Rect> FaceDetection::findFaces() {
	if (!face.load(this->FACE_CASCADE)) {
		printf("Error loading face cascade\n");
		exit(0);
	}
	this->face.detectMultiScale(this->grayImg, this->facePosition, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

	return this->facePosition;
}

