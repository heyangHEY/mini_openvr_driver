cmake_minimum_required(VERSION 3.10)
project(MINI_OpenVR_Driver CXX)

set(CMAKE_CXX_STANDARD 17)
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

# Driver DLL
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)
add_library(mini SHARED ${SOURCES};${HEADERS})
target_compile_features(mini PRIVATE cxx_std_17)
target_compile_definitions(mini PUBLIC -D_EXPORT)
target_include_directories(mini PRIVATE include/)
set_target_properties(mini PROPERTIES PREFIX "driver_")

# installer stuff
install(TARGETS mini
	DESTINATION mini/bin/win64
	COMPONENT driver)

install(FILES
	${CMAKE_SOURCE_DIR}/resources/mini/driver.vrdrivermanifest
	DESTINATION mini
	COMPONENT driver)

install(FILES
	${CMAKE_SOURCE_DIR}/resources/mini/resources/settings/default.vrsettings
	DESTINATION mini/resources/settings
	COMPONENT driver)

include(InstallRequiredSystemLibraries)
install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}
	DESTINATION mini/bin/win64
	COMPONENT driver)

# 定义要复制的系统库文件的路径
set(SYSTEM_LIBS
	"C:/Windows/System32/ntdll.dll"
    "C:/Windows/System32/KERNEL32.DLL"
    "C:/Windows/System32/KERNELBASE.dll"
    "C:/Windows/System32/msvcrt.dll"
    "C:/Windows/System32/ucrtbase.dll"
    "C:/msys64/ucrt64/bin/libstdc++-6.dll"
    "C:/msys64/ucrt64/bin/libgcc_s_seh-1.dll"
    "C:/msys64/ucrt64/bin/libwinpthread-1.dll"
    "C:/Windows/System32/advapi32.dll"
    "C:/Windows/System32/sechost.dll"
    "C:/Windows/System32/bcrypt.dll"
    "C:/Windows/System32/RPCRT4.dll"
    "C:/Windows/System32/CRYPTBASE.DLL"
    "C:/Windows/System32/bcryptPrimitives.dll"
)

# 使用install命令将系统库文件复制到指定的安装目录
foreach(lib ${SYSTEM_LIBS})
    install(FILES ${lib} DESTINATION mini/bin/win64)
endforeach()
