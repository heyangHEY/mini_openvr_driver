cmake_minimum_required(VERSION 3.10)

# 必须放在project()之前，不然只会找到ucrt64下的库，或者编译时换成
# $ cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_TOOLCHAIN_FILE=/d/workspace/vcpkg/scripts/buildsystems/vcpkg.cmake
set(CMAKE_TOOLCHAIN_FILE "D:/workspace/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(MINI_OpenVR_Driver CXX)

if(BUILD_TYPE MATCHES Debug)
    message("Building Debug")
	set(VCPKG_INSTALLED_DIR "D:/workspace/vcpkg/installed/x64-windows/debug/bin")
elseif(BUILD_TYPE MATCHES Release)
    message("Building Release")
	set(VCPKG_INSTALLED_DIR "D:/workspace/vcpkg/installed/x64-windows/bin")
else()
    message("Building ${BUILD_TYPE}")
endif()

set(CMAKE_CXX_STANDARD 17)
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

function(check_package package_name)
	if(${package_name}_FOUND)
		message(STATUS "Found ${package_name} ${${package_name}_VERSION}: ${${package_name}_DIR}")
	else()
		message(FATAL_ERROR "Could not find ${package_name}")
	endif()
endfunction()

find_package(spdlog CONFIG REQUIRED)
check_package(spdlog)

add_executable(test_spdlog src/test_spdlog.cpp src/logger.cpp include/logger.hpp)
target_include_directories(test_spdlog PRIVATE include/)
target_link_libraries(test_spdlog PRIVATE spdlog::spdlog)

# Driver DLL
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)
add_library(mini SHARED ${SOURCES};${HEADERS})
target_compile_features(mini PRIVATE cxx_std_17)
target_compile_definitions(mini PUBLIC -D_EXPORT)
target_include_directories(mini PRIVATE include/)
target_link_libraries(mini PRIVATE spdlog::spdlog)
set_target_properties(mini PROPERTIES PREFIX "driver_")

# installer stuff
install(TARGETS mini
DESTINATION mini/bin/win64)

install(TARGETS test_spdlog
	DESTINATION mini/bin/win64)
install(CODE "
    include(BundleUtilities)
    fixup_bundle(\"${CMAKE_INSTALL_PREFIX}/mini/bin/win64/test_spdlog.exe\" \"\" \"${VCPKG_INSTALLED_DIR}\")
" COMPONENT Runtime)

install(FILES
	${CMAKE_SOURCE_DIR}/resources/mini/driver.vrdrivermanifest
	DESTINATION mini)

install(FILES
	${CMAKE_SOURCE_DIR}/resources/mini/resources/settings/default.vrsettings
	DESTINATION mini/resources/settings)

include(InstallRequiredSystemLibraries)
install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}
	DESTINATION mini/bin/win64)
