cmake_minimum_required(VERSION 3.16)
project(polynomial C CXX)

set(CMAKE_CXX_STANDARD 11)

# CppUTestを追加
find_package(CppUTest REQUIRED)
find_library(GF_LIB gf PATHS lib)

# テスト対象
add_library(poly src/Poly.c)

# テスト実行ファイル
add_executable(test_runner
    test/TestPoly.cpp
    test/TestRunner.cpp
)

target_include_directories(poly PUBLIC include)
target_include_directories(poly PUBLIC lib)

## リンク
#target_link_libraries(poly PRIVATE ${GF_LIB})

target_link_libraries(test_runner PRIVATE
    poly 
    CppUTest
    CppUTestExt
    ${GF_LIB}
)

# テスト登録
enable_testing()
add_test(NAME poly COMMAND test_runner)
