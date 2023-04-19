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

typedef struct tmx_tex_t {
    int64_t graph;
} tmx_tex_t;

static intptr_t libmod_tmx_load_map(INSTANCE * my, int64_t * params) {
    const char *filename;
    if ( ! (filename = string_get(params[0])) ) {
        return 0;
    }

    tmx_map *map = tmx_load(filename);
    if (!map) {
        tmx_perror("Cannot load map");
        return -1;
    }

    *( tmx_map *)( intptr_t )(params[1]) = *map;
    return 0;
}

static int64_t libmod_tmx_unload_map(INSTANCE * my, int64_t * params) {
    tmx_map * map = (tmx_map *)params[0];
    tmx_map_free(map);
}

static void* tex_load(const char *path) {
    tmx_tex_t * tex = malloc(sizeof(tmx_tex_t));
    tex->graph = gr_load_img(path);
    return tex;
}

static void* tex_free(void * handler) {
    tmx_tex_t * tex = (tmx_tex_t *)handler;
    return (void *) grlib_unload_map(0, tex->graph);
}

void __bgdexport( libmod_tmx, module_initialize )() {
    tmx_img_load_func = tex_load;
}

void __bgdexport( libmod_tmx, module_finalize )() {
}

#include "libmod_tmx_exports.h"
