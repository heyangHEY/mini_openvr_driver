#include "ovrd_interface.hpp"
#include <cstring>
#include "logger.hpp"

DLL_EXPORT void *HmdDriverFactory(const char *pInterfaceName, int *pReturnCode)
{
	build_logger("logger", "debug", "D:/workspace/mini_openvr_driver/logs/rotation.log");
	LOG_I("pInterfaceName: {}", pInterfaceName);

	if( 0 == strcmp(vr::IServerTrackedDeviceProvider_Version, pInterfaceName ) )
	{
		return new CTrackedDeviceProvider();
	}

	if( pReturnCode )
	{
		*pReturnCode = vr::VRInitError_Init_InterfaceNotFound;
	}

	return nullptr;
}
