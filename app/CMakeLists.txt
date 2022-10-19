add_executable(shell-app main.cpp detector.cpp robot.cpp tracker.cpp utils.cpp)
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)
target_link_libraries(shell-app PUBLIC ${OpenCV_LIBS})