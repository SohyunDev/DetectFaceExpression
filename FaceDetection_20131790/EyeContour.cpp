#include "EyeContour.h"

EyeContour::EyeContour(Mat eyeRegion, Rect eyePosition) {
	cvtColor(eyeRegion, this->eyeRegion, CV_BGR2GRAY);
	this->eyePosition = eyePosition;
	this->threshold = averageIntensity();
	makeBinaryImg();

	findContours(this->binaryEyeRegion, this->eyeContours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
	if (this->eyeContours.size() > 0) {
		int maxContourindex = getLargestContourIndex();
		makeContourPoints(maxContourindex);
	}
	setUpDownLeftRightPosition();
	imshow("Eye", this->binaryEyeRegion);
}

double EyeContour::averageIntensity()
{
	double average = 0;
	int totalPixel = this->eyeRegion.cols * this->eyeRegion.rows;
	for (int row = 0; row < this->eyeRegion.rows; row++) {
		for (int col = 0; col < this->eyeRegion.cols; col++) {
			average += this->eyeRegion.at<uchar>(row, col);
		}
	}
	average = average / totalPixel;
	average = average*0.8;
	return average;
}

void EyeContour::makeBinaryImg()
{
	this->binaryEyeRegion = this->eyeRegion.clone();
	for (int row = 0; row < this->eyeRegion.rows; row++) {
		for (int col = 0; col < this->eyeRegion.cols; col++) {
			if (this->eyeRegion.at<uchar>(row, col) > this->threshold) {
				this->binaryEyeRegion.at<uchar>(row, col) = (uchar)255;
			}
			else {
				this->binaryEyeRegion.at<uchar>(row, col) = (uchar)0;
			}
		}
	}
	dilate(this->binaryEyeRegion, this->binaryEyeRegion, Mat());
	erode(this->binaryEyeRegion, this->binaryEyeRegion, Mat());
	medianBlur(this->binaryEyeRegion, this->binaryEyeRegion, 5);
}



int EyeContour::getLargestContourIndex()
{
	int maxContourSize = 0;
	int maxContourIndex = -1;
	for (int i = 0; i < this->eyeContours.size(); i++) {
		if (this->eyeContours[i].size() > maxContourSize) {
			maxContourSize = this->eyeContours[i].size();
			maxContourIndex = i;
		}
	}
	return maxContourIndex;
}

void EyeContour::makeContourPoints(int maxContourIndex)
{
	vector<Point>tempEyeContour = this->eyeContours[maxContourIndex];
	for (int i = 0; i < tempEyeContour.size(); i++) {
		tempEyeContour[i].x += this->eyePosition.x;
		tempEyeContour[i].y += this->eyePosition.y;
	}
	this->eyeContour.push_back(tempEyeContour);
}

void EyeContour::setUpDownLeftRightPosition()
{
	if (eyeContour.size() > 0) {
		Point up = eyeContour[0].at(0), down = eyeContour[0].at(0), left = eyeContour[0].at(0), right = eyeContour[0].at(0);
		for (int i = 0; i < eyeContour.size(); i++) {
			for (int j = 0; j < eyeContour[i].size(); j++) {
				if (up.y > eyeContour[i].at(j).y) {
					up = eyeContour[i].at(j);
				}
				if (down.y < eyeContour[i].at(j).y) {
					down = eyeContour[i].at(j);
				}
				if (left.x > eyeContour[i].at(j).x) {
					left = eyeContour[i].at(j);
				}
				if (right.x < eyeContour[i].at(j).x) {
					right = eyeContour[i].at(j);
				}
			}
		}
		this->up = up;
		this->down = down;
		this->left = left;
		this->right = right;
		this->eyeHeight = down.y - up.y;
		this->eyeWidth = right.x - left.x;
	}
}

vector<vector<Point>> EyeContour::getEyeContour()
{
	return this->eyeContour;
}

Point EyeContour::getUp()
{
	return this->up;
}

Point EyeContour::getDown()
{
	return this->down;
}

Point EyeContour::getLeft()
{
	return this->left;
}

Point EyeContour::getRight()
{
	return this->right;
}

int EyeContour::getEyeHeight()
{
	return this->eyeHeight;
}

int EyeContour::getEyeWidth()
{
	return this->eyeWidth;
}