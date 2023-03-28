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

# process test

set(TEST_INPUT ${PROJECT_SOURCE_DIR}/src/test/input.txt)
set(OUTPUT_PATH ${CMAKE_BINARY_DIR}/test_results/)

# create output
add_test(NAME process COMMAND cmdl-args "--i" ${TEST_INPUT} "--o" ${OUTPUT_PATH} "--header" "parser.h" "--cpp" "parser.cpp" "--pragma" "--comments" "--print" "--values" "--space" "cmdl_args" "--tab" "2" "--v")

# compare to refrence

set(RESULT_HEADER ${CMAKE_BINARY_DIR}/test_results/parser.h)
set(REFERENCE_HEADER ${PROJECT_SOURCE_DIR}/src/test/reference.h)


add_test(NAME check_process_header COMMAND ${CMAKE_COMMAND}
    -DOUTPUT_FILE=${RESULT_HEADER}
    -DREFERENCE_FILE=${REFERENCE_HEADER}
    -P ${PROJECT_SOURCE_DIR}/src/test/compare.cmake
)

set(RESULT_CPP ${CMAKE_BINARY_DIR}/test_results/parser.cpp)
set(REFERENCE_CPP ${PROJECT_SOURCE_DIR}/src/test/reference.cpp)

add_test(NAME check_process_source COMMAND ${CMAKE_COMMAND}
    -DOUTPUT_FILE=${RESULT_CPP}
    -DREFERENCE_FILE=${REFERENCE_CPP}
    -P ${PROJECT_SOURCE_DIR}/src/test/compare.cmake
)
