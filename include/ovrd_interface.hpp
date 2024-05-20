#pragma once

#include "define.hpp"
#include "device_provider.hpp"

#ifdef _WIN32
    #define DLL_EXPORT extern "C" __declspec(dllexport)
#elif defined(__linux__)
    #define DLL_EXPORT __attribute__((visibility("default")))
#endif

DLL_EXPORT void *HmdDriverFactory(const char *pInterfaceName, int *pReturnCode);
