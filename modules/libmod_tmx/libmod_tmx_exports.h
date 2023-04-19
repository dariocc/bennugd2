#ifndef __LIBMOD_TMX_EXPORTS
#define __LIBMOD_TMX_EXPORTS

#include "bgddl.h"
#include "tmx.h"

#if defined(__BGDC__) || !defined(__STATIC__)

DLCONSTANT  __bgdexport( libmod_tmx, constants_def)[] =
{
    { "TMX_LAYER_TYPE_NONE"     , TYPE_INT      , L_NONE},
    { "TMX_LAYER_TYPE_LAYER"    , TYPE_INT      , L_LAYER},
    { "TMX_LAYER_TYPE_OBJGR"    , TYPE_INT      , L_OBJGR},
    { "TMX_LAYER_TYPE_GROUP"    , TYPE_INT      , L_GROUP},
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
