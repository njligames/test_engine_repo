if(EMSCRIPTEN)
  add_subdirectory(${CMAKE_BINARY_DIR}/${${CMAKE_PROJECT_NAME}_REPO_DIR}/cmake/external_libraries/emscripten)
elseif(WINDOWS)
  if(ARCH_64)
    add_subdirectory(${CMAKE_BINARY_DIR}/${${CMAKE_PROJECT_NAME}_REPO_DIR}/cmake/external_libraries/windows64)
  else()
    add_subdirectory(${CMAKE_BINARY_DIR}/${${CMAKE_PROJECT_NAME}_REPO_DIR}/cmake/external_libraries/windows32)
  endif()
elseif(APPLE)
  if(IOS)
    add_subdirectory(${CMAKE_BINARY_DIR}/${${CMAKE_PROJECT_NAME}_REPO_DIR}/cmake/external_libraries/ios)
  elseif(TVOS)
    add_subdirectory(${CMAKE_BINARY_DIR}/${${CMAKE_PROJECT_NAME}_REPO_DIR}/cmake/external_libraries/appletv)
  else()
    add_subdirectory(${CMAKE_BINARY_DIR}/${${CMAKE_PROJECT_NAME}_REPO_DIR}/cmake/external_libraries/macos)
  endif()
elseif(UNIX AND NOT APPLE AND NOT ANDROID)
  if(LINUX)
    add_subdirectory(${CMAKE_BINARY_DIR}/${${CMAKE_PROJECT_NAME}_REPO_DIR}/cmake/external_libraries/linux)
  elseif(UNIX)
    add_subdirectory(${CMAKE_BINARY_DIR}/${${CMAKE_PROJECT_NAME}_REPO_DIR}/cmake/external_libraries/unix)
  endif()
elseif(ANDROID)
  add_subdirectory(${CMAKE_BINARY_DIR}/${${CMAKE_PROJECT_NAME}_REPO_DIR}/cmake/external_libraries/android)
endif()


