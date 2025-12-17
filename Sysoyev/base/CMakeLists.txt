project(base)

file(GLOB HEADERS "*.h")
file(GLOB SOURCES "*.cpp")

set(LIB_SOURCES)
foreach(src ${SOURCES})
    if(NOT src MATCHES "sample_postfix\\.cpp$")  
        list(APPEND LIB_SOURCES ${src})
    endif()
endforeach()

add_library(base_lib STATIC ${LIB_SOURCES})


target_include_directories(base_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(postfix sample_postfix.cpp)
target_link_libraries(postfix base_lib)