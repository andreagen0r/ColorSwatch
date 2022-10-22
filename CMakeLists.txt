cmake_minimum_required(VERSION 3.16)

project(ColorSwatches VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 6.2 COMPONENTS Quick Widgets REQUIRED)

qt_add_executable(app${PROJECT_NAME}
    main.cpp
)

qt_add_qml_module(app${PROJECT_NAME}
    URI ColorSwatch
    VERSION 1.0
    QML_FILES main.qml ColorSwatch.qml InputDialog.qml
#    RESOURCE_PREFIX "/"
    RESOURCES
        "assets/task--add.svg"
        "assets/add.svg"
        "assets/subtract.svg"
    SOURCES
        swatch_item.h
        swatches_model.h swatches_model.cpp
        iswatches_repository.h
        swatches_qsettings_repository.h swatches_qsettings_repository.cpp
        icolor_palette_repository.h
        color_palette_qsettings_repository.h color_palette_qsettings_repository.cpp
        color_palette_model.h color_palette_model.cpp
        color_palette_data.h color_palette_data.cpp
)

set_target_properties(app${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(app${PROJECT_NAME}
    PRIVATE Qt6::Quick Qt6::Widgets)

install(TARGETS app${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
