add_executable(qt_test_box
    qt_test_box.cpp
    ${PROJECT_SOURCE_DIR}/src/data_model.cpp ${PROJECT_SOURCE_DIR}/include/data_model.hpp
)

target_compile_features(qt_test_box PRIVATE cxx_std_17)

target_include_directories(qt_test_box PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(qt_test_box PRIVATE
    Qt::Core
    Qt::Widgets
)

add_executable(qt_test_chart
    qt_test_chart.cpp
)

target_compile_features(qt_test_chart PRIVATE cxx_std_17)

target_link_libraries(qt_test_chart PRIVATE
    Qt::Core
    Qt::Charts
    Qt::Widgets
)

add_executable(custom_graph_framework
    custom_graph_framework.cpp
    ${PROJECT_SOURCE_DIR}/src/custom_graph_view.cpp ${PROJECT_SOURCE_DIR}/include/custom_graph_view.hpp
    ${PROJECT_SOURCE_DIR}/src/data_callout.cpp ${PROJECT_SOURCE_DIR}/include/data_callout.hpp
)

target_compile_features(custom_graph_framework PRIVATE cxx_std_17)

target_include_directories(custom_graph_framework PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(custom_graph_framework PRIVATE
    Qt::Charts
    Qt::Core
    Qt::Gui
)

# Resources:


# We don't need this because we are using AUTORCC switch
# qt5_add_resources(app app.qrc FILES ${application_resource_files})
