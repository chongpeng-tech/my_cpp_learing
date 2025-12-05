# Specify the minimum required version of CMake for this project. 
cmake_minimum_required(VERSION 3.14)

project(AUT_AP_2025_Spring_HW1)

# Set the C++ standard to C++17 and make it a required standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 步骤 1: 删除了 find_package(GTest REQUIRED) 语句 ---


# --- 步骤 2: 添加 GTest 自动下载和集成代码 ---
# 使用 FetchContent 模块，让 CMake 自动从 GitHub 下载 GTest 源码
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0 # 使用一个稳定版本
)

FetchContent_MakeAvailable(googletest)
# ---------------------------------------------------


include_directories(include/)

# --- 步骤 3A: 修改目标名称为 unit_test ---
# 添加所有源文件，用于生成 unit_test 可执行文件
add_executable(unit_test
        src/main.cpp
        src/unit_test.cpp
        src/Q2_Sort_By_Distance.cpp
        src/Q3_Count_Islands.cpp 
)

# Set compiler flags for C++.
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wpedantic")


# Set compiler flags specific to the Release build type.
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


# --- 步骤 3B: 修正并统一链接库到 unit_test ---
# 链接到我们自动下载的 GTest 库
target_link_libraries(unit_test
        GTest::gtest
        GTest::gtest_main
)
