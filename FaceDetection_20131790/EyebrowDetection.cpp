#include "EyebrowDetection.h"

EyebrowDetection::EyebrowDetection(Mat eyebrowRegion, Rect eyebrowPosition)
{
	cvtColor(eyebrowRegion, this->eyebrowRegion, CV_BGR2GRAY);
	this->eyebrowPosition = eyebrowPosition;
	this->threshold = averageIntensity();
	makeBinaryImg();
	//ÄÁÅõ¾î
	findContours(this->binaryEyebrowRegion, this->eyebrowContours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
	if (this->eyebrowContours.size() > 0) {
		int maxContourIndex = getLargestContourIndex();
		makeContourPoints(maxContourIndex);
	}
	imshow("eyebrow", this->binaryEyebrowRegion);
	setUpDownLeftRightPosition();
	
}


double EyebrowDetection::averageIntensity() {

	double average=0;
	int totalPixel = this->eyebrowRegion.cols * this->eyebrowRegion.rows;
	for (int row = 0; row < this->eyebrowRegion.rows; row++) {  
		for (int col = 0; col < this->eyebrowRegion.cols; col++) {
			average += this->eyebrowRegion.at<uchar>(row, col);
		}
	}
	average = average / totalPixel;
	average = average * 0.8;
	return average;
}


void EyebrowDetection::makeBinaryImg() {
	this->binaryEyebrowRegion = this->eyebrowRegion.clone();
	for (int row = 0; row < this->eyebrowRegion.rows; row++) {
		for (int col = 0; col < this->eyebrowRegion.cols; col++) {
			if (this->eyebrowRegion.at<uchar>(row, col) > this->threshold) {
				this->binaryEyebrowRegion.at<uchar>(row, col) = (uchar)255;
			}
			else {
				this->binaryEyebrowRegion.at<uchar>(row, col) = (uchar)0;
			}
		}
	}
	medianBlur(this->binaryEyebrowRegion, this->binaryEyebrowRegion, 5);
}

int EyebrowDetection::getLargestContourIndex() {
	int maxContourSize=0;
	int maxContourIndex = -1;
	for (int i = 0; i < this->eyebrowContours.size(); i++) {
		if (this->eyebrowContours[i].size() > maxContourSize) {
			maxContourSize = this->eyebrowContours[i].size();
			maxContourIndex = i;
		}
	}
	return maxContourIndex;
}


vector<vector<Point>> EyebrowDetection::getEyebrowContour()
{
	return this->eyebrowContour;
}


void EyebrowDetection::makeContourPoints(int maxContourIndex) {
	vector<Point>tempEyebrowContour = this->eyebrowContours[maxContourIndex];
	for (int i = 0; i < tempEyebrowContour.size(); i++) {
		tempEyebrowContour[i].x += this->eyebrowPosition.x;
		tempEyebrowContour[i].y += this->eyebrowPosition.y;
	}
	this->eyebrowContour.push_back(tempEyebrowContour);
}

void EyebrowDetection::setUpDownLeftRightPosition()
{
	if (eyebrowContour.size() > 0) {
		Point up = eyebrowContour[0].at(0), down = eyebrowContour[0].at(0), left = eyebrowContour[0].at(0), right = eyebrowContour[0].at(0);
		for (int i = 0; i < eyebrowContour.size(); i++) {
			for (int j = 0; j < eyebrowContour[i].size(); j++) {
				if (up.y > eyebrowContour[i].at(j).y) {
					up = eyebrowContour[i].at(j);
				}
				if (down.y < eyebrowContour[i].at(j).y) {
					down = eyebrowContour[i].at(j);
				}
				if (left.x > eyebrowContour[i].at(j).x) {
					left = eyebrowContour[i].at(j);
				}
				if (right.x < eyebrowContour[i].at(j).x) {
					right = eyebrowContour[i].at(j);
				}
			}
		}
		this->up = up;
		this->down = down;
		this->left = left;
		this->right = right;
	}
}

Point EyebrowDetection::getUp()
{
	return this->up;
}

Point EyebrowDetection::getDown()
{
	return this->down;
}

Point EyebrowDetection::getLeft()
{
	return this->left;
}

Point EyebrowDetection::getRight()
{
	return this->right;
}

