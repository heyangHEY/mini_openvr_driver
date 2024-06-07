#pragma once

#include "define.hpp"
#include "aruco/aruco.hpp"
#include <thread>
#include <opencv2/opencv.hpp>

class CDeviceDriver_Aruco: public vr::ITrackedDeviceServerDriver
{
public:
    CDeviceDriver_Aruco();

    virtual vr::EVRInitError Activate( uint32_t unObjectId ) override final;
    virtual void Deactivate() override final;
    virtual void EnterStandby() override final;
    virtual void *GetComponent( const char *pchComponentNameAndVersion ) override final;
    virtual void DebugRequest( const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize ) override final;
    virtual vr::DriverPose_t GetPose() override final;

    void RunFrame();

private:
    vr::TrackedDeviceIndex_t m_tracked_device_index;
    vr::PropertyContainerHandle_t m_property_container;

    int camId = 0;
    cv::VideoCapture inputVideo;
    std::shared_ptr<Aruco> detector;
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
    float fpCameraMatrix[9] = {
        640,		0,			640,
        0,			640,		360,
        0,			0,			1.0
    };
    float fpDistCoeffs[4] = {0.0, 0.0, 0.0, 0.0};

    double dpQuaternion[4] = {1.0, 0.0, 0.0, 0.0}; // first w
	double dpTranslation[3] = {0.0, 0.0, 0.0};
	bool bDrawArucoImg = true;
};
