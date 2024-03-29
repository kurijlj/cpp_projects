set(HEADER_LIST "${Focus_Precision_Analyzer_SOURCE_DIR}/extern/clipp/clipp.hpp")
set(HEADER_LIST "${Focus_Precision_Analyzer_SOURCE_DIR}/extern/armadillo/include/armadillo")
set(HEADER_LIST "${Focus_Precision_Analyzer_SOURCE_DIR}/include/input_validators++/validators.hpp")

add_executable(app
    app.cpp
    mainwindow.cpp mainwindow.hpp
    custom_header_view.cpp custom_header_view.hpp
    table_view_widget.cpp table_view_widget.hpp
    data_model.cpp data_model.hpp
    app.qrc
)

target_include_directories(app PRIVATE ../extern/clipp)
target_include_directories(app PRIVATE ../extern/armadillo/include)
target_include_directories(app PRIVATE ../include)

target_compile_features(app PRIVATE cxx_std_17)

target_link_libraries(app PRIVATE
    Qt::Charts
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

# Resources:
set(application_resource_files
    "images/copy.png"
    "images/cut.png"
    "images/new.png"
    "images/open.png"
    "images/paste.png"
    "images/save.png"
)


# We don't need this because we are using AUTORCC switch
# qt5_add_resources(app app.qrc FILES ${application_resource_files})
