# set(HEADER_LIST "${CLI_App_Framework_SOURCE_DIR}/extern/clipp/clipp.hpp")

add_executable(app
    app.cpp
    mainwindow.cpp mainwindow.hpp
    vertex.hpp
)

# target_include_directories(app PRIVATE ../extern/clipp)

target_compile_features(app PRIVATE cxx_std_17)

target_link_libraries(app PRIVATE
    Qt::Core
    Qt::Gui
    Qt::OpenGL
    # Qt::Widgets
)

# Resources:
set(application_resource_files
    "shaders/simple.vrt"
    "shaders/simple.frg"
)


qt5_add_resources(app app.qrc FILES ${application_resource_files})
