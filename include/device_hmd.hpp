#pragma once

#include "define.hpp"
#include <thread>

class CDeviceDriver_Hmd: public vr::ITrackedDeviceServerDriver, public vr::IVRDisplayComponent
{
public:
    CDeviceDriver_Hmd();

    virtual vr::EVRInitError Activate( uint32_t unObjectId ) override final;
    virtual void Deactivate() override final;
    virtual void EnterStandby() override final;
    virtual void *GetComponent( const char *pchComponentNameAndVersion ) override final;
    virtual void DebugRequest( const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize ) override final;
    virtual vr::DriverPose_t GetPose() override final;

    virtual void GetWindowBounds( int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight ) override final;
    virtual bool IsDisplayOnDesktop() override final;
    virtual bool IsDisplayRealDisplay() override final;
    virtual void GetRecommendedRenderTargetSize( uint32_t *pnWidth, uint32_t *pnHeight ) override final;
    virtual void GetEyeOutputViewport( vr::EVREye eEye, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight ) override final;
    virtual void GetProjectionRaw( vr::EVREye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom ) override final;
    virtual vr::DistortionCoordinates_t ComputeDistortion( vr::EVREye eEye, float fU, float fV ) override final;
    virtual bool ComputeInverseDistortion( vr::HmdVector2_t *pResult, vr::EVREye eEye, uint32_t unChannel, float fU, float fV ) override final;
    void RunFrame();

private:
    vr::TrackedDeviceIndex_t m_tracked_device_index;
    vr::PropertyContainerHandle_t m_property_container;
    bool eye2head_flag = false;
};
