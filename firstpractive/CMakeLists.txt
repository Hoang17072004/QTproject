cmake_minimum_required(VERSION 3.16)

project(firstpractive VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appfirstpractive
    main.cpp
)

qt_add_qml_module(appfirstpractive
    URI firstpractive
    VERSION 1.0
    QML_FILES
        Main.qml
        Home.qml
        Setting.qml
    RESOURCES
        assets/images/biahoi.jpg
        assets/images/cafesua.jpg
        assets/images/coca.jpg
        assets/images/nuoccam.jpg
        assets/images/nuockiwi.jpg
        assets/images/sinhtoduahau.jpg
        assets/images/trachanh.jpg
        assets/images/logo.jpg
        assets/images/ExampleCode.png
    SOURCES Productcontrol.h Productcontrol.cpp Product.h Product.cpp
    QML_FILES Message.qml
    SOURCES Curbillcontroller.h Curbillcontroller.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appfirstpractive PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appfirstpractive
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appfirstpractive
    PRIVATE Qt6::Quick
)
target_link_libraries(appfirstpractive PRIVATE Qt6::Core)
target_link_libraries(appfirstpractive PRIVATE Qt6::Core)
target_link_libraries(appfirstpractive PRIVATE Qt6::Core)

include(GNUInstallDirs)
install(TARGETS appfirstpractive
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
