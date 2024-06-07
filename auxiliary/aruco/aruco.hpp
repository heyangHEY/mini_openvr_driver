#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect/aruco_detector.hpp>
#include <vector>
#include <iostream>


class Aruco
{
public:
    Aruco() {};
    ~Aruco() {};
    bool config(int imgWidth, int imgHeight, int markerNumX, int markerNumY, float markerLength, float markerSeparation, int dictionaryId, bool bShowRejected, bool bRefindStrategy, float fpCamMatrix[], float fpDistCoeffs[]);
    void detect_board(uchar* rawImgData, double* dpRotation, double* dpTranslation, bool bDrawImg);

private:
    int markerNumX;
    int markerNumY;
    float markerLength;
    float markerSeparation;
    int dictionaryId;
    bool bShowRejected;
    bool bRefindStrategy;
    cv::Mat mCameraMatrix;
    cv::Mat mDistCoeffs;
    float *fpCameraMatrix;
    float *fpDistCoeffs;
    std::string detectorParamsFile;
    int imgWidth;
    int imgHeight;

    float axisLength;
    cv::Ptr<cv::aruco::GridBoard> gridboard;
    cv::Ptr<cv::aruco::Board> board;
    cv::Ptr<cv::aruco::ArucoDetector> detector;

    cv::Vec3d rvec;
    cv::Vec3d tvec;
    double totalTime = 0;   
    int totalIterations = 0;
};
