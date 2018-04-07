# General source files
if(GVR)
  file(GLOB SOURCE_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/*.c
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/*.cc
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/*.cpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/*.cxx
    )
  file(GLOB GVR_SOURCE_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/Source/*.m
    )
  SET_SOURCE_FILES_PROPERTIES( ${GVR_SOURCE_FILES} PROPERTIES COMPILE_FLAGS "-x objective-c++ -fobjc-arc" )
  list(APPEND SOURCE_FILES "${GVR_SOURCE_FILES}")
else()
  file(GLOB SOURCE_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/*.c
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/*.cpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/*.cxx
    )
endif()

if(OCULUS)
  file(GLOB MAIN_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/main/oculus_rift_sdl2_opengl_demo.cpp
    )
elseif(GVR)
  file(GLOB MAIN_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/main/gvr_main.cpp
    )
else()
  file(GLOB MAIN_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/main/main.cpp
    )
endif()

if(GVR)
  file(GLOB INCLUDE_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/include/*.h
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/include/*.hh
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/include/*.hpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/include/*.hxx
    )
else()
  file(GLOB INCLUDE_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/include/*.h
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/include/*.hpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/include/*.hxx
    )
endif()
