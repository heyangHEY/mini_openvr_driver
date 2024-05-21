#include "device_provider.hpp"
#include "logger.hpp"

vr::EVRInitError CTrackedDeviceProvider::Init(vr::IVRDriverContext *pDriverContext)
{
    VR_INIT_SERVER_DRIVER_CONTEXT(pDriverContext);
    LOG_I("CTrackedDeviceProvider::Init()");

    m_pHmd = std::make_unique<CDeviceDriver_Hmd>();
    vr::VRServerDriverHost()->TrackedDeviceAdded("1024", vr::TrackedDeviceClass_HMD, m_pHmd.get()); // hmd serial number
    return vr::VRInitError_None;
}

void CTrackedDeviceProvider::Cleanup()
{
    LOG_I("CTrackedDeviceProvider::Cleanup()");
    m_pHmd = nullptr;
}

void CTrackedDeviceProvider::RunFrame()
{
    LOG_I("CTrackedDeviceProvider::RunFrame()");
    if(m_pHmd)
    {
        m_pHmd->RunFrame();
    }

    struct vr::VREvent_t event;
    while(vr::VRServerDriverHost()->PollNextEvent(&event, sizeof(struct vr::VREvent_t))){}
}

const char * const *CTrackedDeviceProvider::GetInterfaceVersions() { return vr::k_InterfaceVersions; }
bool CTrackedDeviceProvider::ShouldBlockStandbyMode() { return true; }
void CTrackedDeviceProvider::EnterStandby() {}
void CTrackedDeviceProvider::LeaveStandby() {}
