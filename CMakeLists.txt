cmake_minimum_required(VERSION 3.12)
project(sfml_hello)

set(CMAKE_CXX_STANDARD 14)

add_executable(sfml_hello main.cpp Collision.cpp Collision.h)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()