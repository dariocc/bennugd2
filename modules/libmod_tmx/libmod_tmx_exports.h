#ifndef __LIBMOD_TMX_EXPORTS
#define __LIBMOD_TMX_EXPORTS

#include "bgddl.h"
#include "tmx.h"

#if defined(__BGDC__) || !defined(__STATIC__)

char * __bgdexport( libmod_tmx, types_def ) =
    "TYPE TMX_TILESET_LIST_T\n"
    "END\n"

    "TYPE TMX_LAYER_T\n"
    "END\n"

    "TYPE TMX_TILE_T\n"
    "END\n"

    "TYPE TMX_TILEMAP_T\n"
    "     INT orient=TMX_O_NONE;\n"
    "     UINT width=0;\n"
    "     UINT height=0;\n"
    "     UINT tile_width=0;\n"
    "     UINT tile_height=0;\n"
    "     UINT tile_height=0;\n"
    "     INT renderorder=0;\n"
    "     TMX_TILESET_LIST_T POINTER ts_head;\n"
    "     TMX_LAYER_T POINTER ly_head;\n"
    "     TMX_TILE_T POINTER POINTER tiles;\n"
    "END\n"
    ;

DLCONSTANT  __bgdexport( libmod_tmx, constants_def)[] =
{
    { "TMX_FLIPPED_HORIZONTALLY"          , TYPE_INT32,       TMX_FLIPPED_HORIZONTALLY },
    { "TMX_FLIPPED_VERTICALLY"            , TYPE_INT32,       TMX_FLIPPED_VERTICALLY },
    { "TMX_FLIPPED_DIAGONALLY"            , TYPE_INT32,       TMX_FLIPPED_DIAGONALLY },
    { "TMX_FLIP_BITS_REMOVAL"             , TYPE_INT32,       TMX_FLIP_BITS_REMOVAL },

    { "TMX_O_NONE"                        , TYPE_INT,          O_NONE },
    { "TMX_O_ORT"                         , TYPE_INT,          O_ORT },
    { "TMX_O_ISO"                         , TYPE_INT,          O_ISO },
    { "TMX_O_STA"                         , TYPE_INT,          O_STA },
    { "TMX_O_HEX"                         , TYPE_INT,          O_HEX },
    { "TMX_R_NONE"                        , TYPE_INT,          R_NONE },
    { "TMX_R_RIGHTDOWN"                   , TYPE_INT,          R_RIGHTDOWN },
    { "TMX_R_RIGHTUP"                     , TYPE_INT,          R_RIGHTUP },
    { "TMX_R_LEFTDOWN"                    , TYPE_INT,          R_LEFTDOWN },
    { "TMX_R_LEFTUP"                      , TYPE_INT,          R_LEFTUP },
    { "TMX_SI_NONE"                       , TYPE_INT,          SI_NONE },
    { "TMX_SI_EVEN"                       , TYPE_INT,          SI_EVEN },
    { "TMX_SI_ODD"                        , TYPE_INT,          SI_ODD },
    { "TMX_SA_NONE"                       , TYPE_INT,          SA_NONE },
    { "TMX_SA_X"                          , TYPE_INT,          SA_X },
    { "TMX_SA_Y"                          , TYPE_INT,          SA_Y },

    // Documented in libtmx but non-existing in sources
    // { "TMX_OA_NONE"                       , TYPE_INT,          OA_NONE },
    // { "TMX_OA_TOP"                        , TYPE_INT,          OA_TOP },
    // { "TMX_OA_LEFT"                       , TYPE_INT,          OA_LEFT },
    // { "TMX_OA_BOTTOM"                     , TYPE_INT,          OA_BOTTOM },
    // { "TMX_OA_RIGHT"                      , TYPE_INT,          OA_RIGHT },
    // { "TMX_OA_TOPLEFT"                    , TYPE_INT,          OA_TOPLEFT },
    // { "TMX_OA_TOPRIGHT"                   , TYPE_INT,          OA_TOPRIGHT },
    // { "TMX_OA_BOTTOMLEFT"                 , TYPE_INT,          OA_BOTTOMLEFT },

    { "TMX_L_NONE"                        , TYPE_INT      , L_NONE},
    { "TMX_L_LAYER"                       , TYPE_INT      , L_LAYER},
    { "TMX_L_OBJGR"                       , TYPE_INT      , L_OBJGR},
    { "TMX_L_IMAGE"                       , TYPE_INT      , L_IMAGE},
    { "TMX_L_GROUP"                       , TYPE_INT      , L_GROUP},

    { "TMX_G_NONE"                        , TYPE_INT      , G_NONE},
    { "TMX_G_INDEX"                       , TYPE_INT      , G_INDEX},

    { "TMX_OT_NONE"                       , TYPE_INT      , OT_NONE},
    { "TMX_OT_SQUARE"                     , TYPE_INT      , OT_SQUARE},
    { "TMX_OT_POLYGON"                    , TYPE_INT      , OT_POLYGON},
    { "TMX_OT_POLYLINE"                   , TYPE_INT      , OT_POLYLINE},
    { "TMX_OT_ELLIPSE"                    , TYPE_INT      , OT_ELLIPSE},
    { "TMX_OT_TILE"                       , TYPE_INT      , OT_TILE},
    { "TMX_OT_TEXT"                       , TYPE_INT      , OT_TEXT},
    { "TMX_OT_POINT"                      , TYPE_INT      , OT_POINT},

    { "TMX_PT_NONE"                       , TYPE_INT       , PT_NONE },
    { "TMX_PT_INT"                        , TYPE_INT       , PT_INT },
    { "TMX_PT_FLOAT"                      , TYPE_INT       , PT_FLOAT },
    { "TMX_PT_BOOL"                       , TYPE_INT       , PT_BOOL },
    { "TMX_PT_STRING"                     , TYPE_INT       , PT_STRING },
    { "TMX_PT_COLOR"                      , TYPE_INT       , PT_COLOR },
    { "TMX_PT_FILE"                       , TYPE_INT       , PT_FILE },
    { "TMX_HA_NONE"                       , TYPE_INT       , HA_NONE },
    { "TMX_HA_LEFT"                       , TYPE_INT       , HA_LEFT },
    { "TMX_HA_CENTER"                     , TYPE_INT       , HA_CENTER },
    { "TMX_HA_RIGHT"                      , TYPE_INT       , HA_RIGHT },
    { "TMX_VA_NONE"                       , TYPE_INT       , VA_NONE },
    { "TMX_VA_TOP"                        , TYPE_INT       , VA_TOP },
    { "TMX_VA_CENTER"                     , TYPE_INT       , VA_CENTER },
    { "TMX_VA_BOTTOM"                     , TYPE_INT       , VA_BOTTOM },

    { NULL                      , 0             , 0                     }
} ;

#endif

/* Functions declaration                                             */

DLSYSFUNCS  __bgdexport( libmod_tmx, functions_exports)[] =
{
    FUNC( "TMX_LOAD"               , "S"    , TYPE_INT , libmod_tmx_load_map                   ),
    FUNC( "TMX_UNLOAD"             , "I"    , TYPE_INT , libmod_tmx_unload_map                 ),
    FUNC( "TMX_GET_MAP_WIDTH"      , "I"    , TYPE_DWORD , libmod_tmx_get_map_width            ),
    FUNC( "TMX_GET_MAP_HEIGHT"     , "I"    , TYPE_DWORD , libmod_tmx_get_map_height           ),
    FUNC( 0                 , 0         , 0                , 0                                 )
};

#endif