cmake_minimum_required(VERSION 3.24)
project(Vicon LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

#set(BOOST_ROOT $ENV{HOME}/workspace/boost_1_80_0)
#set(Boost_INCLUDE_DIR ${BOOST_ROOT})
#set(Boost_LIBRARY_DIR ${BOOST_ROOT}/stage/lib)

set(lib "${CMAKE_CURRENT_SOURCE_DIR}/lib")
#message(${lib_space})
#add_subdirectory(${lib_space} ${CMAKE_BINARY_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
find_package(Eigen3 CONFIG REQUIRED)

#find_package(rclcpp REQUIRED)

function(create exec_name target_name)
    add_library(${exec_name} STATIC
            "${CMAKE_CURRENT_SOURCE_DIR}/src/${target_name}.cpp")
    set_target_properties(${exec_name} PROPERTIES LINKER_LANGUAGE CXX)
    target_include_directories(${exec_name} PUBLIC "${lib}/Linux64")
    target_include_directories(${exec_name} PUBLIC "${lib}/logger")
#    target_include_directories(${exec_name} PUBLIC "${lib}/Yaml")
    target_link_libraries(${exec_name} PUBLIC ${Boost_LIBRARIES})
    target_link_libraries(${exec_name} ${lib}/Linux64/libViconDataStreamSDK_CPP.so)
    if (CMAKE_BUILD_TYPE STREQUAL "RELEASE" OR CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_options(${exec_name} PRIVATE -mtune=native -fPIC -O3 -g -march=native)
    endif()
endfunction()

create(vicon vicon/vicon)

add_executable(main
        "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
target_link_libraries(main vicon)