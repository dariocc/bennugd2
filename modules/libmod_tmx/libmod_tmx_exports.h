#ifndef __LIBMOD_TMX_EXPORTS
#define __LIBMOD_TMX_EXPORTS

/* ----------------------------------------------------------------- */

#include "bgddl.h"
#include "libmod_tmx.h"

/* ----------------------------------------------------------------- */

#if defined(__BGDC__) || !defined(__STATIC__)

/* ----------------------------------------------------------------- */

DLCONSTANT  __bgdexport( libmod_tmx, constants_def)[] =
{
    /* Files */
    { "O_READ"                  , TYPE_QWORD    , 0                     },
    { NULL                      , 0             , 0                     }
} ;

#endif

/* Functions declaration                                             */

DLSYSFUNCS  __bgdexport( libmod_tmx, functions_exports)[] =
{
    /* Files */
    FUNC( "SAVE"            , "SV++"    , TYPE_INT          , libmod_tmx_file_save              ),
    FUNC( "FSEEK"           , "III"     , TYPE_INT          , libmod_tmx_file_fseek             ),

    FUNC( 0                 , 0         , 0                , 0                                   )
};

/* ----------------------------------------------------------------- */

#endif
