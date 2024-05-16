cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
# cspell:disable

project(
  cxtest
  DESCRIPTION "tools made by cx for debugging c++"
  LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# cmake-lint: disable=C0103
set(OpenMP_C_FLAGS "-Xclang -fopenmp")
set(OpenMP_C_LIB_NAMES "omp")
set(OpenMP_omp_LIBRARY omp)
set(OpenMP_CXX_FLAGS "-Xclang -fopenmp")
set(OpenMP_CXX_LIB_NAMES "omp")
set(OpenMP_omp_LIBRARY omp)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(
  ${PROJECT_SOURCE_DIR}/ ${Geant4_INCLUDE_DIR}
  ${HOME}/software/install/include/ /opt/homebrew/opt/qt@5/include/
  /opt/homebrew/include/)
link_directories(${HOME}/software/install/lib/
                 /opt/homebrew/opt/qt@5/lib/ /opt/homebrew/lib/)

find_package(
  ROOT REQUIRED
  COMPONENTS Core
             RIO
             Net
             Hist
             Graf
             Graf3d
             Gpad
             Tree
             Rint
             Postscript
             Matrix
             Physics
             MathCore
             Thread
             dl)
include(${ROOT_USE_FILE})
add_definitions(${ROOT_CXX_FLAGS})

find_package(
  Boost
  COMPONENTS program_options iostreams filesystem
  REQUIRED)
find_library(CXCORSIKAIO CorsikaIODict REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(spdlog REQUIRED)
find_package(PkgConfig)
# pkg_check_modules(TensorFlow REQUIRED tensorflow)

set(LINK_LIBS
    ${ROOT_LIBRARIES}
    ${Boost_LIBRARIES}
    ${Geant4_LIBRARIES}
    CorsikaIODict
    cxthetaphi
    cxMergeFile
    chenxufunc
    cxTeVCat
    yaml-cpp
    cfitsio
    sla
    healpix_cxx
    # ${YAML_CPP_LIBRARIES}
    spdlog::spdlog)

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

# add_library(cxtest SHARED ${sources} ${headers}) target_link_libraries(cxtest
# ${LINK_LIBS})

add_executable(test ${sources} ${headers} p0_test.cpp)
target_link_libraries(test ${LINK_LIBS})
