cmake_minimum_required (VERSION 3.14)

project(ClrProfiler)

if(NOT WIN32)
    set(BASE_SOURCES )
    add_compile_options(-Wno-invalid-noreturn -Wno-pragma-pack -Wno-int-to-pointer-cast -fPIC -fms-extensions -DBIT64 -DPAL_STDCPP_COMPAT -DPLATFORM_UNIX -DHOST_64BIT -std=c++11)
    add_link_options(--no-undefined -pthread)

    include_directories($ENV{CORECLR_PATH}/src/pal/inc/rt $ENV{CORECLR_PATH}/src/pal/inc $ENV{CORECLR_PATH}/src/inc)
endif(NOT WIN32)


if (WIN32)
  set(BASE_SOURCES ClrProfiler.def)
endif(WIN32)

include_directories($CORECLR_BIN/inc $ENV{CORECLR_PATH}/src/pal/prebuilt/inc)

set(SOURCES 
  ${BASE_SOURCES}
  miniutf.cpp
  string.cpp 
  util.cpp
  il_rewriter.cpp
  il_rewriter_wrapper.cpp 
  clr_helpers.cpp
  CorProfiler.cpp 
  ClassFactory.cpp
  dllmain.cpp
  $ENV{CORECLR_PATH}/src/pal/prebuilt/idl/corprof_i.cpp)

add_library("ClrProfiler" SHARED ${SOURCES})

set_target_properties("ClrProfiler" PROPERTIES PREFIX "")
