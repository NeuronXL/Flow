cmake_minimum_required(VERSION 3.16)

project(Flow VERSION 0.1.0 LANGUAGES CXX)

add_executable(Flow
    src/main.cpp
    src/thread_pool.cpp
)

# Keep the C++17 requirement scoped to this target instead of globally.
target_compile_features(Flow PRIVATE cxx_std_17)
