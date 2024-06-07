add_library(aux_aruco aruco_detect_board.cpp aruco.hpp)
target_link_libraries(
    aux_aruco
    PUBLIC
        ${OpenCV_LIBS}
        aux_log
        aux_includes
)
