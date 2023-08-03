cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(CMAKE_CXX_COMPILER icpx)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Wno-unknown-pragmas -Wno-pass-failed -Wno-unneeded-internal-declaration -Wno-unused-function -Wno-gnu-anonymous-struct -Wno-nested-anon-types -Wno-extra-semi -Wno-unused-local-typedef -fsycl -fsycl-unnamed-lambda -ferror-limit=1")
project(registration)

find_package(PCL 1.12 REQUIRED)
find_package(PCL-ONEAPI 1.12 REQUIRED)



include_directories(${PCL_INCLUDE_DIRS} ${PCL-ONEAPI_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS} ${PCL-ONEAPI_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS} ${PCL-ONEAPI_DEFINITIONS})

file(COPY test_P.pcd test_Q.pcd DESTINATION ${CMAKE_BINARY_DIR} )

add_executable (oneapi_icp_example oneapi_icp_example.cpp)

add_custom_target(run ./oneapi_icp_example test_P.pcd test_Q.pcd )

#target_link_libraries (oneapi_icp_example pcl_oneapi_registration pcl_oneapi_search pcl_oneapi_kdtree pcl_io)

target_link_libraries ( oneapi_icp_example

                        #pcl_segmentation
                        pcl_oneapi_registration
                        pcl_oneapi_search
                        pcl_oneapi_kdtree
                        pcl_io
                        pcl_segmentation
)


