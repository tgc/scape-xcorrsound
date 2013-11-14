cmake_minimum_required (VERSION 2.6) 
project (scape-xcorrsound)


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules/")

find_package(Boost
  COMPONENTS program_options)

find_package(FFTW)

#find_package (LibAVCodec 53.35.0 REQUIRED)
#find_package (LibAVFormat 53.21.1 REQUIRED)
#find_package (LibAVUtil 51.22.1 REQUIRED)

#include_directories(${FFTW_INCLUDES} ${Boost_INCLUDE_DIR} libs/core libs/sound_index tpie ${CMAKE_CURRENT_BINARY_DIR}/tpie)
include_directories(${FFTW_INCLUDES} ${Boost_INCLUDE_DIR} libs/core libs/sound_index)

#include_directories (${LIBAVCODEC_INCLUDE_DIRS})
#include_directories (${LIBAVFORMAT_INCLUDE_DIRS})
#include_directories (${LIBAVUTIL_INCLUDE_DIRS})

## testing
#include_directories (/home/jsn/chromaprint-0.7/build/src/Headers)

#link_directories (${LIBAVCODEC_LIBRARY_DIRS})
#link_directories (${LIBAVFORMAT_LIBRARY_DIRS})
#link_directories (${LIBAVUTIL_LIBRARY_DIRS})


#link_directories (/home/jsn/chromaprint-0.7/build/src)
#list (APPEND CHROMA_LIBS chromaprint)
#add_definitions (-D__STDC_CONSTANT_MACROS)

#get_filename_component (LIBAVCODEC_RPATH ${LIBAVCODEC_LIBRARY} PATH)
#get_filename_component (LIBAVFORMAT_RPATH ${LIBAVFORMAT_LIBRARY} PATH)
#get_filename_component (LIBAVUTIL_RPATH ${LIBAVUTIL_LIBRARY} PATH)
## testing

#if (LINUX)
#    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,${LIBAVCODEC_RPATH}")
#    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,${LIBAVCODEC_LIBAVFORMAT}")
#    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,${LIBAVUTIL_RPATH}")
#    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,${LIBSWSCALE_RPATH}")
#endif (LINUX)

# General package setup
set(CPACK_PACKAGE_NAME scape-xcorrsound)
set(CPACK_PACKAGE_VERSION 0.9.1)
set(CPACK_PACKAGE_VENDOR "SCAPE")

# Debian package configuration section
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE amd64)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6, libboost-program-options-dev, libfftw3-dev")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Jesper Sindahl Nielsen <jsn@statsbiblioteket.dk>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY 
"This is a package of the toolsuite scape-xcorrsound. It contains three tools
waveform-compare: Compare two wave files to determine if they represent the same waveforms
sound-match: find the location of a small wavefile inside a big wavefile
overlap-analysis: find the overlap between two wave files")

# RPM package configuration section
set(CPACK_RPM_PACKAGE_MAINTAINER "Tom G. Christensen <swpkg@statsbiblioteket.dk>")
set(CPACK_RPM_PACKAGE_SUMMARY "A collection of tools for sound analysis")
set(CPACK_RPM_PACKAGE_DESCRIPTION
"The xcorrSound package contains several tools.
 - overlap-analysis is a tool to find the overlap between two audio files.
 - waveform-compare is a tool that splits two audio files into equal sized
   blocks and outputs the correlation for each block (a_i,b_i), if a and b
   was the input.
 - sound-match is a tool to find the location of a small wavefile inside a
   big wavefile

The tools all make use of cross correlation, which can be computed through
the Fourier transform.")
set(CPACK_RPM_PACKAGE_LICENSE "GPLv2+")
set(CPACK_RPM_PACKAGE_GROUP "Applications/Multimedia")
set(CPACK_RPM_PACKAGE_URL "https://github.com/openplanets/scape-xcorrsound")

#configure_file("${CMAKE_CURRENT_SOURCE_DIR}/scape-xcorrsound.spec.in" "${CMAKE_CURRENT_BINARY_DIR}/scape-xcorrsound.spec" @ONLY IMMEDIATE)
#set(CPACK_RPM_USER_BINARY_SPECFILE "${CMAKE_CURRENT_BINARY_DIR}/scape-xcorrsound.spec")

set(CPACK_GENERATOR "DEB;RPM")
include(CPack)
# Finished package setup

#add_subdirectory (tpie)
add_subdirectory (libs)
add_subdirectory (apps)
add_subdirectory (man)

#add_executable(tpietest tpietest.cc)
#target_link_libraries(tpietest tpie)

