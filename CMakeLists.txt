cmake_minimum_required(VERSION 3.28)

# run "emcmake cmake -B web-build"
# then "cmake --build web-build --config Release"

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_NAME "FrenchQuiz")
set(EXEC1 "Paradigms")
set(EXEC2 "Recognition")
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES CXX C)

# assuming visage has been added as a submodule
add_subdirectory(libs/visage)
file(GLOB_RECURSE FONT_TTF_FILES fonts/*.ttf)
add_embedded_resources(EmbeddedFontResources "fonts.h" "resources::fonts" "${FONT_TTF_FILES}")
file(GLOB_RECURSE SQL_FILES dbs/*.db)
add_embedded_resources(EmbeddedDbResources "dbs.h" "resources::dbs" "${SQL_FILES}")

# ditto for SQLiteCpp
add_subdirectory(libs/SQLiteCpp)

add_executable(${EXEC1} 
  src-pdgm/main.cpp
)

add_executable(${EXEC2}
  src-rcgn/main.cpp
  src-rcgn/RcgnApp.cpp
  src-rcgn/DbManager.cpp
)

# if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
#     target_compile_definitions(${EXEC1} PUBLIC "IS_LINUX")
#     set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# endif()
# if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
#     target_compile_definitions(${EXEC1} PUBLIC "IS_MACOS")
#     add_compile_options(-mmacosx-version-min=15.0)
#     target_compile_definitions(${EXEC1} PUBLIC -D_GLIBCXX_USE_CXX11_ABI=1)
# endif()
# 
# 
# if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
#     target_compile_definitions(${EXEC2} PUBLIC "IS_LINUX")
#     set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# endif()
# if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
#     target_compile_definitions(${EXEC2} PUBLIC "IS_MACOS")
#     add_compile_options(-mmacosx-version-min=15.0)
#     target_compile_definitions(${EXEC2} PUBLIC -D_GLIBCXX_USE_CXX11_ABI=1)
# endif()

# set_target_properties(${EXEC1} PROPERTIES MACOSX_BUNDLE TRUE)
# set_property(TARGET ${EXEC1} PROPERTY CXX_STANDARD 20)
# set_target_properties(${EXEC2} PROPERTIES MACOSX_BUNDLE TRUE)
# set_property(TARGET ${EXEC2} PROPERTY CXX_STANDARD 20)

include_directories(libs/visage libs/SQLiteCpp src-pdgm src-rcgn)

if (EMSCRIPTEN)
    MESSAGE(STATUS "Building for WebAssembly")    
    target_link_options(${EXEC1}
      PRIVATE
      --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/minshell.html
      -sGL_ENABLE_GET_PROC_ADDRESS
      -sALLOW_MEMORY_GROWTH=1
      --bind
      -s STACK_SIZE=48MB
      "-sEXPORTED_FUNCTIONS=['_main', '_pasteCallback']"
      "-sEXPORTED_RUNTIME_METHODS=['ccall', 'cwrap', 'UTF8ToString']"
      "-sNO_DISABLE_EXCEPTION_CATCHING"
  )

  set_target_properties(${EXEC1} PROPERTIES
    SUFFIX ".html"
    OUTPUT_NAME "paradigms"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/site"
  )

  target_link_options(${EXEC2}
    PRIVATE
    --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/minshell.html
    -sGL_ENABLE_GET_PROC_ADDRESS
    -sALLOW_MEMORY_GROWTH=1
    --bind
    -s STACK_SIZE=48MB
    "-sEXPORTED_FUNCTIONS=['_main', '_pasteCallback']"
    "-sEXPORTED_RUNTIME_METHODS=['ccall', 'cwrap', 'UTF8ToString']"
    "-sNO_DISABLE_EXCEPTION_CATCHING"
  )

  set_target_properties(${EXEC2} PROPERTIES
    SUFFIX ".html"
    OUTPUT_NAME "recognitions"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/site"
  )

endif()

target_link_libraries(${EXEC1} PRIVATE
  visage
  EmbeddedFontResources
  EmbeddedDbResources
  SQLiteCpp
  sqlite3 # ${SQL} 
)

target_link_libraries(${EXEC2} PRIVATE
  visage
  EmbeddedFontResources
  EmbeddedDbResources
  SQLiteCpp
  sqlite3 # ${SQL} 
)