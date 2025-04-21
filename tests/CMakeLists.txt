
if(BUILD_WITH_GTEST)
    include(GoogleTest)
    add_subdirectory(gtest)
endif()

if(BUILD_WITH_CATCH2)
    include(Catch)
    add_subdirectory(catch2)
endif()

if(BUILD_WITH_QTEST)
    add_subdirectory(qtest)
endif()