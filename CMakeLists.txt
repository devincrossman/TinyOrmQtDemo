cmake_minimum_required(VERSION 3.22)
add_compile_definitions(WIN32_LEAN_AND_MEAN NOMINMAX _WIN32_WINNT=0x0A00 WINVER=0x0A00)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL" CACHE STRING "" FORCE)

set(QT_INSTALL_DIR "C:/Qt/6.10.0/msvc2022_64")
list(APPEND CMAKE_PREFIX_PATH ${QT_INSTALL_DIR})

project(HelloTinyOrmQt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_DEPLOY_BIN_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
include("${CMAKE_BINARY_DIR}/.qt/QtDeploySupport-Release.cmake" OPTIONAL)

# Qt via Conan
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)

qt_standard_project_setup()

# TinyORM via FetchContent
include(FetchContent)
FetchContent_Declare(
    TinyOrm
    GIT_REPOSITORY https://github.com/silverqx/TinyORM.git
    GIT_TAG        origin/main
)

FetchContent_MakeAvailable(TinyOrm)

file(GLOB_RECURSE SOURCES "src/*.cpp")

qt_add_resources(RESOURCES_QRC ${CMAKE_CURRENT_SOURCE_DIR}/resources/resources.qrc)

qt_add_executable(HelloTinyOrmQt WIN32 ${SOURCES} ${RESOURCES_QRC})

target_include_directories(HelloTinyOrmQt
    PRIVATE
        ${tinyorm_SOURCE_DIR}/include
)

target_link_libraries(HelloTinyOrmQt
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        TinyOrm::TinyOrm
)

# deploy Qt DLLs next to the exe
add_custom_command(TARGET HelloTinyOrmQt POST_BUILD
    COMMAND "${__QT_DEPLOY_TOOL}" --release
            --dir "$<TARGET_FILE_DIR:HelloTinyOrmQt>" 
            "$<TARGET_FILE:HelloTinyOrmQt>"
    COMMENT "Deploying Qt DLLs using windeployqt"
)
