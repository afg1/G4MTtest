cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH /Users/andrew/Documents/Programs/Geant4/geant4.9.5.p01/cmake/Modules/)

find_package(Geant4 REQUIRED vis_all)

include_directories("include" ${Geant4_INCLUDE_DIRS} ${ROOT_INCLUDE_DIR})
add_definitions("src" ${Geant4_DEFINITIONS} ${ROOT_DEFINITIONS} "-O3" "-Wall" "-DG4VIS_USE" )
set(CMAKE_CXX_FLAGS ${Geant4_CXX_FLAGS} ${ROOT_CXX_FLAGS})

FILE(GLOB sources src/*.cc)
FILE(GLOB headers include/*.hh)
add_executable(WC_mk3 WC_mk3.cc ${sources} ${headers})
target_link_libraries(WC_mk3 ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
