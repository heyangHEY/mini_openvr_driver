cmake_minimum_required(VERSION 3.10)
project(MINI_OpenVR_Driver CXX)

set(CMAKE_CXX_STANDARD 17)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

set(OPENVR_LIB_DIR ${CMAKE_SOURCE_DIR}/external/openvr/lib/win64 CACHE STRING "OpenVR .lib directory")
set(OPENVR_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/openvr/headers CACHE STRING "OpenVR include directory")
set(OPENVR_IMPLEMENTATION_DIR ${CMAKE_SOURCE_DIR}/external/openvr/bin/win64 CACHE STRING "OpenVR implementation (dll, so, dylib)")

# Driver DLL
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)
add_library(mini SHARED ${SOURCES};${HEADERS})
target_compile_features(mini PRIVATE cxx_std_17)
target_compile_definitions(mini PUBLIC -D_EXPORT)
target_include_directories(mini PRIVATE include/)
target_include_directories(mini PRIVATE ${OPENVR_INCLUDE_DIR})
target_link_libraries(mini ${OPENVR_LIB_DIR}/openvr_api.lib)
set_target_properties(mini PROPERTIES PREFIX "driver_")

# installer stuff
install(TARGETS mini
  DESTINATION mini/bin/win64
  COMPONENT driver)

install(FILES
  ${OPENVR_IMPLEMENTATION_DIR}/openvr_api.dll
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
