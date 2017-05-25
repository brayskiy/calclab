cmake_minimum_required(VERSION 3.4.1)

SET(ROOT_DIR .)

SET(BRSRC ${ROOT_DIR}/brsrc)
SET(THIRD_PARTY ${BRSRC}/third_party)
SET(RAPID_JSON ${THIRD_PARTY}/rapidjson-0.1)

SET(NDK src/main/cpp)

SET(BPLOT ${BRSRC}/lib/libbplot)
SET(BPLOT_INC ${BPLOT}/include)
#SET(BPLOT_SRC ${BPLOT}/jni)
SET(BPLOT_DRV ${BPLOT}/driver)

SET(BOASCRIPT ${BRSRC}/tools/boa)
#SET(BOA_SRC ${BOASCRIPT}/jni)
SET(BOA_INC ${BOASCRIPT}/jni)

include_directories(
    ${ROOT_DIR}
    ${NDK}
    ${BRSRC}
    ${BRSRC}/bstd
    ${BRSRC}/data
    ${BRSRC}/debug
    ${BRSRC}/graph
    ${BRSRC}/math
    ${BRSRC}/util
    ${BRSRC}/sys
    ${BPLOT_INC}
    ${BPLOT_DRV}
    ${BOA_INC}
    ${RAPID_JSON}/rapidjson
)

add_library(native-lib SHARED
      ${NDK}/ndk.cpp
      ${BRSRC}/util/DateTime.cpp
      ${BRSRC}/sys/BMemory.cpp
)

SET(RELATIVE_PATH ../../../..)

#FILE(GLOB BPLOT_SOURCES "${BPLOT_SRC}/*.cpp")
#add_library(bplot STATIC ${BPLOT_SOURCES})

add_library(bplot STATIC IMPORTED)
set_target_properties(bplot PROPERTIES IMPORTED_LOCATION ${RELATIVE_PATH}/libs/debug/${ANDROID_ABI}/libbplot.a)

#FILE(GLOB BOA_SOURCES "${BOA_SRC}/*.cpp")
#add_library(boascript STATIC ${BOA_SOURCES})

add_library(boascript STATIC IMPORTED)
set_target_properties(boascript PROPERTIES IMPORTED_LOCATION ${RELATIVE_PATH}/libs/debug/${ANDROID_ABI}/libboascript.a)

find_library(
    log-lib log
)

target_link_libraries(
    native-lib ${log-lib} bplot boascript
)
