cmake_minimum_required(VERSION 3.22)
project(HelloTinyOrmQt LANGUAGES CXX)

add_compile_definitions(WIN32_LEAN_AND_MEAN NOMINMAX WIN32_WINNT=0x0A00)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_DEPLOY_BIN_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
include("${CMAKE_BINARY_DIR}/.qt/QtDeploySupport-Release.cmake")

# Qt via Conan
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(MSVC_RUNTIME_DYNAMIC OFF CACHE BOOL "" FORCE)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# TinyORM via FetchContent
include(FetchContent)
FetchContent_Declare(
    TinyOrm
    GIT_REPOSITORY https://github.com/silverqx/TinyORM.git
    GIT_TAG        origin/main
)

FetchContent_MakeAvailable(TinyOrm)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE RESOURCES "resources/*.qrc")

add_executable(HelloTinyOrmQt WIN32 ${SOURCES} ${RESOURCES})

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

add_custom_command(TARGET HelloTinyOrmQt POST_BUILD
    COMMAND "${__QT_DEPLOY_TOOL}" 
            --dir "$<TARGET_FILE_DIR:HelloTinyOrmQt>" 
            "$<TARGET_FILE:HelloTinyOrmQt>"
    COMMENT "Deploying Qt DLLs using windeployqt"
)
