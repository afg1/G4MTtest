cmake_minimum_required(VERSION 2.6)

find_package(Geant4 REQUIRED vis_all)

include_directories("include" ${Geant4_INCLUDE_DIRS} ${ROOT_INCLUDE_DIR})
add_definitions(${Geant4_DEFINITIONS} ${ROOT_DEFINITIONS} "-O3" "-Wall" "-DG4VIS_USE" )
set(CMAKE_CXX_FLAGS ${Geant4_CXX_FLAGS} ${ROOT_CXX_FLAGS})

FILE(GLOB sources src/*.cc)
FILE(GLOB headers include/*.hh)
add_executable(MFT G4_basic.cc ${sources} ${headers})
target_link_libraries(MFT ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
