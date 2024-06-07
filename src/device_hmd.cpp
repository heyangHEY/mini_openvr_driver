#include "device_hmd.hpp"
#include <string.h>
#include "log/logger.hpp"

CDeviceDriver_Hmd::CDeviceDriver_Hmd()
{
    LOG_I("CDeviceDriver_Hmd::CDeviceDriver_Hmd()");
    vr::VRSettings()->SetFloat(vr::k_pch_SteamVR_Section, vr::k_pch_SteamVR_IPD_Float, static_cast<float>(0.0f));
}

vr::EVRInitError CDeviceDriver_Hmd::Activate( uint32_t unObjectId )
{
    LOG_I("CDeviceDriver_Hmd::Activate()");
    m_tracked_device_index = unObjectId;
    m_property_container = vr::VRProperties()->TrackedDeviceToPropertyContainer(m_tracked_device_index);
    vr::VRProperties()->SetStringProperty(m_property_container, vr::Prop_SerialNumber_String, "1024");
    vr::VRProperties()->SetStringProperty(m_property_container, vr::Prop_ModelNumber_String, "0");
    vr::VRProperties()->SetStringProperty(m_property_container, vr::Prop_RenderModelName_String, "0");
    vr::VRProperties()->SetFloatProperty(m_property_container, vr::Prop_UserIpdMeters_Float, static_cast<float>(0.0f));
    vr::VRProperties()->SetBoolProperty(m_property_container, vr::Prop_HasDriverDirectModeComponent_Bool, false);
    vr::VRProperties()->SetFloatProperty(m_property_container, vr::Prop_DisplayFrequency_Float, static_cast<float>(60.0f));
    vr::VRProperties()->SetFloatProperty(m_property_container, vr::Prop_SecondsFromVsyncToPhotons_Float, static_cast<float>(0.0f));
    vr::VRProperties()->SetFloatProperty(m_property_container, vr::Prop_UserHeadToEyeDepthMeters_Float, static_cast<float>(0.0f));
    vr::VRProperties()->SetUint64Property(m_property_container, vr::Prop_CurrentUniverseId_Uint64, 2);
    return vr::VRInitError_None;
}

// 当VR系统从这个Hmd切换到另一个Hmd作为活动显示时调用，驱动程序应在被停用时清理尽可能多的内存和线程使用。
void CDeviceDriver_Hmd::Deactivate()
{
    LOG_I("CDeviceDriver_Hmd::Deactivate()");
    m_tracked_device_index = vr::k_unTrackedDeviceIndexInvalid;
}

// 处理系统的请求，将此设备置于待机模式。
void CDeviceDriver_Hmd::EnterStandby() {}

// 请求驱动程序的组件接口，用于设备特定的功能。
void *CDeviceDriver_Hmd::GetComponent( const char *pchComponentNameAndVersion )
{
    LOG_I("CDeviceDriver_Hmd::GetComponent()");
    // strcmp 区分大小写
    // stricmp 非标准函数，不区分大小写
    // if(strcmp(pchComponentNameAndVersion, vr::IVRDisplayComponent_Version) == 0)
    if(stricmp(pchComponentNameAndVersion, vr::IVRDisplayComponent_Version) == 0)
    {
        return static_cast<vr::IVRDisplayComponent *>(this);
    }
    return nullptr;
}

// VR客户端已向驱动程序提出此调试请求。
void CDeviceDriver_Hmd::DebugRequest( const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize )
{
    LOG_I("CDeviceDriver_Hmd::DebugRequest()");
    if(unResponseBufferSize >= 1)
    {
        pchResponseBuffer[0] = 0;
    }
}

vr::DriverPose_t CDeviceDriver_Hmd::GetPose()
{
    LOG_I("CDeviceDriver_Hmd::GetPose()");
    vr::DriverPose_t t = {0};
    t.poseIsValid = true;
    t.deviceIsConnected = true;
    t.result = vr::TrackingResult_Running_OK;
    t.qRotation = vr::HmdQuaternion_t{1, 0, 0, 0};
    t.qWorldFromDriverRotation = vr::HmdQuaternion_t{1, 0, 0, 0}; // w=1.0
    t.qDriverFromHeadRotation = vr::HmdQuaternion_t{1, 0, 0, 0}; // w=1.0
    return t;
}

// 获取VR显示窗口的大小和位置
void CDeviceDriver_Hmd::GetWindowBounds( int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight )
{
    LOG_I("CDeviceDriver_Hmd::GetWindowBounds()");
    // hmd 插入 pc 后，为拓展屏，在显示设置中，将拓展屏调整到主屏合适的位置。
    // offset 为 拓展屏原点 相对于 主屏原点 的偏移。定义“屏幕原点”为“屏幕左上角第一个像素”，主屏原点坐标为 [0, 0]。
    // 假设：主屏右边为拓展屏，主屏分辨率为 1920*1080，拓展屏为 Side by side 模式，3840*1080，则：
    *pnX = 2560; // offset_x = 3840
    *pnY = 0; // offset_y = 0
    *pnWidth = 3840; // width = 3840
    *pnHeight = 1080; // height = 1080
}

// 判断VR显示是否在桌面上扩展
bool CDeviceDriver_Hmd::IsDisplayOnDesktop()
{
    LOG_I("CDeviceDriver_Hmd::IsDisplayOnDesktop()");
    return true;
}

// 判断VR显示是否为真实显示，而非虚构显示
bool CDeviceDriver_Hmd::IsDisplayRealDisplay()
{
    LOG_I("CDeviceDriver_Hmd::IsDisplayRealDisplay()");
    return true;
}

// 获取建议的渲染目标大小
void CDeviceDriver_Hmd::GetRecommendedRenderTargetSize( uint32_t *pnWidth, uint32_t *pnHeight )
{
    LOG_I("CDeviceDriver_Hmd::GetRecommendedRenderTargetSize()");
    *pnWidth = 3840; // 3840 * 1.4 = 5376
    *pnHeight = 1080; // 1080 * 1.4 = 1512
}

// 获取帧缓冲区中的视口，以绘制失真输出。
void CDeviceDriver_Hmd::GetEyeOutputViewport( vr::EVREye eEye, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight )
{
    LOG_I("CDeviceDriver_Hmd::GetEyeOutputViewport()");
    // left: eEye = 0; right eEye = 1
    // 设置左右眼的视口矩阵参数
    // 比如，若拓展屏为 3840*1080，SBS模式：左半边显示左眼的内容，右半边显示右眼的内容。则:
    // 左眼的视口，size为[1920,1080]，原点坐标为[0,0]
    // 右眼的视口，size为[1920,1080]，原点坐标为[1920,0]
    if(eEye == vr::Eye_Left)
    {
        *pnX = 0;
        *pnY = 0;
        *pnWidth = 1920;
        *pnHeight = 1080;
    } else
    {
        *pnX = 1920;
        *pnY = 0;
        *pnWidth = 1920;
        *pnHeight = 1080;
    }
}

// 获取构建自定义投影矩阵所需的组件，这在应用程序需要进行一些特殊操作（如无限Z）时非常有用
void CDeviceDriver_Hmd::GetProjectionRaw( vr::EVREye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom )
{
    LOG_I("CDeviceDriver_Hmd::GetProjectionRaw()");
    if(eEye == vr::Eye_Left)
    {
        *pfLeft     = static_cast<float>(-0.299042533);
        *pfRight    = static_cast<float>(0.304215378);
        *pfTop      = static_cast<float>(-0.2455669);
        *pfBottom   = static_cast<float>(0.08854639);
    } else
    {
        *pfLeft     = static_cast<float>(-0.261943438);
        *pfRight    = static_cast<float>(0.352588622);
        *pfTop      = static_cast<float>(-0.240336522);
        *pfBottom   = static_cast<float>(0.0948431145);
    }
}

// 计算指定眼睛和输入UV的失真函数结果。UV从该眼的视口的左上角的0,0开始，到右下角的1,1结束
vr::DistortionCoordinates_t CDeviceDriver_Hmd::ComputeDistortion( vr::EVREye eEye, float fU, float fV )
{
    LOG_I("CDeviceDriver_Hmd::ComputeDistortion()");
    vr::DistortionCoordinates_t coordinates;
    coordinates.rfBlue[0] = fU;
    coordinates.rfBlue[1] = fV;
    coordinates.rfGreen[0] = fU;
    coordinates.rfGreen[1] = fV;
    coordinates.rfRed[0] = fU;
    coordinates.rfRed[1] = fV;
    return coordinates;
}

bool CDeviceDriver_Hmd::ComputeInverseDistortion( vr::HmdVector2_t *pResult, vr::EVREye eEye, uint32_t unChannel, float fU, float fV )
{
    LOG_I("CDeviceDriver_Hmd::ComputeInverseDistortion()");
    return false;
}

void CDeviceDriver_Hmd::RunFrame()
{
    LOG_I("CDeviceDriver_Hmd::RunFrame()");
    if(m_tracked_device_index != vr::k_unTrackedDeviceIndexInvalid)
    {
        vr::VRServerDriverHost()->TrackedDevicePoseUpdated(m_tracked_device_index, GetPose(), sizeof(vr::DriverPose_t));
    }

    if(!eye2head_flag)
    {
        eye2head_flag = true;
        vr::HmdMatrix34_t left = {0};
        left.m[0][0] = static_cast<float>(0.99985095901973708);
        left.m[0][1] = static_cast<float>(0.017199587942883298);
        left.m[0][2] = -static_cast<float>(0.0014946310271570784);
        left.m[0][3] = static_cast<float>(-0.034631866021305933);
        left.m[1][0] = static_cast<float>(-0.017218996322680494);
        left.m[1][1] = static_cast<float>(0.9997520041410104);
        left.m[1][2] = -static_cast<float>(0.014122194647885458);
        left.m[1][3] = static_cast<float>(-0.038042607191872788);
        left.m[2][0] = -static_cast<float>(-0.0012513644360586662);
        left.m[2][1] = -static_cast<float>(-0.014145825908312055);
        left.m[2][2] = static_cast<float>(0.99989915976383337);
        left.m[2][3] = -static_cast<float>(-0.048461297583114918);
        vr::HmdMatrix34_t right = {0};
        right.m[0][0] = static_cast<float>(0.996603307028862);
        right.m[0][1] = static_cast<float>(0.056871838052233566);
        right.m[0][2] = -static_cast<float>(-0.059560410137072362);
        right.m[0][3] = static_cast<float>(0.034811510738390533);
        right.m[1][0] = static_cast<float>(-0.05702376201194824);
        right.m[1][1] = static_cast<float>(0.99837245720157708);
        right.m[1][2] = -static_cast<float>(-0.000852799677485976);
        right.m[1][3] = static_cast<float>(-0.040149668624768577);
        right.m[2][0] = -static_cast<float>(0.059414972735333804);
        right.m[2][1] = -static_cast<float>(0.0042462616318061294);
        right.m[2][2] = static_cast<float>(0.99822433865189519);
        right.m[2][3] = -static_cast<float>(-0.054257832333583687);

        vr::VRServerDriverHost()->SetDisplayEyeToHead(m_tracked_device_index, left, right);
    }
}
