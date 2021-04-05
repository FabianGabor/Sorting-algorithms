cmake_minimum_required(VERSION 3.17)
set(ENV{CC} "/usr/bin/clang")
set(ENV{CXX} "/usr/bin/clang++")
set(ENV{LDFLAGS} "-L/usr/local/opt/llvm/lib")
set(ENV{CPPFLAGS} "-I/usr/local/opt/llvm/include")

set(PROJECT_NAME Sorting_algorithms)
project(${PROJECT_NAME} C)

option(${PROJECT_NAME}_ENABLE_OPENMP
        "Enable OpenMP support for the library"
        ON)

set(OpenMP_C_FLAGS "-fopenmp") # might not be needed?!

set(CMAKE_C_STANDARD 11)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
if(${PROJECT_NAME}_ENABLE_OPENMP)
    message(STATUS "Searching for OpenMP...")
    find_package(OpenMP)
    if (OPENMP_FOUND)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    else()
        set(${PROJECT_NAME}_ENABLE_OPENMP OFF)
        message(STATUS "** OpenMP NOT FOUND; CONTENT DISABLED **")
    endif()
endif()

include(CheckLibraryExists)

CHECK_LIBRARY_EXISTS(m sin "" HAVE_LIB_M)

if (HAVE_LIB_M)
    set(EXTRA_LIBS ${EXTRA_LIBS} m)
endif (HAVE_LIB_M)


set(SOURCE_FILES main.c)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTRA_LIBS})


