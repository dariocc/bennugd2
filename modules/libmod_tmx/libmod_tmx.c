#include <stdio.h> // TODO: Remove me
#include <stdlib.h>
#include <string.h>
#include <tmx.h>

#include "bgddl.h"

#include "files.h"
#include "xctype.h"
#include "xstrings.h"
#include "g_bitmap.h"
#include "m_map.h"
#include "g_grlib.h"

#include "dlvaracc.h"

#include "libmod_tmx.h"

static const int TMX_MAX_MAP_ID = 1;
static tmx_last_map_id = 0;
static tmx_map **tmx_maps; // 1-based array (first element is always ignored)

static uint64_t libmod_tmx_load_map(INSTANCE * my, int64_t * params) {
    const char *filename;
    tmx_map *result = (tmx_map *)( intptr_t )(params[1]);
    
    if ( ! (filename = string_get(params[0])) ) {
        return 0;
    }

    tmx_map *map = tmx_load(filename);
    if (!map) {
        tmx_perror("Cannot load map");
        return 0;
    }

    tmx_last_map_id++;
    tmx_maps[tmx_last_map_id] = map;

    result = map;

    return tmx_last_map_id;
}

static int64_t libmod_tmx_unload_map(INSTANCE * my, int64_t * params) {
    int64_t tilemap_id = params[0];
    tmx_map_free(tmx_maps[tilemap_id]);
}

static void* tex_load(const char *path) {
    int64_t *handler = malloc(sizeof(handler));
    *handler = gr_load_img(path);
    return handler;
}

static void* tex_free(void * handler) {
    return (void *) grlib_unload_map(0, (int64_t *)handler);
}

void __bgdexport( libmod_tmx, module_initialize )() {
    tmx_img_load_func = tex_load;
    tmx_maps = malloc(sizeof *tmx_maps * TMX_MAX_MAP_ID);
}

void __bgdexport( libmod_tmx, module_finalize )() {
}

#include "libmod_tmx_exports.h"
