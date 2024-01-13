# 设置项目所需的 cmake 最低版本
cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(PopStar VERSION 1.0)

# 添加 C++11 的标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 自动执行 MOC
set(CMAKE_AUTOMOC ON)

# 自动执行 RCC
set(CMAKE_AUTORCC ON)

# 自动执行 UIC
set(CMAKE_AUTOUIC ON)

# 查找 Qt 包，并且加载包中指定的模块信息
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# 添加 ui 文件的搜索路径
set(CMAKE_AUTOUIC_SEARCH_PATHS ./ui)

# 添加头文件路径
include_directories (./src)

# 设置目标文件的输出路径
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/output/lib-debug)
    set(LIB_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/output/lib-debug)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/output/bin-dbg)
else()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/output/lib)
    set(LIB_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/output/lib)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/output/bin)
endif()

# 添加源代码文件
add_executable(PopStar
    ./src/main.cpp
    ./src/mainwindow.cpp
    ./src/popstar.cpp
    ./src/game_over.cpp
    resources/image.qrc
)

# 指定目标文件所需要使用的 Qt 模块
target_link_libraries(PopStar Qt5::Core Qt5::Gui Qt5::Widgets)
