#pragma once

#include <memory>

#include "openvr_driver.h"
#include "device_hmd.hpp"

class CTrackedDeviceProvider: public vr::IServerTrackedDeviceProvider
{
public:
    CTrackedDeviceProvider() = default;
    virtual vr::EVRInitError Init( vr::IVRDriverContext *pDriverContext ) override final;
    virtual void Cleanup() override final;
    virtual void RunFrame() override final;

    virtual const char * const *GetInterfaceVersions() override final;
    virtual bool ShouldBlockStandbyMode() override final;
    virtual void EnterStandby() override final;
    virtual void LeaveStandby() override final;

private:
    std::unique_ptr<CDeviceDriver_Hmd> m_pHmd;
};
