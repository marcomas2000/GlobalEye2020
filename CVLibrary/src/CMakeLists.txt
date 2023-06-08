set (SOURCES Camera.cpp
             Frame.cpp
)

add_library(CVLibrary STATIC ${SOURCES})
target_include_directories(CVLibrary PUBLIC ${OpenCV_INCLUDE_DIRS} )