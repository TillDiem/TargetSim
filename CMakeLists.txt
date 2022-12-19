cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

project(Simulation)

find_package(Geant4 REQUIRED ui_all vis_all)
find_package(ROOT REQUIRED)


include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)
file(GLOB MACRO_FILES "*.mac" )
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})
add_executable(sim sim.cc ${sources} ${headers})

target_link_libraries(sim ${Geant4_LIBRARIES})
target_link_libraries(sim ${ROOT_LIBRARIES})

ROOT_GENERATE_DICTIONARY(TillDict AnalysisManager.hh LINKDEF LinkDef.h)

add_custom_target(Simulation DEPENDS sim)
