cmake_minimum_required(VERSION 3.12)
project(sfml_hello)

set(CMAKE_CXX_STANDARD 14)

add_executable(sfml_hello src/main.cpp src/Collision.cpp src/Collision.h src/Entities/Sprite.cpp src/Entities/Sprite.h src/Entities/SpaceShip.cpp src/Entities/SpaceShip.h src/Entities/Fire.cpp src/Entities/Fire.h src/Entities/Alien.cpp src/Entities/Alien.h src/game.h src/game.cpp)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()