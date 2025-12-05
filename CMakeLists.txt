cmake_minimum_required(VERSION 3.16)

project(Flow VERSION 0.1.0 LANGUAGES CXX)

add_executable(Flow
    src/main.cpp
    src/thread_pool.cpp
)

# Keep the C++17 requirement scoped to this target instead of globally.
target_compile_features(Flow PRIVATE cxx_std_17)

enable_testing()

add_executable(test_basic
    tests/test_basic.cpp
    src/thread_pool.cpp
)
target_include_directories(test_basic PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_compile_features(test_basic PRIVATE cxx_std_17)
add_test(NAME test_basic COMMAND test_basic)

add_executable(test_stress
    tests/test_stress.cpp
    src/thread_pool.cpp
)
target_include_directories(test_stress PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_compile_features(test_stress PRIVATE cxx_std_17)
add_test(NAME test_stress COMMAND test_stress)
