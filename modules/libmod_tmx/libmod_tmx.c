#include <stdlib.h>
#include <string.h>
#include <tmx.h>

#include "bgddl.h"

#include "files.h"
#include "xctype.h"
#include "xstrings.h"

#include "dlvaracc.h"

#include "libmod_tmx.h"

static int64_t libmod_tmx_load_map(INSTANCE * my, int64_t * params) {
    const char *filename;
    if ( ! (filename = string_get(params[0])) ) {
        return 0;
    }
    tmx_map *map = tmx_load(filename);
    if (!map) {
        tmx_perror("Cannot load map");
        return -1;
    }
    return (int64_t)map;
}

static uint32_t libmod_tmx_get_map_width(INSTANCE * my, int64_t * params) {
    tmx_map * map = (tmx_map *)params[0];
    return map->width;
}

static uint32_t libmod_tmx_get_map_height(INSTANCE * my, int64_t * params) {
    tmx_map * map = (tmx_map *)params[0];
    return map->height;
}

static int64_t libmod_tmx_unload_map(INSTANCE * my, int64_t * params) {
    tmx_map * map = (tmx_map *)params[0];
    tmx_map_free(map);
}

static void* tex_loader(const char *path) {
}

void __bgdexport( libmod_tmx, module_initialize )() {
}

void __bgdexport( libmod_tmx, module_finalize )() {
}

#include "libmod_tmx_exports.h"
