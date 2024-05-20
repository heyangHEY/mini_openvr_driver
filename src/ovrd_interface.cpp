#include "ovrd_interface.hpp"
#include <cstring>

DLL_EXPORT void *HmdDriverFactory(const char *pInterfaceName, int *pReturnCode)
{
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
