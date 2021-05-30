cmake_minimum_required(VERSION 2.8)
project(zhangCalibration)

# set compile information
set( CMAKE_CXX_COMPILER "g++" )
set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -march=native -O3" )


############### dependencies ######################
## find packages
# 添加cmake模块以使用ceres库
list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )
# ceres
find_package( Ceres REQUIRED )
include_directories( ${CERES_INCLUDE_DIRS} )
# Eigen
include_directories( "/usr/include/eigen3" )
# OpenCV
# set(OpenCV_DIR /usr/include)
find_package(OpenCV 3 REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
link_directories(${OpenCV_LIB_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})
list(APPEND LIBS ${LIBS} ${OpenCV_LIBS})
# g2o
include_directories(
        "/usr/local/include/g2o"
)
include_directories(
        ${G2O_INCLUDE_DIRS}
)
# set the location of libs to THIRD_PARTY_LIBS
set( THIRD_PARTY_LIBS
        ${OpenCV_LIBS}
        ${Sophus_LIBRARIES}
        ${CERES_LIBRARIES}
        g2o_core g2o_stuff g2o_types_sba
        )

## find include files
include_directories( ${PROJECT_SOURCE_DIR}/inc )


############### set configuration ######################
# set the location of exe file
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin )
# set the location of linked-lib file
set( LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib )
# set subdirectory
add_subdirectory( src )
add_subdirectory( test )