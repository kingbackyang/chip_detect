#include<opencv2\opencv.hpp>
#include<opencv2\dnn.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <io.h>
#include <stdio.h>
#include <fstream>

using namespace std;
using namespace cv;
using namespace dnn;

const size_t inWidth = 300;
const size_t inHeight = 300;
const float WHRatio = inWidth / (float)inHeight;
const char* classNames[] = { "background","pool", "extra", "edgebreak", "burr", "edgecorner", "lack"};

int main() 
{
	String weights = "frozen_inference_graph_v2.pb";
	String prototxt = "ssd_v2.pbtxt";
	Net net = readNetFromTensorflow(weights, prototxt);
	cout << "successfully loaded" << endl;

	Mat frame = cv::imread("test_image/02500.jpg");
	cv::Mat blob = cv::dnn::blobFromImage(frame, 1, Size(inWidth, inHeight), true, true);
	cout << "blob size: " << blob.size << endl;

	net.setInput(blob);
	Mat output = net.forward();
	cout << "output size: " << output.size << endl;
	Mat detectionMat(output.size[2], output.size[3], CV_32F, output.ptr<float>());
	float confidenceThreshold = 0.5;
	for (int i = 0; i < detectionMat.rows; i++)
	{
		float confidence = detectionMat.at<float>(i, 2);
		if (confidence > confidenceThreshold)
		{
			size_t objectClass = (size_t)(detectionMat.at<float>(i, 1));
			int xLeftBottom = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
			int yLeftBottom = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
			int xRightTop = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
			int yRightTop = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);

			ostringstream ss;
			ss << confidence;
			String conf(ss.str());

			Rect object((int)xLeftBottom, (int)yLeftBottom,
				(int)(xRightTop - xLeftBottom),
				(int)(yRightTop - yLeftBottom));

			rectangle(frame, object, Scalar(0, 255, 0), 2);
			String label = String(classNames[objectClass]) + ": " + conf;
			int baseLine = 0;
			Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 2, &baseLine);
			rectangle(frame, Rect(Point(xLeftBottom, yLeftBottom - labelSize.height),
				Size(labelSize.width, labelSize.height + baseLine)),
				Scalar(0, 255, 0), FILLED);
			putText(frame, label, Point(xLeftBottom, yLeftBottom),
				FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));
		}
	}
	cv::namedWindow("image", WINDOW_NORMAL);
	cv::imshow("image", frame);
	cv::waitKey(0);
	return 0;
}
