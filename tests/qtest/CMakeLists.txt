add_executable(qtest_tests qtest_tests.cpp)
target_link_libraries(qtest_tests PRIVATE Qt::Test Comparator)
add_coverage_test(qtest_tests)
set_target_properties(qtest_tests PROPERTIES FOLDER "tests/QTest" AUTOMOC ON)

# add qt's binary directory to test's path for ctest execution
set_tests_properties(qtest_tests
    PROPERTIES
    ENVIRONMENT_MODIFICATION "PATH=path_list_append:$<SHELL_PATH:${DLL_DIR}>" )
