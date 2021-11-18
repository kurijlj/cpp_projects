
set(HEADER_LIST "${PROJECT_SOURCE_DIR}/extern/clipp/clipp.hpp")
set(HEADER_LIST "${PROJECT_SOURCE_DIR}/extern/libtiff/tiffio.h")
set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/input_validators++/validators.hpp")
set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/tiffio++/tiffio++.hpp")
set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/CImg/CImg.h")

find_package(ImageMagick)

# ### CIMG related stuff
# Flags to enable fast image display, using the XSHM library.
SET(CIMG_XSHM_CCFLAGS  -Dcimg_use_xshm)

# Flags to enable screen mode switching, using the XRandr library.
SET(CIMG_XRANDR_CCFLAGS  -Dcimg_use_xrandr)

# Flags to enable native support for TIFF image files, using the TIFF library.
# ( http://www.libtiff.org/ )
SET(CIMG_TIFF_CCFLAGS  -Dcimg_use_tiff)

SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_TIFF_CCFLAGS}")

if(NOT WIN32)
  FIND_PACKAGE(X11)
  FIND_PACKAGE(Threads REQUIRED)
endif()

if(NOT APPLE)
  if(NOT WIN32)
    if(X11_FOUND)
      SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_XSHM_CCFLAGS} ${CIMG_XRANDR_CCFLAGS}")
      SET(SYSTEM_LIBS ${SYSTEM_LIBS} Xext Xrandr)
    endif()
  endif(NOT WIN32)
endif(NOT APPLE)

if(X11_FOUND)
  link_directories(${X11_LIB_DIRS})
  include_directories(${X11_INCLUDE_DIR})
  SET(SYSTEM_LIBS ${SYSTEM_LIBS} ${X11_LIBRARIES})
endif()

if (NOT WIN32)
  SET(SYSTEM_LIBS ${SYSTEM_LIBS} ${CMAKE_THREAD_LIBS_INIT})
endif()

if(WIN32)
  SET(SYSTEM_LIBS ${SYSTEM_LIBS} gdi32)
endif()

# Add CIMG Flags to Compilation Flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CIMG_CFLAGS}")

SET(APPS app
    tifinfo
    tifinfoplus
    cimg_test
    )

SET(INCLUDE_DIRS ../extern/clipp
    ../extern/libtiff
    ../include
    )

foreach(program ${APPS})
    add_executable(${program} ${program}.cpp)
    target_include_directories(${program} PRIVATE ${INCLUDE_DIRS})
    target_compile_features(${program} PRIVATE cxx_std_17)
    target_link_libraries(${program} PRIVATE input_validators++ tiff)
endforeach(program)
