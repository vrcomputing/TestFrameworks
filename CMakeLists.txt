cmake_minimum_required(VERSION 3.28)

project(testframeworks)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

option(BUILD_WITH_GTEST             "" ON)
option(BUILD_WITH_QTEST             "" ON)
option(BUILD_WITH_CATCH2            "" ON)
option(BUILD_WITH_OPEN_CPP_COVERAGE "" ON)

set(CMAKE_WARN_DEPRECATED FALSE)
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        6910c9d9165801d8827d628cb72eb7ea9dd538c5 # release-1.16.0
)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        2b60af89e23d28eefc081bc930831ee9d45ea58b # release-3.8.1
)

if(BUILD_WITH_GTEST)
    FetchContent_MakeAvailable(googletest)
endif()

if(BUILD_WITH_CATCH2)
    FetchContent_MakeAvailable(Catch2)
endif()

if(BUILD_WITH_OPEN_CPP_COVERAGE)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(PROGRAM_FILES "$ENV{ProgramFiles}")
    else()
        set(PROGRAM_FILES "$ENV{ProgramFiles(x86)}")
    endif()
    find_program(OpenCppCoverage_EXE NAMES OpenCppCoverage.exe PATHS ${PROGRAM_FILES}/OpenCppCoverage REQUIRED)
    add_executable(OpenCppCoverage IMPORTED)
    set_target_properties(OpenCppCoverage PROPERTIES IMPORTED_LOCATION ${OpenCppCoverage_EXE})

    function(add_coverage_test TARGET_NAME)
        cmake_path(NATIVE_PATH CMAKE_SOURCE_DIR SOURCE_DIR)
        cmake_path(NATIVE_PATH CMAKE_BINARY_DIR BINARY_DIR)
        add_test(NAME ${TARGET_NAME} COMMAND OpenCppCoverage
            --sources
            ${SOURCE_DIR}
            --excluded_sources
            ${BINARY_DIR}
            --modules
            $<TARGET_FILE_NAME:${TARGET_NAME}>
            --export_type
            html:coverage
            --
            $<TARGET_FILE_NAME:${TARGET_NAME}>
        WORKING_DIRECTORY $<TARGET_FILE_DIR:${TARGET_NAME}>)
    endfunction()
else()
    function(add_coverage_test)
        add_test(${ARGV})
    endfunction()
endif()

if(BUILD_WITH_QTEST)
    find_package(Qt6 REQUIRED COMPONENTS Test)

    # find Qt test shared library and append its directory to the VS debugger path
    get_target_property(DLL_DIR Qt::Test IMPORTED_LOCATION)
    get_filename_component(DLL_DIR ${DLL_DIR} DIRECTORY)
    set(CMAKE_VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${DLL_DIR}" CACHE PATH "Qt's directory for shared libraries" FORCE)
endif()

if(BUILD_WITH_OPEN_CPP_COVERAGE)
    find_package(Qt6 REQUIRED COMPONENTS Test)

    # find Qt test shared library and append its directory to the VS debugger path
    get_target_property(DLL_DIR Qt::Test IMPORTED_LOCATION)
    get_filename_component(DLL_DIR ${DLL_DIR} DIRECTORY)
    set(CMAKE_VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${DLL_DIR}" CACHE PATH "Qt's directory for shared libraries" FORCE)
endif()

add_subdirectory(libs)

include(CTest)
enable_testing()
add_subdirectory(tests)

# folders

function(set_target_folder_property TARGET_NAME FOLDER_NAME)
    if(TARGET ${TARGET_NAME})
        set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "${FOLDER_NAME}")
    endif()
endfunction()

set_target_folder_property(gtest          "3rdparty/gtest")
set_target_folder_property(gtest_main     "3rdparty/gtest")
set_target_folder_property(gmock          "3rdparty/gmock")
set_target_folder_property(gmock_main     "3rdparty/gmock")
set_target_folder_property(Catch2         "3rdparty/Catch2")
set_target_folder_property(Catch2WithMain "3rdparty/Catch2")