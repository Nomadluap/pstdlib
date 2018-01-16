cmake_minimum_required(VERSION 3.4)


set(SOURCES
    catch.hpp
    main.cpp
    test_cstring.cpp)

add_executable(pstdlib_testing ${SOURCES})

target_link_libraries(pstdlib_testing pstdlib)