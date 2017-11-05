#include "DetectEmotion.h"

DetectEmotion::DetectEmotion(Mat faceRegion, EyeContour leftEye, EyeContour rightEye, LipDetection lip, EyebrowDetection leftEyebrow, EyebrowDetection rightEyebrow)
{
	this->faceRegion = faceRegion;
	this->leftEye = leftEye;
	this->rightEye = rightEye;
	this->lip = lip;
	this->leftEyebrow = leftEyebrow;
	this->rightEyebrow = rightEyebrow;

	calculateEyeRatio();
	calculateMouthEdgeRatio();
	calculateMouthRatio();

	estimateEmotion();
}


void DetectEmotion::calculateEyeRatio()
{
	double leftWidth = this->leftEye.getEyeWidth();
	double leftHeight = this->leftEye.getEyeHeight();
	double rightWidth = this->rightEye.getEyeWidth();
	double rightHeight = this->rightEye.getEyeHeight();

	double leftEyeRatio = leftHeight / leftWidth ;
	double rightEyeRatio = rightHeight / rightWidth ;

	if (leftEyeRatio < rightEyeRatio) {
		this->eyeRatio = leftEyeRatio;
	}
	else {
		this->eyeRatio = rightEyeRatio;
	}
}

void DetectEmotion::calculateMouthEdgeRatio()
{
	double upToLeftAndRight;
	double upToLeft, upToRight;
	upToLeft = this->lip.getLeft().y - this->lip.getUp().y;
	upToRight = this->lip.getRight().y - this->lip.getUp().y;
	if (upToLeft < upToRight) {
		upToLeftAndRight = upToLeft;
	}
	else {
		upToLeftAndRight = upToRight;
	}
	this->mouthEdgeRatio = upToLeftAndRight / this->lip.getLipHeight();
}

void DetectEmotion::calculateMouthRatio()
{
	this->mouthRatio = (double)this->lip.getLipHeight() / (double)this->lip.getLipWidth();
}

bool DetectEmotion::isAngryEyebrow() {
	if (this->leftEyebrow.getLeft().y < this->leftEyebrow.getRight().y &&
		this->rightEyebrow.getRight().y < this->rightEyebrow.getLeft().y) {
		return true;
	}
	return false;
}


bool DetectEmotion::isEyeBig() {
	if (this->eyeRatio > 0.33) {
		return true;
	}
	else {
		return false;
	}
}

bool DetectEmotion::isEyeSmall() {
	if (this->eyeRatio < 0.3) {
		return true;
	}
	else {
		return false;
	}
}

bool DetectEmotion::isSmileMouth() {
	if (this->mouthEdgeRatio < 0.3) {
		return true;
	}
	else {
		return false;
	}
}

bool DetectEmotion::isSadOrAngryMouth() {
	if (this->mouthEdgeRatio > 0.5) {
		return true;
	}
	else {
		return false;
	}
}

bool DetectEmotion::isSurprizedMouth() {
	if (mouthRatio > 0.7) {
		return true;
	}
	else {
		return false;
	}
}


bool DetectEmotion::isHappy() {
	if (isEyeSmall() && isSmileMouth()) {
		return true;
	}
	return false;
}

bool DetectEmotion::isAngry() {
	if (isEyeBig() && isSadOrAngryMouth() && isAngryEyebrow()) {
		return true;
	}
	return false;
}

bool DetectEmotion::isSad() {
	if (isEyeSmall() && isSadOrAngryMouth()) {
		return true;
	}
	return false;
}

bool DetectEmotion::isSurprised() {
	if (isEyeBig() && isSurprizedMouth()) {
		return true;
	}
	return false;
}


void DetectEmotion::estimateEmotion()
{
	int trueNum=0;
	if (isHappy()) {
		this->emotion = "Happy";
		trueNum++;
	}
	if (isAngry()) {
		this->emotion = "Angry";
		trueNum++;
	}
	if (isSad()) {
		this->emotion = "Sad";
		trueNum++;
	}
	if (isSurprised()) {
		this->emotion = "Surpised";
		trueNum++;
	}
	if (trueNum != 1) {
		this->emotion = "";
	}
}

String DetectEmotion::getEmotion()
{
	return this->emotion;
}

double DetectEmotion::getEyeSize() {
	//if (isAngryEyebrow() == true && isSadOrAngryMouth() == true) {
	//	return 1;
	//}
	return this->eyeRatio;
}