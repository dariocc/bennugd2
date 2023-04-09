project(mod_tmx)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "../../bin/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin/")

set(CMAKE_MODULE_PATH ../../cmake/Modules)

file(GLOB SOURCES_LIBMOD_TMX
     "../../modules/libmod_tmx/*.c"
     )

include_directories(../../core/include ../../core/bgdrtm ../../modules/libmod_tmx ../../modules/libbgload)

find_library(TMX_LIB NAMES tmx PATHS /usr/local/lib64)
find_path(TMX_INCLUDE_DIRS tmx.h PATHS /usr/local/include)
include_directories(${TMX_INCLUDE_DIRS})
add_library(mod_tmx SHARED ${SOURCES_LIBMOD_TMX})
target_link_libraries(mod_tmx ${TMX_LIB})