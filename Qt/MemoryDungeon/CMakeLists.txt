cmake_minimum_required(VERSION 3.5)

project(MemoryDungeon VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS QuickWidgets)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
)

# https://stackoverflow.com/questions/37446890/qt-using-cmake-ui-mainwindow-h-no-such-file-or-directory
set(CMAKE_AUTOUIC ON)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MemoryDungeon
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MemoryDungeon APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MemoryDungeon SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MemoryDungeon
            ${PROJECT_SOURCES}
            resources/images/images.qrc
            src/gamerules/gamerule.h src/gamerules/gamerule.cpp
            src/gamerules/row.h src/gamerules/row.cpp
            src/users/user.h src/users/user.cpp
            src/widgets/userlogindialog.h src/widgets/userlogindialog.cpp src/widgets/userlogindialog.ui
            src/widgets/messagedialog.h src/widgets/messagedialog.cpp src/widgets/messagedialog.ui
            src/widgets/clickablelabel.h src/widgets/clickablelabel.cpp




        )
    endif()
endif()

target_link_libraries(MemoryDungeon PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_link_libraries(MemoryDungeon PRIVATE Qt${QT_VERSION_MAJOR}::QuickWidgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MemoryDungeon)
endif()
set_target_properties(MemoryDungeon PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS MemoryDungeon
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MemoryDungeon)
endif()
