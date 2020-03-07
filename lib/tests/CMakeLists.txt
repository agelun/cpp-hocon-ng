# Setup compiling the test executable. C++ compile flags are inherited from the parent directory.
add_definitions(-Wno-error)
set(TEST_CASES
    concatenation_test.cc
    config_document_parser_test.cc
    config_node_test.cc
    config_value_test.cc
    path_test.cc
    token_test.cc
    tokenizer_test.cc
    test_utils.cc
    config_document_tests.cc
    conf_parser_test.cc
    config_substitution_test.cc
    config_value_factory_test.cc
    config_test.cc
    program_options.cc
)

add_executable(lib${PROJECT_NAME}_test $<TARGET_OBJECTS:lib${PROJECT_NAME}src> ${TEST_CASES} main.cc)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME} MATCHES "SunOS")
    target_link_libraries(lib${PROJECT_NAME}_test rt)
endif()

target_include_directories(lib${PROJECT_NAME}_test PRIVATE ../../../Catch2/single_include/catch2)

target_link_libraries(lib${PROJECT_NAME}_test
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    Catch2
)

add_test(NAME "unit_tests" COMMAND lib${PROJECT_NAME}_test)

configure_file (
    "${CMAKE_CURRENT_LIST_DIR}/fixtures.hpp.in"
    "${CMAKE_CURRENT_LIST_DIR}/fixtures.hpp"
)
