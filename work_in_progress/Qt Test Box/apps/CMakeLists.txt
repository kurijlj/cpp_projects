add_executable(qt_test_box
    qt_test_box.cpp
    data_model.cpp data_model.hpp
)

target_compile_features(qt_test_box PRIVATE cxx_std_17)

target_link_libraries(qt_test_box PRIVATE
    Qt::Core
    Qt::Widgets
)

# Resources:


# We don't need this because we are using AUTORCC switch
# qt5_add_resources(app app.qrc FILES ${application_resource_files})
