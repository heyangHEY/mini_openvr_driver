#include "device_aruco.hpp"
#include <string.h>
#include "log/logger.hpp"

CDeviceDriver_Aruco::CDeviceDriver_Aruco()
{
    LOG_I("CDeviceDriver_Aruco::CDeviceDriver_Aruco()");
}

vr::EVRInitError CDeviceDriver_Aruco::Activate( uint32_t unObjectId )
{
    LOG_I("CDeviceDriver_Aruco::Activate()");
    m_tracked_device_index = unObjectId;
    m_property_container = vr::VRProperties()->TrackedDeviceToPropertyContainer(m_tracked_device_index);
    vr::VRProperties()->SetStringProperty(m_property_container, vr::Prop_SerialNumber_String, "1023");
    // vr::VRProperties()->SetStringProperty(m_property_container, vr::Prop_ModelNumber_String, "0");

    inputVideo.open(camId);
    if(!inputVideo.isOpened())
    {
        std::cout << "can not open web camera" << std::endl;
        return vr::VRInitError_Unknown;
    }
    inputVideo.set(cv::CAP_PROP_FRAME_WIDTH, iInWidth);
    inputVideo.set(cv::CAP_PROP_FRAME_HEIGHT, iInHeight);
    inputVideo.set(cv::CAP_PROP_FPS, iInFPS);
    detector = std::make_shared<Aruco>(Aruco());
    detector->config(iInWidth, iInHeight, iMarkerNumX, iMarkerNumY, fMarkerLength, fMarkerSeparation, iDictionaryId, bShowRejected, bRefindStrategy, fpCameraMatrix, fpDistCoeffs);
    
    return vr::VRInitError_None;
}

// 当VR系统从这个Hmd切换到另一个Hmd作为活动显示时调用，驱动程序应在被停用时清理尽可能多的内存和线程使用。
void CDeviceDriver_Aruco::Deactivate()
{
    LOG_I("CDeviceDriver_Aruco::Deactivate()");
    m_tracked_device_index = vr::k_unTrackedDeviceIndexInvalid;
}

// 处理系统的请求，将此设备置于待机模式。
void CDeviceDriver_Aruco::EnterStandby() {}

// 请求驱动程序的组件接口，用于设备特定的功能。
void *CDeviceDriver_Aruco::GetComponent( const char *pchComponentNameAndVersion )
{
    LOG_I("CDeviceDriver_Aruco::GetComponent()");
    return nullptr;
}

// VR客户端已向驱动程序提出此调试请求。
void CDeviceDriver_Aruco::DebugRequest( const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize )
{
    LOG_I("CDeviceDriver_Aruco::DebugRequest()");
    if(unResponseBufferSize >= 1)
    {
        pchResponseBuffer[0] = 0;
    }
}

vr::DriverPose_t CDeviceDriver_Aruco::GetPose()
{
    LOG_I("CDeviceDriver_Aruco::GetPose()");
    if(inputVideo.grab())
    {
        cv::Mat image;
        inputVideo.retrieve(image);
        // std::cout << "image width: " << image.cols << ", height: " << image.rows << std::endl;
        detector->detect_board(image.data, dpQuaternion, dpTranslation, bDrawArucoImg);
        imshow("image", image);
        cv::waitKey(1);
    }
    vr::DriverPose_t t = {0};
    t.poseIsValid = true;
    t.deviceIsConnected = true;
    t.result = vr::TrackingResult_Running_OK;
    t.qRotation = vr::HmdQuaternion_t({dpQuaternion[0], dpQuaternion[1], dpQuaternion[2], dpQuaternion[3]});
    t.vecPosition[0] = dpTranslation[0];
    t.vecPosition[1] = dpTranslation[1];
    t.vecPosition[2] = dpTranslation[2];
    t.qWorldFromDriverRotation = vr::HmdQuaternion_t{1, 0, 0, 0}; // w=1.0
    t.qDriverFromHeadRotation = vr::HmdQuaternion_t{1, 0, 0, 0}; // w=1.0

    LOG_T("pose t: [{}, {}, {}], q: [{}, {}, {}, {}]", dpTranslation[0], dpTranslation[1], dpTranslation[2], 
        dpQuaternion[0], dpQuaternion[1], dpQuaternion[2], dpQuaternion[3]);

    return t;
}

void CDeviceDriver_Aruco::RunFrame()
{
    LOG_I("CDeviceDriver_Aruco::RunFrame()");
    if(m_tracked_device_index != vr::k_unTrackedDeviceIndexInvalid)
    {
        vr::VRServerDriverHost()->TrackedDevicePoseUpdated(m_tracked_device_index, GetPose(), sizeof(vr::DriverPose_t));
    }
}
