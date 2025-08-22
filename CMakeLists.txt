cmake_minimum_required(VERSION 3.16)
project(nexus)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS Widgets Network Svg REQUIRED)

include(FetchContent)
FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG da40186618909b1a7363d4e4495aa899c6e0eb75
)
FetchContent_MakeAvailable(cpr)

# List your sources
set(SOURCES
        src/main.cpp
        resources/resources.qrc
        src/api/AccountManagementClient.hpp
        src/api/RestClientBase.hpp
        src/ui/main_ui.cpp
        src/ui/main_ui.h
        src/ui/components/ProfileDialog.hpp
        src/ui/components/SettingsDialog.hpp
)

# Generate Qt resources
qt6_add_resources(QT_RESOURCES resources/resources.qrc)

# Create executable target
add_executable(nexus
        ${SOURCES}
        ${QT_RESOURCES}
)

# Compile definitions
target_compile_definitions(nexus PRIVATE
        APP_VERSION="0.1.0"
        QT_DEPRECATED_WARNINGS
)

# Link against Qt, cpr, and curl
target_link_libraries(nexus PRIVATE
        Qt6::Widgets
        Qt6::Network
        cpr::cpr
        Qt6::Svg
)

# Run windeployqt after build
add_custom_command(TARGET nexus POST_BUILD
        COMMAND "C:/Qt/6.9.1/mingw_64/bin/windeployqt.exe" "$<TARGET_FILE:nexus>"
        COMMENT "Running windeployqt to deploy Qt runtime..."
)
