/*
 *  Copyright (C) 2006-2019 SplinterGU (Fenix/BennuGD)
 *  Copyright (C) 2002-2006 Fenix Team (Fenix)
 *  Copyright (C) 1999-2002 José Luis Cebrián Pagüe (Fenix)
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

#include <stdlib.h>
#include <string.h>

#include "bgdrtm.h"

#include "libbggfx.h"

/* --------------------------------------------------------------------------- */

FONT * fonts[ MAX_FONTS ] = { 0 };

static unsigned char default_font[ 256 * 8 ] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x7F, 0xC1, 0xF7, 0xC1, 0xFF, 0xDD, 0xC1, 0x7F,
    0x7F, 0xFF, 0xFF, 0xFF, 0xE3, 0xF7, 0xFF, 0x7F,
    0x7E, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00,
    0x18, 0x3C, 0x7E, 0xFF, 0x7E, 0x3C, 0x18, 0x00,
    0x3C, 0x7E, 0x3C, 0xFF, 0xFF, 0x7E, 0x3C, 0x7E,
    0x18, 0x18, 0x3C, 0x7E, 0xFF, 0x7E, 0x3C, 0x7E,
    0x00, 0x00, 0x1C, 0x3E, 0x3E, 0x1C, 0x00, 0x00,
    0xFF, 0xFF, 0xF7, 0xE3, 0xE3, 0xF7, 0xFF, 0xFF,
    0x00, 0x3E, 0x77, 0x63, 0x63, 0x77, 0x3E, 0x00,
    0xFF, 0xE3, 0xDD, 0xFF, 0xFF, 0xDD, 0xE3, 0xFF,
    0x0F, 0x07, 0x0F, 0x7F, 0xEE, 0xEE, 0xEE, 0x7C,
    0x3E, 0x77, 0x77, 0x77, 0x3E, 0x1C, 0x7F, 0x1C,
    0x3F, 0x3B, 0x3F, 0x38, 0x38, 0x78, 0xF8, 0xF0,
    0x7F, 0x73, 0x7F, 0x73, 0x73, 0x77, 0xF7, 0xE0,
    0xDD, 0x7F, 0x3E, 0xF7, 0xF7, 0x3E, 0x7F, 0xDD,
    0xC0, 0xF0, 0xFC, 0xFF, 0xFC, 0xF0, 0xC0, 0x00,
    0x03, 0x0F, 0x3F, 0xFF, 0x3F, 0x0F, 0x03, 0x00,
    0x1C, 0x3E, 0x7F, 0x1C, 0x1C, 0x7F, 0x3E, 0x1C,
    0x77, 0x77, 0x77, 0x77, 0x77, 0x00, 0x77, 0x00,
    0x7F, 0xFF, 0xFF, 0x7F, 0x1F, 0x1F, 0x1F, 0x00,
    0x3F, 0x73, 0x3C, 0x7E, 0x7E, 0x3C, 0xEE, 0x7C,
    0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00,
    0x1C, 0x3E, 0x7F, 0x1C, 0x7F, 0x3E, 0x1C, 0xFF,
    0x1C, 0x3E, 0x7F, 0x1C, 0x1C, 0x1C, 0x1C, 0x00,
    0x1C, 0x1C, 0x1C, 0x1C, 0x7F, 0x3E, 0x1C, 0x00,
    0x00, 0x1C, 0x0E, 0xFF, 0x0E, 0x1C, 0x00, 0x00,
    0x00, 0x38, 0x70, 0xFF, 0x70, 0x38, 0x00, 0x00,
    0x00, 0x00, 0xE0, 0xE0, 0xE0, 0xFF, 0x00, 0x00,
    0x00, 0x36, 0x77, 0xFF, 0x77, 0x36, 0x00, 0x00,
    0x00, 0x1C, 0x3E, 0x7F, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0xFF, 0xFF, 0x7F, 0x3E, 0x1C, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x00,
    0x00, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x36, 0x7F, 0x36, 0x36, 0x7F, 0x36, 0x00,
    0x00, 0x0C, 0x3F, 0x3C, 0x3F, 0x0F, 0x3F, 0x0C,
    0x00, 0x73, 0x76, 0x0C, 0x18, 0x37, 0x67, 0x00,
    0x00, 0x18, 0x3C, 0x18, 0x3F, 0x66, 0x3F, 0x00,
    0x00, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x06, 0x0C, 0x0C, 0x0C, 0x0C, 0x06, 0x00,
    0x00, 0x30, 0x18, 0x18, 0x18, 0x18, 0x30, 0x00,
    0x00, 0x00, 0x1E, 0x0C, 0x3F, 0x0C, 0x1E, 0x00,
    0x00, 0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x18,
    0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x1C, 0x00,
    0x00, 0x00, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x00,
    0x00, 0x3E, 0x67, 0x6F, 0x7B, 0x73, 0x3E, 0x00,
    0x00, 0x18, 0x78, 0x18, 0x18, 0x18, 0xFE, 0x00,
    0x00, 0x3E, 0x63, 0x03, 0x3E, 0x60, 0x7F, 0x00,
    0x00, 0x7E, 0x03, 0x3E, 0x03, 0x03, 0x7E, 0x00,
    0x00, 0x0E, 0x1E, 0x36, 0x66, 0x7F, 0x06, 0x00,
    0x00, 0x7F, 0x60, 0x7E, 0x03, 0x03, 0x7E, 0x00,
    0x00, 0x3F, 0x60, 0x7E, 0x63, 0x63, 0x3E, 0x00,
    0x00, 0x7F, 0x03, 0x06, 0x0C, 0x18, 0x18, 0x00,
    0x00, 0x3E, 0x63, 0x3E, 0x63, 0x63, 0x3E, 0x00,
    0x00, 0x3E, 0x63, 0x63, 0x3F, 0x03, 0x03, 0x00,
    0x00, 0x00, 0x00, 0x18, 0x00, 0x18, 0x00, 0x00,
    0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x18, 0x30,
    0x00, 0x00, 0x06, 0x0C, 0x18, 0x0C, 0x06, 0x00,
    0x00, 0x00, 0x00, 0x3F, 0x00, 0x3F, 0x00, 0x00,
    0x00, 0x00, 0x18, 0x0C, 0x06, 0x0C, 0x18, 0x00,
    0x00, 0x3E, 0x63, 0x06, 0x0C, 0x00, 0x0C, 0x00,
    0x00, 0x3E, 0x6F, 0x7F, 0x7F, 0x60, 0x3E, 0x00,
    0x00, 0x3E, 0x63, 0x63, 0x7F, 0x63, 0x63, 0x00,
    0x00, 0x7E, 0x63, 0x7E, 0x63, 0x63, 0x7E, 0x00,
    0x00, 0x3F, 0x60, 0x60, 0x60, 0x60, 0x3F, 0x00,
    0x00, 0x7E, 0x63, 0x63, 0x63, 0x63, 0x7E, 0x00,
    0x00, 0x7F, 0x60, 0x7C, 0x60, 0x60, 0x7F, 0x00,
    0x00, 0x7F, 0x60, 0x7F, 0x60, 0x60, 0x60, 0x00,
    0x00, 0x3F, 0x60, 0x60, 0x6F, 0x63, 0x3F, 0x00,
    0x00, 0x63, 0x63, 0x7F, 0x63, 0x63, 0x63, 0x00,
    0x00, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x00,
    0x00, 0x03, 0x03, 0x03, 0x03, 0x63, 0x3E, 0x00,
    0x00, 0x66, 0x6C, 0x7C, 0x66, 0x63, 0x63, 0x00,
    0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7F, 0x00,
    0x00, 0x63, 0x77, 0x7F, 0x63, 0x63, 0x63, 0x00,
    0x00, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x63, 0x00,
    0x00, 0x3E, 0x63, 0x63, 0x63, 0x63, 0x3E, 0x00,
    0x00, 0x7E, 0x63, 0x63, 0x7E, 0x60, 0x60, 0x00,
    0x00, 0x3E, 0x63, 0x63, 0x6F, 0x67, 0x3F, 0x00,
    0x00, 0x7E, 0x63, 0x63, 0x7E, 0x66, 0x63, 0x00,
    0x00, 0x3F, 0x60, 0x3E, 0x03, 0x03, 0x7E, 0x00,
    0x00, 0xFF, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00,
    0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3E, 0x00,
    0x00, 0x63, 0x63, 0x63, 0x36, 0x36, 0x1C, 0x00,
    0x00, 0x63, 0x63, 0x6B, 0x6B, 0x6B, 0x36, 0x00,
    0x00, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00,
    0x00, 0xC3, 0xC3, 0x7E, 0x18, 0x18, 0x18, 0x00,
    0x00, 0x7F, 0x06, 0x0C, 0x18, 0x30, 0x7F, 0x00,
    0x00, 0x0F, 0x0C, 0x0C, 0x0C, 0x0C, 0x0F, 0x00,
    0x00, 0x00, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x00,
    0x00, 0x78, 0x18, 0x18, 0x18, 0x18, 0x78, 0x00,
    0x00, 0x18, 0x3C, 0x7E, 0x18, 0x18, 0x18, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
    0x00, 0x1E, 0x33, 0x7C, 0x30, 0x30, 0x7F, 0x00,
    0x00, 0x00, 0x3C, 0x06, 0x3E, 0x66, 0x3E, 0x00,
    0x00, 0x60, 0x60, 0x7C, 0x66, 0x66, 0x7C, 0x00,
    0x00, 0x00, 0x3E, 0x60, 0x60, 0x60, 0x3E, 0x00,
    0x00, 0x03, 0x03, 0x1F, 0x33, 0x33, 0x1F, 0x00,
    0x00, 0x00, 0x1E, 0x33, 0x3E, 0x30, 0x1F, 0x00,
    0x00, 0x1F, 0x30, 0x3C, 0x30, 0x30, 0x30, 0x00,
    0x00, 0x00, 0x1F, 0x33, 0x33, 0x1F, 0x03, 0x3E,
    0x00, 0x30, 0x30, 0x3E, 0x33, 0x33, 0x33, 0x00,
    0x0C, 0x00, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x00,
    0x06, 0x00, 0x06, 0x06, 0x06, 0x06, 0x66, 0x3C,
    0x00, 0x30, 0x36, 0x36, 0x3E, 0x33, 0x33, 0x00,
    0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x0E, 0x00,
    0x00, 0x00, 0x7E, 0xDB, 0xDB, 0xDB, 0xDB, 0x00,
    0x00, 0x00, 0x3E, 0x33, 0x33, 0x33, 0x33, 0x00,
    0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00,
    0x00, 0x00, 0x3E, 0x33, 0x33, 0x3E, 0x30, 0x30,
    0x00, 0x00, 0x1F, 0x33, 0x33, 0x1F, 0x03, 0x03,
    0x00, 0x00, 0x36, 0x38, 0x30, 0x30, 0x30, 0x00,
    0x00, 0x00, 0x1F, 0x30, 0x1E, 0x03, 0x3E, 0x00,
    0x00, 0x18, 0x1E, 0x18, 0x18, 0x18, 0x0E, 0x00,
    0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x00,
    0x00, 0x00, 0x33, 0x33, 0x1E, 0x1E, 0x0C, 0x00,
    0x00, 0x00, 0x63, 0x63, 0x6B, 0x6B, 0x36, 0x00,
    0x00, 0x00, 0x33, 0x1E, 0x0C, 0x1E, 0x33, 0x00,
    0x00, 0x00, 0x33, 0x33, 0x33, 0x1F, 0x03, 0x3E,
    0x00, 0x00, 0x3F, 0x07, 0x0C, 0x38, 0x3F, 0x00,
    0x00, 0x07, 0x06, 0x1C, 0x06, 0x06, 0x07, 0x00,
    0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00,
    0x00, 0xF0, 0x30, 0x1C, 0x30, 0x30, 0xF0, 0x00,
    0x00, 0x3B, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x3E, 0x63, 0xDD, 0xF1, 0xF1, 0xDD, 0x63, 0x3E,
    0x7C, 0xC6, 0xC0, 0xC6, 0x7C, 0x0C, 0x06, 0x7C,
    0x3F, 0x00, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x00,
    0x07, 0x00, 0x1E, 0x33, 0x3E, 0x30, 0x1F, 0x00,
    0x7E, 0xC3, 0x3C, 0x06, 0x3E, 0x66, 0x3E, 0x00,
    0x7E, 0x00, 0x3C, 0x06, 0x3E, 0x66, 0x3E, 0x00,
    0x70, 0x00, 0x3C, 0x06, 0x3E, 0x66, 0x3E, 0x00,
    0x18, 0x18, 0x3C, 0x06, 0x3E, 0x66, 0x3E, 0x00,
    0x00, 0x00, 0x7C, 0xE0, 0xE0, 0x7C, 0x0E, 0x3C,
    0x3F, 0x61, 0x1E, 0x33, 0x3E, 0x30, 0x1E, 0x00,
    0x3F, 0x00, 0x1E, 0x33, 0x3E, 0x30, 0x1E, 0x00,
    0x38, 0x00, 0x1E, 0x33, 0x3E, 0x30, 0x1E, 0x00,
    0x00, 0x3F, 0x00, 0x0C, 0x0C, 0x0C, 0x0C, 0x00,
    0x00, 0x1E, 0x33, 0x0C, 0x0C, 0x0C, 0x0C, 0x00,
    0x00, 0x38, 0x00, 0x0C, 0x0C, 0x0C, 0x0C, 0x00,
    0xE7, 0x3C, 0x66, 0xC3, 0xFF, 0xC3, 0xC3, 0x00,
    0x38, 0x38, 0x00, 0x7C, 0xC6, 0xFE, 0xC6, 0x00,
    0x1E, 0x00, 0xFE, 0x70, 0x7C, 0x70, 0xFE, 0x00,
    0x00, 0x00, 0x7F, 0x0E, 0x7F, 0xEE, 0x7F, 0x00,
    0x3F, 0x7E, 0xEE, 0xFF, 0xEE, 0xEE, 0xEF, 0x00,
    0x3F, 0x61, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00,
    0x3F, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00,
    0x38, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00,
    0x1E, 0x33, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x00,
    0x38, 0x00, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x00,
    0x3F, 0x00, 0x36, 0x36, 0x1E, 0x06, 0x06, 0x3C,
    0xE3, 0x1C, 0x3E, 0x77, 0x77, 0x3E, 0x1C, 0x00,
    0xEE, 0x00, 0xEE, 0xEE, 0xEE, 0xEE, 0x7C, 0x00,
    0x1C, 0x1C, 0x7F, 0xC0, 0xC0, 0x7F, 0x1C, 0x1C,
    0x1C, 0x36, 0x33, 0x7C, 0x30, 0x63, 0x7E, 0x00,
    0xEE, 0xEE, 0x7C, 0xFE, 0x38, 0xFE, 0x38, 0x38,
    0xF8, 0xCC, 0xCC, 0xF8, 0xC6, 0xCF, 0xC6, 0xC7,
    0x0E, 0x1B, 0x18, 0x3E, 0x18, 0x18, 0xD8, 0x70,
    0x0E, 0x00, 0x3C, 0x06, 0x3E, 0x66, 0x3E, 0x00,
    0x00, 0x07, 0x00, 0x0C, 0x0C, 0x0C, 0x0C, 0x00,
    0x07, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00,
    0x07, 0x00, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x00,
    0x1E, 0x00, 0x3E, 0x33, 0x33, 0x33, 0x33, 0x00,
    0xFE, 0x00, 0xEE, 0xFE, 0xFE, 0xFE, 0xEE, 0x00,
    0x3C, 0x6C, 0x6C, 0x3F, 0x00, 0x7F, 0x00, 0x00,
    0x3C, 0x66, 0x66, 0x3C, 0x00, 0x7E, 0x00, 0x00,
    0x00, 0x18, 0x00, 0x18, 0x30, 0x63, 0x3E, 0x00,
    0x00, 0x00, 0x00, 0xFE, 0xE0, 0xE0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xFE, 0x0E, 0x0E, 0x00, 0x00,
    0xC3, 0xC6, 0xCC, 0xDF, 0x31, 0x63, 0xC6, 0x07,
    0xC3, 0xC6, 0xCC, 0xDB, 0x37, 0x6D, 0xCF, 0x01,
    0x00, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x00,
    0x00, 0x3F, 0x66, 0xCC, 0x66, 0x3F, 0x00, 0x00,
    0x00, 0xFC, 0x66, 0x33, 0x66, 0xFC, 0x00, 0x00,
    0x33, 0xCC, 0x33, 0xCC, 0x33, 0xCC, 0x33, 0xCC,
    0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF,
    0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF,
    0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C,
    0x1C, 0x1C, 0x1C, 0x1C, 0xFC, 0x1C, 0x1C, 0x1C,
    0x1C, 0x1C, 0xFC, 0x1C, 0xFC, 0x1C, 0x1C, 0x1C,
    0x3F, 0x3F, 0x3F, 0x3F, 0xFF, 0x3F, 0x3F, 0x3F,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x3F, 0x3F, 0x3F,
    0x00, 0x00, 0xFC, 0x1C, 0xFC, 0x1C, 0x1C, 0x1C,
    0x3F, 0x3F, 0xFF, 0x07, 0xFF, 0x3F, 0x3F, 0x3F,
    0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F,
    0x00, 0x00, 0xFF, 0x07, 0xFF, 0x3F, 0x3F, 0x3F,
    0x3F, 0x3F, 0xFF, 0x07, 0xFF, 0x00, 0x00, 0x00,
    0x3F, 0x3F, 0x3F, 0x3F, 0xFF, 0x00, 0x00, 0x00,
    0x1C, 0x1C, 0xFC, 0x1C, 0xFC, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xFC, 0x1C, 0x1C, 0x1C,
    0x1C, 0x1C, 0x1C, 0x1C, 0x1F, 0x00, 0x00, 0x00,
    0x1C, 0x1C, 0x1C, 0x1C, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x1C, 0x1C, 0x1C,
    0x1C, 0x1C, 0x1C, 0x1C, 0x1F, 0x1C, 0x1C, 0x1C,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
    0x1C, 0x1C, 0x1C, 0x1C, 0xFF, 0x1C, 0x1C, 0x1C,
    0x1C, 0x1C, 0x1F, 0x1C, 0x1F, 0x1C, 0x1C, 0x1C,
    0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F,
    0x3F, 0x3F, 0x3F, 0x38, 0x3F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x3F, 0x38, 0x3F, 0x3F, 0x3F, 0x3F,
    0x3F, 0x3F, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0xFF, 0x3F, 0x3F, 0x3F,
    0x3F, 0x3F, 0x3F, 0x38, 0x3F, 0x3F, 0x3F, 0x3F,
    0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00,
    0x3F, 0x3F, 0xFF, 0x00, 0xFF, 0x3F, 0x3F, 0x3F,
    0x1C, 0x1C, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00,
    0x3F, 0x3F, 0x3F, 0x3F, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0xFF, 0x1C, 0x1C, 0x1C,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x3F, 0x3F, 0x3F,
    0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x00, 0x00, 0x00,
    0x1C, 0x1C, 0x1F, 0x1C, 0x1F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x1F, 0x1C, 0x1F, 0x1C, 0x1C, 0x1C,
    0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x3F, 0x3F,
    0x3F, 0x3F, 0x3F, 0x3F, 0xFF, 0x3F, 0x3F, 0x3F,
    0x1C, 0x1C, 0xFF, 0x1C, 0xFF, 0x1C, 0x1C, 0x1C,
    0x1C, 0x1C, 0x1C, 0x1C, 0xFC, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1F, 0x1C, 0x1C, 0x1C,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
    0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8,
    0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
    0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x7F, 0xFE, 0xEC, 0xFE, 0x7F, 0x00,
    0x00, 0x7C, 0xEE, 0xFC, 0xEE, 0xFC, 0xE0, 0xE0,
    0x00, 0xFE, 0xEE, 0xE0, 0xE0, 0xE0, 0xE0, 0x00,
    0x00, 0xFF, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x00,
    0xFE, 0xEE, 0x70, 0x38, 0x70, 0xEE, 0xFE, 0x00,
    0x00, 0x00, 0x7F, 0xFC, 0xFC, 0xFC, 0x78, 0x00,
    0x00, 0x77, 0x77, 0x77, 0x77, 0x7E, 0x70, 0xE0,
    0x00, 0x7F, 0xFE, 0x1C, 0x1C, 0x1C, 0x1C, 0x00,
    0xFE, 0x38, 0x7C, 0xEE, 0xEE, 0x7C, 0x38, 0xFE,
    0x3C, 0x7E, 0xE7, 0xFF, 0xE7, 0x7E, 0x3C, 0x00,
    0x3C, 0x7E, 0xE7, 0xE7, 0x7E, 0x7E, 0xFF, 0x00,
    0x1E, 0x38, 0x1C, 0x7E, 0xEE, 0xEE, 0x7C, 0x00,
    0x00, 0x00, 0x7F, 0xFF, 0xFF, 0x7F, 0x00, 0x00,
    0x07, 0x0E, 0x7F, 0xFF, 0xFF, 0x7F, 0x70, 0xE0,
    0x3C, 0x70, 0xE0, 0xFC, 0xE0, 0x70, 0x3C, 0x00,
    0x7C, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0x00,
    0x00, 0xFE, 0x00, 0xFE, 0x00, 0xFE, 0x00, 0x00,
    0x38, 0x38, 0xFE, 0x38, 0x38, 0x00, 0xFE, 0x00,
    0x70, 0x38, 0x1C, 0x38, 0x70, 0x00, 0xFE, 0x00,
    0x1C, 0x38, 0x70, 0x38, 0x1C, 0x00, 0xFE, 0x00,
    0x0F, 0x1F, 0x1F, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C,
    0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0xFC, 0xFC, 0x78,
    0x38, 0x38, 0x00, 0xFE, 0x00, 0x38, 0x38, 0x00,
    0x00, 0x7F, 0xFE, 0x00, 0x7F, 0xFE, 0x00, 0x00,
    0x3C, 0x7E, 0x7E, 0x3C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x1C, 0x1C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00,
    0x0F, 0x0E, 0x0E, 0x0E, 0xFE, 0x7E, 0x3E, 0x1E,
    0x7C, 0x7E, 0x7E, 0x7E, 0x7E, 0x00, 0x00, 0x00,
    0x78, 0x1C, 0x38, 0x70, 0x7C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x3E, 0x3E, 0x3E, 0x3E, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : gr_font_new
 *
 *  Create a new font, with no characters in it.
 *  The font uses the MS-DOS charset and 8bpp by default.
 *
 *  PARAMS :
 *      charset
 *
 *  RETURN VALUE :
 *      Code of the new font or -1 if error
 *      The font data is in the global array fonts[id]
 *
 */

int64_t gr_font_new( int64_t charset ) {
    int fontid;

    for ( fontid = 1; fontid < MAX_FONTS; fontid++ ) if ( !fonts[ fontid ] ) break;

    if ( fontid >= MAX_FONTS ) return -1; // Too much fonts

    fonts[ fontid ] = ( FONT * ) malloc( sizeof( FONT ) );

    if ( !fonts[ fontid ] ) return -1; // No memory

    memset( fonts[ fontid ], 0, sizeof( FONT ) );
    fonts[ fontid ]->charset = charset; // CHARSET_CP850
    fonts[ fontid ]->maxwidth = 0;
    fonts[ fontid ]->maxheight = 0;

    return fontid;
}

/* --------------------------------------------------------------------------- */
/* Utility function used by gr_new_fontfrombitmap to align characters */

static int align_bitmap_char_left( unsigned char *data, int64_t width, int64_t height, int64_t pitch, int64_t bpp ) {
    int n, c, x, align = width;

    switch( bpp ) {
        case    1: {
                uint8_t * p = ( uint8_t * ) data;
                while ( height-- ) {
                    p = ( uint8_t * ) ( data + height * pitch );
                    for ( x = 0; x < width && !( p[ x >> 3 ] & ( 0x80 >> ( x & 3 ) ) ); x++ );
                    if ( align > x ) align = x;
                }
                break;
            }

        case    8: {
                uint8_t * p = ( uint8_t * ) data;
                while ( height-- ) {
                    p = ( uint8_t * ) ( data + height * pitch );
                    for ( x = 0; x < width && !*p++; x++ );
                    if ( align > x ) align = x;
                }
                break;
            }

        case    16: {
                uint16_t * p = ( uint16_t * ) data;
                while ( height-- ) {
                    p = ( uint16_t * ) ( data + height * pitch );
                    for ( x = 0; x < width && !*p++; x++ );
                    if ( align > x ) align = x;
                }
                break;
            }

        case    32: {
                uint32_t * p = ( uint32_t * ) data;
                while ( height-- ) {
                    p = ( uint32_t * ) ( data + height * pitch );
                    for ( x = 0; x < width && !*p++; x++ );
                    if ( align > x ) align = x;
                }
                break;
            }
    }

    return ( align == width ) ? 0 : align;
}

/* --------------------------------------------------------------------------- */
/* Utility function used by gr_new_fontfrombitmap to calculate char widths */

static int get_bitmap_char_width( unsigned char *data, int64_t width, int64_t height, int64_t pitch, int64_t bpp ) {
    int x, c, d, max = 0, w ;

    switch( bpp ) {
        case    1: {
                uint8_t * p;
                while ( height-- ) {
                    p = ( uint8_t * ) ( data + height * pitch );
                    for ( x = width; x > 0 && !( p[ x >> 3 ] & ( 0x80 >> ( x & 3 ) ) ); x-- );
                    if ( max < x ) max = x;
                }
                return ( max < 4 ) ? 4 : max;
            }

        case    8: {
                uint8_t * p;
                while ( height-- ) {
                    p = ( uint8_t * ) ( data + height * pitch + width - 1 );
                    for ( x = width; x > 0 && !*p--; x-- );
                    if ( max < x ) max = x;
                }
                return ( !max ) ? width * 65 / 100 : max;
            }

        case    16: {
                uint16_t * p;
                while ( height-- ) {
                    p = ( ( uint16_t * ) ( data + height * pitch ) ) + width - 1;
                    for ( x = width; x > 0 && !*p--; x-- );
                    if ( max < x ) max = x;
                }
                return ( !max ) ? width * 65 / 100 : max;
            }

        case    32: {
                uint32_t * p;
                while ( height-- ) {
                    p = ( ( uint32_t * ) ( data + height * pitch ) ) + width - 1;
                    for ( x = width; x > 0 && !*p--; x-- );
                    if ( max < x ) max = x;
                }
                return ( !max ) ? width * 65 / 100 : max;
        }
    }

    return width;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : gr_font_new_from_bitmap
 *
 *  Create a new font using a bitmap as source.
 *  For 1bpp fonts, the bitmap should be in black and white (1 bit per pixel)
 *  with a fixed character size and a character width of 8, 16, 24...
 *
 *  PARAMS :
 *  map         Pointer to the bitmap
 *  charset     Charset
 *  width       Width of each character, in bits (pixels)
 *  height      Height of each character
 *  first       First char
 *  last        Last char
 *  options     Can be 0 or a combination of the following flags:
 *                  NFB_FIXEDWIDTH  Create a fixed width font (the default is a propotional width one)
 *  charmap     Null char terminate string, used for map each character to a glyph, if it is NULL, then use "first" and "last" arguments
 *
 *  RETURN VALUE :
 *      -1 if Error, id otherwise
 *
 */

#ifdef USE_SDL2
int64_t gr_font_new_from_bitmap( GRAPH * map, int64_t charset, int64_t width, int64_t height, int64_t first, int64_t last, int64_t options, const unsigned char * charmap ) {
#endif
#ifdef USE_SDL2_GPU
int64_t gr_font_new_from_bitmap( GRAPH * map, SDL_Surface * source, int64_t charset, int64_t width, int64_t height, int64_t first, int64_t last, int64_t options, const unsigned char * charmap ) {
#endif
    FONT * f;
    char * chardata, * charptr;
    int i, id;
    int charrowsize, charcolsize;
    int w, h, cw, ch;
    SDL_Surface * surface;
#ifdef USE_SDL2
    surface = map->surface;
#endif

    if ( ( id = gr_font_new( charset ) ) == -1 ) return -1;

#ifdef USE_SDL2_GPU
    if ( !source ) surface = GPU_CopySurfaceFromImage( map->tex );
    else surface = source;
#endif

    f = fonts[ id ];

    f->fontmap = map;

    charrowsize = surface->pitch * height;
    charcolsize = surface->format->BytesPerPixel * width;

    ch = map->height / height;
    cw = map->width / width;

    i = charmap ? 0 : first;

    for ( h = 0; h < ch; h++ ) {
        chardata = surface->pixels + h * charrowsize;

        for ( charptr = chardata, w = 0; w < cw; w++, charptr += charcolsize, i++ ) {
            if ( (  charmap && !charmap[ i ] ) || ( !charmap && i > last ) ) { ch = h; break; }

            int align = 0;
            int idx = ( charmap ) ? ( charset == CHARSET_ISO8859 ) ? dos_to_win[charmap[ i ]] : i  : i;

            if ( options != NFB_FIXEDWIDTH )
                align = align_bitmap_char_left( ( ( unsigned char * ) charptr ),
                                                    width,
                                                    height,
                                                    surface->pitch,
                                                    surface->format->BitsPerPixel );

            f->glyph[ idx ].fontsource.x = w * width + align;
            f->glyph[ idx ].fontsource.y = h * height;
            f->glyph[ idx ].fontsource.w = width - align;
            f->glyph[ idx ].fontsource.h = height;
            f->glyph[ idx ].xoffset = 0;
            f->glyph[ idx ].yoffset = 0;

            if ( options != NFB_FIXEDWIDTH ) {
                int delta1 = 0, delta2 = 1,
                    ww = get_bitmap_char_width( surface->pixels +
                                                surface->pitch                 * ( ( int ) f->glyph[ idx ].fontsource.y ) +
                                                surface->format->BytesPerPixel * ( ( int ) f->glyph[ idx ].fontsource.x ),
                                                width - align,
                                                height,
                                                surface->pitch,
                                                surface->format->BitsPerPixel );

#if 0
               if ( ww & 1 ) {
                    if ( ( ww + align ) < width ) {
                        ww++;
                        delta2 = 0;
                    } else if ( align > 0 ) {
                        f->glyph[ idx ].fontsource.x--;
                        f->glyph[ idx ].xoffset = -1;
                        delta1 = 1;
                    } /* else bad font format */
                }
#endif
                f->glyph[ idx ].fontsource.w = ww + delta1;
                f->glyph[ idx ].xadvance = ww + delta2;
            }
            else
                f->glyph[ idx ].xadvance = width;
        }
    }

    /* Set a reasonable size for the space */

    f->glyph[ 32 ].xadvance = ( options != NFB_FIXEDWIDTH ) ? width * 65 / 100 : width;
    f->maxwidth = width;
    f->maxheight = height;

#ifdef USE_SDL2_GPU
    if ( !source ) SDL_FreeSurface( surface );
#endif
    return id;
}


/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : gr_font_systemfont
 *
 *  Create the system font. This function should be called once.
 *
 *  PARAMS :
 *  chardata  Pointer to the system font data
 *
 *  RETURN VALUE :
 *      Always returns 1
 *
 */

int gr_font_systemfont() {
    Uint32 * pixels = malloc( 8 * 8 * 256 * sizeof( Uint32 ) );
    if ( !pixels ) return 0;

    int i, ii, iii;

    // Convert 1bpp data to 32bpp data
    for ( i = 0; i < 256; i++ )
        for ( ii = 0; ii < 8; ii++ )
            for ( iii = 0; iii < 8; iii++ )
                pixels[ i * 64 + ii * 8 + iii ] = ( default_font[ i * 8 + ii ] & ( 0x80 >> iii ) ) ? 0xffffffff : 0;

    SDL_Surface * surface = SDL_CreateRGBSurfaceFrom(   pixels,
                                                        8,                          /* width  */
                                                        8 * 256,                    /* height */
                                                        gPixelFormat->BitsPerPixel, /* depth  */
                                                        8 * 4,                      /* pitch  */
                                                        gPixelFormat->Rmask,
                                                        gPixelFormat->Gmask,
                                                        gPixelFormat->Bmask,
                                                        gPixelFormat->Amask
                                                    );

    if ( !surface ) return 0;
//    SDL_SetColorKey( surface, SDL_TRUE, 0 );

    GRAPH *map = bitmap_new( 0, 0, 0, surface );
    if ( !map ) {
        SDL_FreeSurface( surface );
        return 0;
    }

    bitmap_add_cpoint( map, 0, 0 );

    int fontid;

#ifdef USE_SDL2
    fontid = gr_font_new_from_bitmap( map, CHARSET_CP850, 8, 8, 0, 255, 0, NULL );
#endif
#ifdef USE_SDL2_GPU
    fontid = gr_font_new_from_bitmap( map, surface, CHARSET_CP850, 8, 8, 0, 255, 0, NULL );
#endif

    SDL_FreeSurface( surface );

    if ( fontid == -1 ) return -1;

    if ( fonts[ 0 ] && fonts[ 0 ] != ( FONT * ) -1 ) gr_font_destroy( 0 );
    fonts[ 0 ] = fonts[ fontid ];
    fonts[ fontid ] = NULL;

    return 1;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : gr_font_destroy
 *
 *  Destroy a font and all the internal bitmap data
 *
 *  PARAMS :
 *  fontid  ID of the font
 *
 *  RETURN VALUE :
 *      None
 *
 */

void gr_font_destroy( int64_t fontid ) {
    int n;
    if ( fontid < 0 || fontid >= MAX_FONTS || !fonts[ fontid ] ) return;

    if ( fonts[ fontid ]->fontmap )
        bitmap_destroy( fonts[ fontid ]->fontmap );
    else
        for ( n = 0; n < MAX_GLYPH; n++ )
            bitmap_destroy( fonts[ fontid ]->glyph[ n ].glymap );

    free( fonts[ fontid ] );
    fonts[ fontid ] = NULL;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : gr_font_get
 *
 *  Return a font object, given an ID
 *
 *  PARAMS :
 *  id  id of the font
 *
 *  RETURN VALUE :
 *      Pointer to the font object or NULL if it does not exist
 *
 */

FONT * gr_font_get( int64_t id ) {
    if ( id < 0 || id >= MAX_FONTS ) return NULL;
    if ( !id && ( !fonts[ 0 ] || fonts[ 0 ] == ( FONT * ) -1 ) ) gr_font_systemfont();
    return fonts[ id ];
}

/* --------------------------------------------------------------------------- */

void gr_font_init() {
    fonts[ 0 ] = ( FONT * ) -1;
}

/* --------------------------------------------------------------------------- */
