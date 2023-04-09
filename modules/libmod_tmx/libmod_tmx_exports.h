#ifndef __LIBMOD_TMX_EXPORTS
#define __LIBMOD_TMX_EXPORTS

/* ----------------------------------------------------------------- */

#include "bgddl.h"

/* ----------------------------------------------------------------- */

#if defined(__BGDC__) || !defined(__STATIC__)

/* ----------------------------------------------------------------- */

DLCONSTANT  __bgdexport( libmod_tmx, constants_def)[] =
{
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

/* ----------------------------------------------------------------- */

#endif
