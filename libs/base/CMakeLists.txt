add_library(libbase STATIC
        libbase/configure_working_directory.cpp
)

target_include_directories(libbase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
