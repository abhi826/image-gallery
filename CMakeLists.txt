cmake_minimum_required(VERSION 3.20)
project(ImageGallery LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core Gui Quick QuickControls2 Network
)

qt_add_executable(appImageGallery
    src/main.cpp
    src/gallerymodel.h
    src/gallerymodel.cpp
)

target_link_libraries(appImageGallery
    PRIVATE Qt6::Core Qt6::Gui Qt6::Quick
            Qt6::QuickControls2 Qt6::Network
)

set_target_properties(appImageGallery PROPERTIES
    QT_QML_MODULE_NAME    "GalleryModule"
    QT_QML_MODULE_VERSION "1.0"
)
