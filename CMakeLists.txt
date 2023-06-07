cmake_minimum_required(VERSION 3.25)
project(gimpsep-c-imp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

add_executable(gimpsep-c-imp main.cpp core/Gimpsep.cpp utils/FileReader.h utils/FileReader.cpp core/GimpsepVideo.cpp)

target_link_libraries(gimpsep-c-imp PRIVATE ${OpenCV_LIBS})
