cmake_minimum_required(VERSION 3.18)
project(frogger CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

add_executable(frogger WIN32 ${SOURCES})

# Target architecture for MinGW
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH_DIR "x86_64-w64-mingw32")
else()
    set(ARCH_DIR "i686-w64-mingw32")
endif()

# Auto-download MinGW SDL2 packages if not present
set(VENDOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor")
if(NOT EXISTS "${VENDOR_DIR}/SDL2-2.30.12")
    message(STATUS "Downloading SDL2 development libraries...")
    file(DOWNLOAD
        "https://github.com/libsdl-org/SDL/releases/download/release-2.30.12/SDL2-devel-2.30.12-mingw.zip"
        "${CMAKE_CURRENT_BINARY_DIR}/SDL2.zip"
        SHOW_PROGRESS
    )
    file(ARCHIVE_EXTRACT INPUT "${CMAKE_CURRENT_BINARY_DIR}/SDL2.zip" DESTINATION "${VENDOR_DIR}")
endif()

if(NOT EXISTS "${VENDOR_DIR}/SDL2_image-2.8.5")
    message(STATUS "Downloading SDL2_image development libraries...")
    file(DOWNLOAD
        "https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.5/SDL2_image-devel-2.8.5-mingw.zip"
        "${CMAKE_CURRENT_BINARY_DIR}/SDL2_image.zip"
        SHOW_PROGRESS
    )
    file(ARCHIVE_EXTRACT INPUT "${CMAKE_CURRENT_BINARY_DIR}/SDL2_image.zip" DESTINATION "${VENDOR_DIR}")
endif()

if(NOT EXISTS "${VENDOR_DIR}/SDL2_ttf-2.22.0")
    message(STATUS "Downloading SDL2_ttf development libraries...")
    file(DOWNLOAD
        "https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.22.0/SDL2_ttf-devel-2.22.0-mingw.zip"
        "${CMAKE_CURRENT_BINARY_DIR}/SDL2_ttf.zip"
        SHOW_PROGRESS
    )
    file(ARCHIVE_EXTRACT INPUT "${CMAKE_CURRENT_BINARY_DIR}/SDL2_ttf.zip" DESTINATION "${VENDOR_DIR}")
endif()

set(SDL2_DIR "${VENDOR_DIR}/SDL2-2.30.12/${ARCH_DIR}")
set(SDL2_IMAGE_DIR "${VENDOR_DIR}/SDL2_image-2.8.5/${ARCH_DIR}")
set(SDL2_TTF_DIR "${VENDOR_DIR}/SDL2_ttf-2.22.0/${ARCH_DIR}")

target_include_directories(frogger PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${SDL2_DIR}/include"
    "${SDL2_DIR}/include/SDL2"
    "${SDL2_IMAGE_DIR}/include"
    "${SDL2_IMAGE_DIR}/include/SDL2"
    "${SDL2_TTF_DIR}/include"
    "${SDL2_TTF_DIR}/include/SDL2"
)

target_link_directories(frogger PRIVATE
    "${SDL2_DIR}/lib"
    "${SDL2_IMAGE_DIR}/lib"
    "${SDL2_TTF_DIR}/lib"
)

target_link_libraries(frogger PRIVATE
    mingw32
    SDL2main
    SDL2
    SDL2_image
    SDL2_ttf
)

target_link_options(frogger PRIVATE
    -static-libgcc
    -static-libstdc++
)

# Copy all runtime DLLs to build directory
file(GLOB RUNTIME_DLLS
    "${SDL2_DIR}/bin/*.dll"
    "${SDL2_IMAGE_DIR}/bin/*.dll"
    "${SDL2_TTF_DIR}/bin/*.dll"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/runtime/*.dll"
)

add_custom_command(TARGET frogger POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${RUNTIME_DLLS}
        $<TARGET_FILE_DIR:frogger>
    COMMENT "Copying runtime DLLs"
)

add_custom_command(TARGET frogger POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/frogger"
        "$<TARGET_FILE_DIR:frogger>/frogger"
    COMMENT "Copying frogger assets"
)
