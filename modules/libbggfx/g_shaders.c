/*
 *  Copyright (C) 2006-2019 SplinterGU (Fenix/BennuGD)
 *
 *  This file is part of Bennu Game Development
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty. In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *     1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *
 *     2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *
 *     3. This notice may not be removed or altered from any source
 *     distribution.
 *
 */
/* --------------------------------------------------------------------------- */

#include <SDL.h>
#include <stdlib.h>
#include <string.h>

#include "libbggfx.h"

/* --------------------------------------------------------------------------- */

BGD_SHADER * shader_create( char * vertex, char * fragment, const char * position_name, const char * texcoord_name, const char * color_name, const char * modelViewMatrix_name ) {
    uint32_t vertex_shader = 0, frags_shader = 0;
    char * source = NULL, * source2 = NULL;
    int header_size;
    const char * header = "";
    BGD_SHADER * shader = malloc( sizeof( BGD_SHADER ) );

    if ( !shader ) {
        printf("memory error!\n");
        return NULL;
    }

    GPU_Renderer * renderer = GPU_GetCurrentRenderer();

    // Get size from header
    if ( renderer->shader_language == GPU_LANGUAGE_GLSL ) {
        if ( renderer->max_shader_version >= 120 ) header = "#version 120\n";
        else header = "#version 110\n";  // Maybe this is good enough?
    } else if( renderer->shader_language == GPU_LANGUAGE_GLSLES ) header = "#version 100\nprecision mediump int;\nprecision mediump float;\n";

    header_size = strlen( header );

    // Allocate source buffer
    source = ( char * ) malloc( header_size + strlen( vertex ) + 1 );
    if ( !source ) {
        printf("memory error 2!\n");
        free( shader );
        return NULL;
    }

    // Prepend header
    strcpy( source, header );
    strcat( source, vertex );

    // Compile the shader
    if ( !( vertex_shader = GPU_CompileShader( GPU_VERTEX_SHADER, source ) ) ) {
        printf("ERROR compile 1: %s\n", GPU_GetShaderMessage());
        free( source );
        free( shader );
        return NULL;
    }

    // Allocate source buffer
    source2 = ( char * ) realloc( source, header_size + strlen( fragment ) + 1 );
    if ( !source2 ) {
        printf("memory error 3!\n");
        GPU_FreeShader( vertex_shader );
        free( source );
        free( shader );
        return NULL;
    }

    // Prepend header
    strcpy( source2, header );
    strcat( source2, fragment );

    // Compile the shader
    if ( !( frags_shader = GPU_CompileShader( GPU_FRAGMENT_SHADER, source2 ) ) ) {
        printf("ERROR compile 2: %s\n", GPU_GetShaderMessage());
        GPU_FreeShader( vertex_shader );
        free( source2 );
        free( shader );
        return NULL;
    }

    // Clean up
    free( source2 );

    if ( !( shader->shader = GPU_LinkShaders( vertex_shader, frags_shader ) ) ) {
        printf("ERROR linking shaders: %s\n", GPU_GetShaderMessage());
        GPU_FreeShader( vertex_shader );
        GPU_FreeShader( frags_shader );
        free( shader );
        return NULL;
    }


    // example: "gpu_Vertex", "gpu_TexCoord", "gpu_Color", "gpu_ModelViewProjectionMatrix"
    shader->block = GPU_LoadShaderBlock( shader->shader, position_name, texcoord_name, color_name, modelViewMatrix_name );
    GPU_ActivateShaderProgram( shader->shader, &shader->block );

    return shader;
}

/* --------------------------------------------------------------------------- */

void shader_activate( BGD_SHADER * shader ) {
    GPU_ActivateShaderProgram( shader ? shader->shader : 0, shader ? &shader->block : NULL );
}

/* --------------------------------------------------------------------------- */

void shader_deactivate( void ) {
    GPU_DeactivateShaderProgram();
}

/* --------------------------------------------------------------------------- */

int shader_getattributelocation( BGD_SHADER * shader, const char * name ) {
    if ( !shader ) return -1;
    return ( int ) GPU_GetAttributeLocation( shader->shader, name );
}

/* --------------------------------------------------------------------------- */

int shader_getuniformlocation( BGD_SHADER * shader, const char * name ) {
    if ( !shader ) return -1;
    return ( int ) GPU_GetUniformLocation( shader->shader, name );
}

/* --------------------------------------------------------------------------- */

void shader_setshaderimage( GRAPH * image, int location, int image_unit ) {
    GPU_SetShaderImage( image->tex, location, image_unit );
}

/* --------------------------------------------------------------------------- */

void shader_setattributei( int location, int value ) {
    GPU_SetAttributei( location, value );
}

/* --------------------------------------------------------------------------- */

void shader_setattributeiv( int location, int nvalues, int * values ) {
    GPU_SetAttributeiv( location, nvalues, values );
}

/* --------------------------------------------------------------------------- */

void shader_setattributeui( int location, unsigned int value ) {
    GPU_SetAttributeui( location, value );
}

/* --------------------------------------------------------------------------- */

void shader_setattributeuiv( int location, int nvalues, unsigned int * values ) {
    GPU_SetAttributeuiv( location, nvalues, values );
}

/* --------------------------------------------------------------------------- */

void shader_setattributef( int location, float value ) {
    GPU_SetAttributef( location, value );
}

/* --------------------------------------------------------------------------- */

void shader_setattributefv( int location, int nvalues, float * values ) {
    GPU_SetAttributefv( location, nvalues, values );
}

/* --------------------------------------------------------------------------- */

void shader_setuniformi( int location, int value ) {
    GPU_SetUniformi( location, value );
}

/* --------------------------------------------------------------------------- */

void shader_setuniformiv( int location, int nvalues, int * values ) {
    GPU_SetUniformiv( location, 1, nvalues, values );
}

/* --------------------------------------------------------------------------- */

void shader_setuniform2iv( int location, int nvalues, int * values ) {
    GPU_SetUniformiv( location, 2, nvalues, values );
}

/* --------------------------------------------------------------------------- */

void shader_setuniform3iv( int location, int nvalues, int * values ) {
    GPU_SetUniformiv( location, 3, nvalues, values );
}

/* --------------------------------------------------------------------------- */

void shader_setuniform4iv( int location, int nvalues, int * values ) {
    GPU_SetUniformiv( location, 4, nvalues, values );
}

/* --------------------------------------------------------------------------- */

void shader_setuniformui( int location, unsigned int value ) {
    GPU_SetUniformui( location, value );
}

/* --------------------------------------------------------------------------- */

void shader_setuniformuiv( int location, int nvalues, unsigned int * values ) {
    GPU_SetUniformuiv( location, 1, nvalues, values );
}

/* --------------------------------------------------------------------------- */

void shader_setuniform2uiv( int location, int nvalues, unsigned int * values ) {
    GPU_SetUniformuiv( location, 2, nvalues, values );
}

/* --------------------------------------------------------------------------- */

void shader_setuniform3uiv( int location, int nvalues, unsigned int * values ) {
    GPU_SetUniformuiv( location, 3, nvalues, values );
}

/* --------------------------------------------------------------------------- */

void shader_setuniform4uiv( int location, int nvalues, unsigned int * values ) {
    GPU_SetUniformuiv( location, 4, nvalues, values );
}

/* --------------------------------------------------------------------------- */

void shader_setuniformf( int location, float value ) {
    GPU_SetUniformf( location, value );
}

/* --------------------------------------------------------------------------- */

void shader_setuniformfv( int location, int nvalues, float * values ) {
    GPU_SetUniformfv( location, 1, nvalues, values );
}

/* --------------------------------------------------------------------------- */

void shader_setuniform2fv( int location, int nvalues, float * values ) {
    GPU_SetUniformfv( location, 2, nvalues, values );
}

/* --------------------------------------------------------------------------- */

void shader_setuniform3fv( int location, int nvalues, float * values ) {
    GPU_SetUniformfv( location, 3, nvalues, values );
}

/* --------------------------------------------------------------------------- */

void shader_setuniform4fv( int location, int nvalues, float * values ) {
    GPU_SetUniformfv( location, 4, nvalues, values );
}

/* --------------------------------------------------------------------------- */

void shader_setuniformmatrix( int location, int num_matrices, int num_rows, int num_columns, GPU_bool transpose, float * values ) {
    GPU_SetUniformMatrixfv( location,  num_matrices,  num_rows,  num_columns,  transpose, values );
}

/* --------------------------------------------------------------------------- */

void shader_free( BGD_SHADER * shader ) {
    if ( !shader ) return;
    GPU_FreeShaderProgram( shader->shader );
    free( shader );
}

/* --------------------------------------------------------------------------- */