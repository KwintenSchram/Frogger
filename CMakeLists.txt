cmake_minimum_required(VERSION 3.15)
project(Frogger VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find SDL2
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

# Source files
set(SOURCES
    src/start.cpp
    src/Game.cpp
    src/Level.cpp
    src/abstract/Animator.cpp
    src/abstract/Entity.cpp
    src/abstract/Events.cpp
    src/abstract/Factory.cpp
    src/abstract/Row.cpp
    src/abstract/Window.cpp
    src/abstract/entities/Item.cpp
    src/abstract/entities/Lane.cpp
    src/abstract/entities/Obstacle.cpp
    src/abstract/entities/Player.cpp
    src/abstract/entities/Projectile.cpp
    src/abstract/entities/Props.cpp
    src/concrete/EventsSDL.cpp
    src/concrete/FactorySDL.cpp
    src/concrete/SDLdata.cpp
    src/concrete/WindowSDL.cpp
    src/concrete/entities/ItemSDL.cpp
    src/concrete/entities/LaneSDL.cpp
    src/concrete/entities/ObstacleSDL.cpp
    src/concrete/entities/PlayerSDL.cpp
    src/concrete/entities/ProjectileSDL.cpp
    src/levelGenerator/LevelProperties.cpp
    src/levelGenerator/RowProp.cpp
    src/menu/Menu.cpp
    src/menu/MenuButton.cpp
)

# Create executable
add_executable(Frogger ${SOURCES})

# Include directories
target_include_directories(Frogger PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link SDL2
target_link_libraries(Frogger PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    $<TARGET_NAME_IF_EXISTS:SDL2_image::SDL2_image>
    $<TARGET_NAME_IF_EXISTS:SDL2_ttf::SDL2_ttf>
)

# Windows specific settings
if(WIN32)
    # Set subsystem to Windows (not console) for release builds
    set_target_properties(Frogger PROPERTIES
        WIN32_EXECUTABLE $<IF:$<CONFIG:Debug>,FALSE,TRUE>
    )

    # Copy SDL2 DLLs to output directory on Windows
    if(TARGET SDL2::SDL2)
        add_custom_command(TARGET Frogger POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL2::SDL2>
            $<TARGET_FILE_DIR:Frogger>
            COMMENT "Copying SDL2 DLL to output directory"
        )
    endif()

    if(TARGET SDL2_image::SDL2_image)
        add_custom_command(TARGET Frogger POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL2_image::SDL2_image>
            $<TARGET_FILE_DIR:Frogger>
            COMMENT "Copying SDL2_image DLL to output directory"
        )
    endif()

    if(TARGET SDL2_ttf::SDL2_ttf)
        add_custom_command(TARGET Frogger POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL2_ttf::SDL2_ttf>
            $<TARGET_FILE_DIR:Frogger>
            COMMENT "Copying SDL2_ttf DLL to output directory"
        )
    endif()
endif()

# Installation rules
install(TARGETS Frogger DESTINATION bin)

# Print build configuration
message(STATUS "Frogger configuration:")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
