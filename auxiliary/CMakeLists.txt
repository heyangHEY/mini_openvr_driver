add_library(aux_includes INTERFACE)
target_include_directories(aux_includes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(aux_log STATIC ${CMAKE_CURRENT_SOURCE_DIR}/log/logger.cpp)
target_link_libraries(aux_log PUBLIC aux_includes spdlog::spdlog)

add_subdirectory(aruco)
