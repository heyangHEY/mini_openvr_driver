// Copyright (C) 2000-2022, Intel Corporation, all rights reserved.
// Copyright (C) 2009-2011, Willow Garage Inc., all rights reserved.
// Copyright (C) 2009-2016, NVIDIA Corporation, all rights reserved.
// Copyright (C) 2010-2013, Advanced Micro Devices, Inc., all rights reserved.
// Copyright (C) 2015-2023, OpenCV Foundation, all rights reserved.
// Copyright (C) 2008-2016, Itseez Inc., all rights reserved.
// Copyright (C) 2019-2023, Xperience AI, all rights reserved.
// Copyright (C) 2019-2022, Shenzhen Institute of Artificial Intelligence and Robotics for Society, all rights reserved.
// Copyright (C) 2022-2023, Southern University of Science And Technology, all rights reserved.
// Copyright (C) 2024-2024, heyangHEY, all rights reserved.

// Third party copyrights are property of their respective owners.

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <opencv2/opencv.hpp>
#include "log/logger.hpp"
#include "aruco.hpp"

using namespace std;
using namespace cv;

// 参考：https://github.com/opencv/opencv/blob/4.10.0/samples/cpp/tutorial_code/objectDetection/detect_board.cpp
bool Aruco::config(int imgWidth, int imgHeight, int markerNumX, int markerNumY, float markerLength, float markerSeparation, int dictionaryId, bool bShowRejected, bool bRefindStrategy, float fpCameraMatrix[], float fpDistCoeffs[])
{
    this->imgWidth = imgWidth;
    this->imgHeight = imgHeight;
    this->markerNumX = markerNumX; // markersX
    this->markerNumY = markerNumY; // markersY
    this->markerLength = markerLength;
    this->markerSeparation = markerSeparation;
    this->dictionaryId = dictionaryId;
    this->bShowRejected = bShowRejected;
    this->bRefindStrategy = bRefindStrategy;
    this->fpCameraMatrix = fpCameraMatrix;
    this->fpDistCoeffs = fpDistCoeffs;
    this->mCameraMatrix = cv::Mat(3, 3, CV_32FC1, fpCameraMatrix);
    this->mDistCoeffs = cv::Mat(1, 4, CV_32FC1, fpDistCoeffs);

    aruco::DetectorParameters detectorParams = (aruco::DetectorParameters());
    detectorParams.cornerRefinementMethod = aruco::CORNER_REFINE_SUBPIX; // do corner refinement in markers // 使用算法提高角点检测精度
    aruco::Dictionary dictionary = aruco::getPredefinedDictionary(dictionaryId);
    detector = std::make_shared<aruco::ArucoDetector>(aruco::ArucoDetector(dictionary, detectorParams));

    axisLength = 0.5f * ((float)min(markerNumX, markerNumY) * (markerLength + markerSeparation) +
        markerSeparation);

    // Create GridBoard object
    gridboard = std::make_shared<aruco::GridBoard>(aruco::GridBoard(Size(markerNumX, markerNumY), markerLength, markerSeparation, dictionary));
    // // Also you could create Board object
    // board = gridboard.staticCast<aruco::Board>();
    return EXIT_SUCCESS;
}

void Aruco::detect_board(uchar* rawImgData, double* dpRotation, double* dpTranslation, bool bDrawImg)
{
    Mat image = cv::Mat(imgHeight, imgWidth, CV_8UC3, rawImgData, 0);

    double tick = (double)getTickCount(); // 98行

    vector< int > ids;
    vector< vector< Point2f > > corners, rejected;

    // detect markers
    detector->detectMarkers(image, corners, ids, rejected);

    // refind strategy to detect more markers
    if (bRefindStrategy)
        detector->refineDetectedMarkers(image, *gridboard, corners, ids, rejected, mCameraMatrix,
            mDistCoeffs);

    // estimate board pose
    int markersOfBoardDetected = 0;
    if (!ids.empty())
    {
        cv::Mat objPoints, imgPoints;
        gridboard->matchImagePoints(corners, ids, objPoints, imgPoints);
        cv::solvePnP(objPoints, imgPoints, mCameraMatrix, mDistCoeffs, rvec, tvec);
        markersOfBoardDetected = (int)objPoints.total() / 4;
    }

    double currentTime = ((double)getTickCount() - tick) / getTickFrequency();
    totalTime += currentTime;
    totalIterations++;
    if (totalIterations % 30 == 0) {
        // cout << "Detection Time = " << currentTime * 1000 << " ms "
        //     << "(Mean = " << 1000 * totalTime / double(totalIterations) << " ms)" << endl;
        LOG_T("Detection Time = {} ms, (Mean = {} ms)", currentTime * 1000, 1000 * totalTime / double(totalIterations));
    }

    // draw results
    if (bDrawImg)
    {
        if (!ids.empty()) {
            aruco::drawDetectedMarkers(image, corners, ids);
        }

        if (bShowRejected && !rejected.empty())
            aruco::drawDetectedMarkers(image, rejected, noArray(), Scalar(100, 0, 255));

        if (markersOfBoardDetected > 0)
            cv::drawFrameAxes(image, mCameraMatrix, mDistCoeffs, rvec, tvec, axisLength);
    }

    cv::Mat mRotation;
    cv::Rodrigues(rvec, mRotation);
    double r11 = mRotation.at<double>(0, 0);
    double r12 = mRotation.at<double>(0, 1);
    double r13 = mRotation.at<double>(0, 2);
    double r21 = mRotation.at<double>(1, 0);
    double r22 = mRotation.at<double>(1, 1);
    double r23 = mRotation.at<double>(1, 2);
    double r31 = mRotation.at<double>(2, 0);
    double r32 = mRotation.at<double>(2, 1);
    double r33 = mRotation.at<double>(2, 2);

    double qw = sqrt(1 + r11 + r22 + r33) / 2;
    dpRotation[0] = qw; // w
    dpRotation[1] = (r32 - r23) / (4 * qw); // x
    dpRotation[2] = (r13 - r31) / (4 * qw); // y
    dpRotation[3] = (r21 - r12) / (4 * qw); // z

    for (int i = 0; i < 3; i++)
    {
        dpTranslation[i] = tvec.val[i];
    }
}
