cmake_minimum_required(VERSION 3.16)
project(Alien)

set(CMAKE_CXX_STANDARD 17)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif (UNIX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_executable(Alien
        Menu.cpp
        GameMenu.cpp
        Creature.cpp
        Player.cpp
        Monster.cpp
        RandomNumberGenerator.cpp
        StartingMenu.cpp
        MainMenu.cpp
        Game.cpp
        AudioEngine.cpp
        Level.cpp
        Bullet.cpp
        Health.cpp
        main.cpp)


include_directories(./images)
include_directories(./audio)
include_directories(./fonts)

find_package(SFML 3.0 COMPONENTS Graphics Window System Audio REQUIRED)

target_link_libraries(Alien SFML::Graphics SFML::Window SFML::System SFML::Audio)
