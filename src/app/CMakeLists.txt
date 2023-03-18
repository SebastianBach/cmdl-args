add_executable(cmdl-args)

target_sources(cmdl-args PRIVATE    app.cpp 
                                    process.cpp
                                    process.h
                                    parser.cpp 
                                    parser.h
                                    generator.cpp
                                    generator.h
                                    tests.h)

target_include_directories(cmdl-args PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(cmdl-args PROPERTIES VERSION 0.1.0)


get_target_property(VERSION cmdl-args VERSION)
target_compile_definitions(cmdl-args PRIVATE TOOL_VERSION="${VERSION}")

# basic tests

add_test(NAME help COMMAND cmdl-args "--help")
add_test(NAME version COMMAND cmdl-args "--version")
