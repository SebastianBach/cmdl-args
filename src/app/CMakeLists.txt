add_executable(cmdl-args)

target_sources(cmdl-args PRIVATE    app.cpp 
                                    parser.cpp 
                                    parser.h
                                    generator.cpp
                                    generator.h)

target_include_directories(cmdl-args PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

