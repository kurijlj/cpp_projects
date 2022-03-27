cmake_minimum_required(VERSION 3.15)

project(
    image_magick_test
    VERSION 0.1
    DESCRIPTION "Test crossplatform liniking mechanics for ImageMagick library"
    LANGUAGES C CXX
    )
find_package(ImageMagick) 
# find_package(ImageMagick COMPONENTS Magick++)
# find_package(ImageMagick COMPONENTS convert)
# find_package(ImageMagick COMPONENTS Magick++ convert)

if(NOT DEFINED IMAGE_MAGICK_HOME)
    set(IMAGE_MAGICK_HOME "C:/Program Files/ImageMagick-7.1.0-Q16-HDRI")
endif()

set(IMAGE_MAGICK_INCLUDE "${IMAGE_MAGICK_HOME}/include")

if(EXISTS "${IMAGE_MAGICK_HOME}")
    message(STATUS "Looking for ImageMagick - found")
elseif()
    message(FATAL "Looking for ImageMagick - missing")
endif()

# IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#    # Mac OS X specific code
#    SET(OperatingSystem "Mac OS X")
# ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
#    SET(OperatingSystem "Linux")
# ELSE()
#    SET(OperatingSystem "Others")
# ENDIF()

message(STATUS "${CMAKE_SYSTEM_NAME}")

# cmake_minimum_required(VERSION 2.8)
# project(ImageConverter)
# set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
# set(MY_MAGICK_PATH "D:/libraries/ImageMagick-6.5.9/")
# set(MY_MAGICK_LIB_PATH "D:/libraries/ImageMagick-6.5.9/VisualMagick/lib")
# find_package(wxWidgets COMPONENTS core base REQUIRED)
# include_directories(${wxWidgets_INCLUDE_DIRS}
#                     ${MY_MAGICK_PATH}
#                     ${MY_MAGICK_PATH}/magick
#                     ${MY_MAGICK_PATH}/Magick++
#                     ${MY_MAGICK_PATH}/Magick++/lib)
# add_definitions(${wxWidgets_DEFINITIONS})
# set(SRCS ${PROJECT_SOURCE_DIR}/ImageConverter/sources/ImageConverter.cpp)
# add_executable(ImageConverter WIN32 ${SRCS})
# target_link_libraries(ImageConverter ${wxWidgets_LIBRARIES}
#                         ${MY_MAGICK_LIB_PATH}/CORE_RL_bzlib_.lib
#                         ${MY_MAGICK_LIB_PATH}/CORE_RL_coders_.lib
#                         ${MY_MAGICK_LIB_PATH}/CORE_RL_filters_.lib
#                         ${MY_MAGICK_LIB_PATH}/CORE_RL_jbig_.lib
#                         ${MY_MAGICK_LIB_PATH}/CORE_RL_jp2_.lib
#                         ${MY_MAGICK_LIB_PATH}/CORE_RL_jpeg_.lib
#                         ${MY_MAGICK_LIB_PATH}/CORE_RL_lcms_.lib
#                         ${MY_MAGICK_LIB_PATH}/CORE_RL_libxml_.lib
#                         ${MY_MAGICK_LIB_PATH}/CORE_RL_magick_.lib
#                         ${MY_MAGICK_LIB_PATH}/CORE_RL_Magick++_.lib
#                         ${MY_MAGICK_LIB_PATH}/CORE_RL_png_.lib
#                         ${MY_MAGICK_LIB_PATH}/CORE_RL_tiff_.lib
#                         ${MY_MAGICK_LIB_PATH}/CORE_RL_ttf_.lib
#                         ${MY_MAGICK_LIB_PATH}/CORE_RL_wand_.lib
#                         ${MY_MAGICK_LIB_PATH}/CORE_RL_wmf_.lib
#                         ${MY_MAGICK_LIB_PATH}/CORE_RL_xlib_.lib
#                         ${MY_MAGICK_LIB_PATH}/CORE_RL_zlib_.lib
#                         ${MY_MAGICK_LIB_PATH}/X11.lib
#                         ${MY_MAGICK_LIB_PATH}/Xext.lib)
