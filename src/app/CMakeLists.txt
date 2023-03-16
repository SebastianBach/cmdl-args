add_executable(cmdl-args)

target_sources(cmdl-args PRIVATE    app.cpp 
                                    parser.cpp 
                                    parser.h
                                    generator.cpp
                                    generator.h
                                    tests.h)

target_include_directories(cmdl-args PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# basic tests

add_test(NAME help COMMAND cmdl-args "--help")
add_test(NAME version COMMAND cmdl-args "--version")
