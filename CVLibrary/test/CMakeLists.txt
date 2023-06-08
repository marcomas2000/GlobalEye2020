set (SOURCES main.cpp)

add_executable(testCVLibrary ${SOURCES})
target_include_directories(testCVLibrary PUBLIC ${PROJECT_SOURCE_DIR}/CVLibrary/src ${OpenCV_INCLUDE_DIRS} )
target_link_libraries(testCVLibrary ${OpenCV_LIBS} CVLibrary)