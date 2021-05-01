cmake_minimum_required(VERSION 3.12)

set(PROJ_NAME VirusHelper)

project(VirusHelper)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJ_NAME}
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/Virus.cpp
    ${HEADER_DIR}/Virus.hpp
    ${SOURCE_DIR}/Symptom.cpp
    ${HEADER_DIR}/Symptom.hpp
    ${SOURCE_DIR}/SymptomList.cpp
    ${HEADER_DIR}/SymptomList.hpp
    ${SOURCE_DIR}/VirusList.cpp
    ${HEADER_DIR}/VirusList.hpp
    ${SOURCE_DIR}/VirusParams.cpp
    ${HEADER_DIR}/VirusParams.hpp)

target_include_directories(VirusHelper PUBLIC
    ${HEADER_DIR}
)

set_property(TARGET ${PROJ_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${PROJ_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

if(MSVC)
    target_compile_options(${PROJ_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJ_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
