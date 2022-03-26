cmake_minimum_required(VERSION 3.20)

project(
    cmake_finding_things
    VERSION 0.1
    DESCRIPTION "Test CMake package and app searching capabilities"
    LANGUAGES C CXX
    )

if("Windows" STREQUAL ${CMAKE_SYSTEM_NAME})
    set(IMAGE_MAGICK_HOME "C:/Program Files/ImageMagick-7.1.0-Q16-HDRI")

elseif(
        "Linux" STREQUAL ${CMAKE_SYSTEM_NAME}
        OR "FreeBSD" STREQUAL ${CMAKE_SYSTEM_NAME}
        )
    findpackage(ImageMagick)

else()
    message("-- Not implemented platform!")
    message("-- Aborting!")
    return()

endif()

message("ImageMagick home: ${IMAGE_MAGICK_HOME}")
