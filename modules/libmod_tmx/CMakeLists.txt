project(mod_tmx)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "../../bin/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin/")

set(CMAKE_MODULE_PATH ../../cmake/Modules)

file(GLOB SOURCES_LIBMOD_TMX
     "../../modules/libmod_tmx/*.c"
     )

add_library(mod_tmx SHARED ${SOURCES_LIBMOD_TMX})