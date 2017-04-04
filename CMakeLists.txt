cmake_minimum_required (VERSION 2.8.8)
project (Simple-Web-Server)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

include_directories(.)

find_package(Threads REQUIRED)

set(BOOST_COMPONENTS system thread filesystem date_time)
# Late 2017 TODO: remove the following checks and always use std::regex
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9)
        set(BOOST_COMPONENTS ${BOOST_COMPONENTS} regex)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_BOOST_REGEX")
    endif()
endif()
find_package(Boost 1.53.0 COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIR})

if(APPLE)
    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
endif()

add_executable(simple_http_socket simple_http_socket.cpp)
target_link_libraries(simple_http_socket ${Boost_LIBRARIES})
target_link_libraries(simple_http_socket ${CMAKE_THREAD_LIBS_INIT})

add_executable(http_examples http_examples.cpp)
target_link_libraries(http_examples ${Boost_LIBRARIES})
target_link_libraries(http_examples ${CMAKE_THREAD_LIBS_INIT})


install(FILES server_http.hpp client_http.hpp server_https.hpp client_https.hpp DESTINATION include/simple-web-server)
