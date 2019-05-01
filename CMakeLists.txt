cmake_minimum_required (VERSION 2.8.11)
project (darwinLogs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfma")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
set(CMAKE_CXX_COMPILER /usr/bin/g++)

find_package(Boost 1.40.0 COMPONENTS filesystem system iostreams regex REQUIRED)
include_directories("${PROJECT_SOURCE_DIR}")

add_executable (${PROJECT_NAME} 
    src/Adult.cpp 
    src/IoService.cpp 
    src/Child.cpp 
    src/World.cpp 
    src/Person.cpp 
    src/PopulationRepository.cpp 
    src/Elder.cpp 
    src/PopulationService.cpp 
    src/main.cpp 
    src/Environment.cpp 
    src/LogService.cpp
    src/Random.cpp
    src/Couple.cpp
    src/Midwife.cpp
    src/Plotter.cpp
)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})