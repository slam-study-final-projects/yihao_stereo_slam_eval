cmake_minimum_required( VERSION 2.8 )

project(final_project)
# set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_BUILD_TYPE "RelWithDebInfo")
# set( CMAKE_CXX_FLAGS "-O3" )
set( CMAKE_CXX_FLAGS "-O1" )

include_directories("/usr/include/eigen3")
find_package(OpenCV REQUIRED)
find_package(Sophus REQUIRED)
find_package(Pangolin REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} ${Sophus_INCLUDE_DIRS} ${Pangolin_INCLUDE_DIRS})

Find_Package(Eigen3 REQUIRED)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${EIGEN3_INCLUDE_DIR}) 

add_library(depth_generator STATIC
  depth_generator.h
  depth_generator.cc
)

target_link_libraries(depth_generator
  ${OpenCV_LIBS}
)

add_library(orb_matcher STATIC
  orb_matcher.h
  orb_matcher.cc
)

target_link_libraries(orb_matcher
  ${OpenCV_LIBS}
)

add_library(icp_translator STATIC
  icp_translator.h
  icp_translator.cc
)

target_link_libraries(icp_translator
  ${OpenCV_LIBS}
)

add_library(slam_work STATIC
  slam_work.h
  slam_work.cc
)

target_link_libraries(slam_work
  depth_generator orb_matcher icp_translator 
  ${OpenCV_LIBS}
)

add_executable(final_project final_project.cpp)
target_link_libraries(final_project slam_work ${OpenCV_LIBS} ${Sophus_LIBRARIES} ${Pangolin_LIBRARIES})
