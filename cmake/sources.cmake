# General source files
file(GLOB_RECURSE SOURCE_FILES
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/*.c
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/*.cpp
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/*.cxx
  )
file(GLOB MAIN_FILE
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/main.cpp
  )

SOURCE_GROUP("SOURCE\\engine" FILES ${SOURCE_FILES} )
SOURCE_GROUP("SOURCE\\main" FILES ${MAIN_FILE} )

