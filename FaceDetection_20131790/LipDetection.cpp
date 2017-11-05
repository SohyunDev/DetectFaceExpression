#include "LipDetection.h"

LipDetection::LipDetection(Mat lipRegion, Rect mouthPosition)
{	
	Mat tempLipRegion = lipRegion.clone();
	Mat bilateral;
	this->lipRegion.copySize(lipRegion);
	blur(tempLipRegion, tempLipRegion, Size(2, 2));
	bilateralFilter(tempLipRegion, bilateral, 9, 15, 15);

	cvtColor(bilateral, this->lipRegion, CV_BGR2YCrCb);

	cvtColor(lipRegion, this->binaryLipRegion, CV_BGR2GRAY);
	this->mouthPosition = mouthPosition;
	this->threshold = averageIntensityCr();
	makeBinaryImg();

	findContours(this->binaryLipRegion, this->lipContours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
	if (this->lipContours.size() > 0) {
		int maxContourIndex = getLargestContourIndex();
		makeContourPoints(maxContourIndex);
	}
	setUpDownLeftRightPosition();
	imshow("lip", this->binaryLipRegion);
}

double LipDetection::averageIntensityCr()
{

	
	double average = 0;
	int totalPixel = this->lipRegion.cols*this->lipRegion.rows;
	for (int row = 0; row < this->lipRegion.rows; row++) {
		for (int col = 0; col < this->lipRegion.cols; col++) {
			average += this->lipRegion.at<Vec3b>(row, col)[1];
		}
	}
	average = average / totalPixel;
	average = average *2;
	return average;
}

void LipDetection::makeBinaryImg()
{
	vector<Mat> channels;
	split(this->lipRegion, channels);
	cv::threshold(channels[1], this->binaryLipRegion, 160, 255, CV_THRESH_BINARY);
	dilate(this->binaryLipRegion, this->binaryLipRegion, Mat());
	erode(this->binaryLipRegion, this->binaryLipRegion, Mat());
	medianBlur(this->binaryLipRegion, this->binaryLipRegion, 5);
	
}

int LipDetection::getLargestContourIndex()
{
	int maxContourSize = 0;
	int maxContourIndex = -1;
	for (int i = 0; i < this->lipContours.size(); i++) {
		if (this->lipContours[i].size() > maxContourSize) {
			maxContourSize = this->lipContours[i].size();
			maxContourIndex = i;
		}
	}
	return maxContourIndex;
}

void LipDetection::makeContourPoints(int maxContourIndex)
{

	for (int j = 0; j < this->lipContours.size(); j++) {
		vector<Point>tempLipContour = this->lipContours[j];
		for (int i = 0; i < tempLipContour.size(); i++) {
			tempLipContour[i].x += this->mouthPosition.x;
			tempLipContour[i].y += this->mouthPosition.y;
		}
		this->lipContour.push_back(tempLipContour);
	}

}




void LipDetection::setUpDownLeftRightPosition() {
	if (lipContour.size() > 0) {
		Point up = lipContour[0].at(0), down = lipContour[0].at(0), left = lipContour[0].at(0), right = lipContour[0].at(0);
		for (int i = 0; i < lipContour.size(); i++) {
			for (int j = 0; j < lipContour[i].size(); j++) {
				if (up.y > lipContour[i].at(j).y) {
					up = lipContour[i].at(j);
				}
				if (down.y < lipContour[i].at(j).y) {
					down = lipContour[i].at(j);
				}
				if (left.x > lipContour[i].at(j).x) {
					left = lipContour[i].at(j);
				}
				if (right.x < lipContour[i].at(j).x) {
					right = lipContour[i].at(j);
				}
			}
		}
		this->up = up;
		this->down = down;
		this->left = left;
		this->right = right;
		this->lipHeight = down.y-up.y;
		this->lipWidth = right.x - left.x;
	}
}

vector<vector<Point>> LipDetection::getLipContour()
{
	return this->lipContour;
}

Point LipDetection::getUp()
{
	return this->up;
}

Point LipDetection::getDown()
{
	return this->down;
}

Point LipDetection::getLeft()
{
	return this->left;
}

Point LipDetection::getRight()
{
	return this->right;
}

int LipDetection::getLipHeight()
{
	return this->lipHeight;
}

int LipDetection::getLipWidth()
{
	return this->lipWidth;
}