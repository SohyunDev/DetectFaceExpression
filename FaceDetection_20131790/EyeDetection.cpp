#include "EyeDetection.h"


EyeDetection::EyeDetection() {

}

EyeDetection::EyeDetection(String EYE_CASCADE, Mat faceRegion, Rect facePosition) {
	this->EYE_CASCADE = EYE_CASCADE;
	this->faceRegion = faceRegion;
	this->facePosition = facePosition;
}

vector<Rect> EyeDetection::findEyes() {
	vector<Rect> allEyePosition;
	if (!eye.load(this->EYE_CASCADE)) {
		printf("Error loading eye cascade\n");
		exit(0);
	}
	this->eye.detectMultiScale(this->faceRegion, allEyePosition, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
	detectRealEyes(allEyePosition);
	return this->eyePosition;
}

void EyeDetection::detectRealEyes(vector<Rect> allEyePosition) {
	double firstEye = 0, secondEye = 0;
	int firstEyeIndex = 0, secondEyeIndex = 0;
	if (allEyePosition.size() >= 2) {
		for (int i = 0; i < allEyePosition.size(); i++) {
			double area = allEyePosition[i].height * allEyePosition[i].width;
			if ((firstEye < area || secondEye < area) && (allEyePosition[i].y < facePosition.height / 2)) {
				if (firstEye < secondEye) {
					firstEye = area;
					firstEyeIndex = i;
				}
				else {
					secondEye = area;
					secondEyeIndex = i;
				}
			}
		}
		Rect eyePoint1 = Rect(facePosition.x + allEyePosition[firstEyeIndex].x-allEyePosition[firstEyeIndex].width*0.1, facePosition.y + allEyePosition[firstEyeIndex].y , allEyePosition[firstEyeIndex].width*1.4, allEyePosition[firstEyeIndex].height);
		Rect eyePoint2 = Rect(facePosition.x + allEyePosition[secondEyeIndex].x - allEyePosition[secondEyeIndex].width*0.1, facePosition.y + allEyePosition[secondEyeIndex].y , allEyePosition[secondEyeIndex].width*1.4, allEyePosition[secondEyeIndex].height);
		if (eyePoint1.x > eyePoint2.x) {
			Rect temp = eyePoint2;
			eyePoint2 = eyePoint1;
			eyePoint1 = temp;
		}
		this->eyePosition.push_back(eyePoint1);
		this->eyePosition.push_back(eyePoint2);
	}
}
