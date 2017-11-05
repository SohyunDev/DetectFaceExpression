#include "MouthDetection.h"

MouthDetection::MouthDetection() {

}

MouthDetection::MouthDetection(String MOUTH_CASCADE, Mat faceRegion, Rect facePosition, Rect nosePosition) {
	this->MOUTH_CASCADE = MOUTH_CASCADE;
	this->faceRegion = faceRegion;
	this->facePosition = facePosition;
	this->nosePosition = nosePosition;
}

vector<Rect> MouthDetection::findMouth() {
	vector<Rect> allMouthPosition;
	if (!mouth.load(this->MOUTH_CASCADE)) {
		printf("Error loading mouth cascade\n");
		exit(0);
	}
	this->mouth.detectMultiScale(this->faceRegion, allMouthPosition, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
	detectRealMouth(allMouthPosition);
	return this->mouthPosition;
}

void MouthDetection::detectRealMouth(vector<Rect> allMouthPosition) {
	Rect mouthPoint;
	int mouthPosition_y=NULL;
	if (allMouthPosition.size() > 0) {
		for (int i = 0; i < allMouthPosition.size(); i++) {
			if (nosePosition.y+nosePosition.height < allMouthPosition[i].y + facePosition.y + (facePosition.height/2) ) {
				if (mouthPosition_y == NULL) {
					mouthPoint = Rect(facePosition.x + allMouthPosition[i].x, facePosition.y + allMouthPosition[i].y + (facePosition.height*0.7), allMouthPosition[i].width, allMouthPosition[i].height);
					mouthPosition_y = mouthPoint.y;
				}
				else {
					if (mouthPosition_y < allMouthPosition[i].y+facePosition.y){
						mouthPoint = Rect(facePosition.x + allMouthPosition[i].x, facePosition.y + allMouthPosition[i].y + (facePosition.height*0.7), allMouthPosition[i].width, allMouthPosition[i].height);
						mouthPosition_y = mouthPoint.y;
					}
				}
			}
		}
		this->mouthPosition.push_back(mouthPoint);
	}
}