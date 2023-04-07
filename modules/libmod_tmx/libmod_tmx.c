#include <libtmx.h>
#include <bgddl.h>

#include "xctype.h"
#include "bgddl.h"
#include "dlvaracc.h"

#include "libmod_tmx.h"

typedef struct {
    tmx_map *map;
} tmx_map_handle;

static int tmx_load_map(char *filename) {
    tmx_map_handle *handle = (tmx_map_handle*)malloc(sizeof(tmx_map_handle));
    handle->map = tmx_load(filename);
    if (!handle->map) {
        free(handle);
        return -1;
    }
    return (int)handle;
}

static int tmx_get_map_width(int handle) {
    tmx_map_handle *map_handle = (tmx_map_handle*)handle;
    return map_handle->map->width;
}

static int tmx_get_map_height(int handle) {
    tmx_map_handle *map_handle = (tmx_map_handle*)handle;
    return map_handle->map->height;
}

static int tmx_get_map_tileset_count(int handle) {
    tmx_map_handle *map_handle = (tmx_map_handle*)handle;
    return map_handle->map->tileset_count;
}

static void tmx_unload_map(int handle) {
    tmx_map_handle *map_handle = (tmx_map_handle*)handle;
    tmx_map_free(map_handle->map);
    free(map_handle);
}

void __bgdexport( libmod_tmx, module_initialize )() {
}

void __bgdexport( libmod_tmx, module_finalize )() {
}

#include "libmod_tmx_exports.h"
