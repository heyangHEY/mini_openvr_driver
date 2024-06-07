#include <iostream>
#include <opencv2/opencv.hpp>
#include "aruco/aruco.hpp"
#include "log/logger.hpp"

using namespace std;
using namespace cv;

int main()
{
    build_logger("logger", "trace", "logs/rotation.log");

    int camId = 0;
    VideoCapture inputVideo;
    inputVideo.open(camId);
    if(!inputVideo.isOpened())
    {
        std::cout << "can not open web camera" << std::endl;
        return -1;
    }
    inputVideo.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    inputVideo.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
    inputVideo.set(cv::CAP_PROP_FPS, 30);
    
    int iMarkerNumX = 5;
    int iMarkerNumY = 7;
    float fMarkerLength = 100.0f;
    float fMarkerSeparation = 10.0f;
    int iDictionaryId = 10;
    bool bShowRejected = false;
    bool bRefindStrategy = false;

    int iInWidth = 1280;
    int iInHeight = 720;
    int iInFPS = 30;
    float fpCameraMatrix[] = {
        640,		0,			640,
        0,			640,		360,
        0,			0,			1.0
    };
    float fpDistCoeffs[] = {0.0, 0.0, 0.0, 0.0};

    Aruco detector;
    detector.config(iInWidth, iInHeight, iMarkerNumX, iMarkerNumY, fMarkerLength, fMarkerSeparation, iDictionaryId, bShowRejected, bRefindStrategy, fpCameraMatrix, fpDistCoeffs);

    double dpRotation[4];
	double dpTranslation[3];
	bool bDrawArucoImg = true;
    while(inputVideo.grab())
    {
        Mat image;
        inputVideo.retrieve(image);
        // std::cout << "image width: " << image.cols << ", height: " << image.rows << std::endl;
        detector.detect_board(image.data, dpRotation, dpTranslation, bDrawArucoImg);
        imshow("image", image);
        waitKey(1);
    }
}
