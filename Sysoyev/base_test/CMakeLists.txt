project(base_test)


file(GLOB TEST_SOURCES "*.cpp")

add_executable(postfix_test ${TEST_SOURCES})

target_link_libraries(postfix_test 
    base_lib   
    gtest      
)


target_include_directories(postfix_test PRIVATE
    ${CMAKE_SOURCE_DIR}/Sysoyev/base
    ${CMAKE_SOURCE_DIR}/Sysoyev/gtest
)