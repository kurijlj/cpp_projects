cmake_minimum_required(VERSION 3.15)

#find_package(ImageMagick) 
#find_package(ImageMagick COMPONENTS Magick++)
#find_package(ImageMagick COMPONENTS convert)
#find_package(ImageMagick COMPONENTS Magick++ convert)

if(NOT DEFINED IMAGE_MAGICK_HOME)
    set(IMAGE_MAGICK_HOME "C:/Program Files/ImageMagick-7.1.0-Q16-HDRI")
endif()

set(IMAGE_MAGICK_INCLUDE "${IMAGE_MAGICK_HOME}/include")

if(EXISTS "${IMAGE_MAGICK_HOME}")
    message(STAUS "Looking for ImageMagick - found")
elseif()
    message(FATAL "Looking for ImageMagick - missing")
endif()
