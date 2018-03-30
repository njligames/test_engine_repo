# General source files
file(GLOB SOURCE_FILES
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/*.c
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/*.cpp
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/*.cxx
  )
file(GLOB MAIN_FILES
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/main/main.cpp
  )

