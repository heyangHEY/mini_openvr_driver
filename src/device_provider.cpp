#include "device_provider.hpp"
#include "log/logger.hpp"

vr::EVRInitError CTrackedDeviceProvider::Init(vr::IVRDriverContext *pDriverContext)
{
    VR_INIT_SERVER_DRIVER_CONTEXT(pDriverContext);
    LOG_I("CTrackedDeviceProvider::Init()");

    m_pHmd = std::make_unique<CDeviceDriver_Hmd>();
    vr::VRServerDriverHost()->TrackedDeviceAdded("1024", vr::TrackedDeviceClass_HMD, m_pHmd.get()); // hmd serial number

    m_pAruco = std::make_shared<CDeviceDriver_Aruco>();
    vr::VRServerDriverHost()->TrackedDeviceAdded("1023", vr::TrackedDeviceClass_GenericTracker, m_pAruco.get()); // TODO

    return vr::VRInitError_None;
}

void CTrackedDeviceProvider::Cleanup()
{
    LOG_I("CTrackedDeviceProvider::Cleanup()");
    m_pHmd = nullptr;
    m_pAruco = nullptr;
}

void CTrackedDeviceProvider::RunFrame()
{
    LOG_I("CTrackedDeviceProvider::RunFrame()");
    if(m_pHmd)
    {
        m_pHmd->RunFrame();
    }
    if(m_pAruco)
    {
        m_pAruco->RunFrame();
    }

    struct vr::VREvent_t event;
    while(vr::VRServerDriverHost()->PollNextEvent(&event, sizeof(struct vr::VREvent_t))){}
}

const char * const *CTrackedDeviceProvider::GetInterfaceVersions() { return vr::k_InterfaceVersions; }
bool CTrackedDeviceProvider::ShouldBlockStandbyMode() { return true; }
void CTrackedDeviceProvider::EnterStandby() {}
void CTrackedDeviceProvider::LeaveStandby() {}
