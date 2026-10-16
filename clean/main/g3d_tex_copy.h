/* A named palette or texture image of one texture resource (g3d_resource.h) copied over a named
 * one of another, as the looks of field actors, heads and held items put a design into a
 * model's texture. The size copied is the destination's. */
#ifndef CLEAN_MAIN_G3D_TEX_COPY_H
#define CLEAN_MAIN_G3D_TEX_COPY_H

#include "g3d_resource.h"
#include "types.h"

void G3dTexCopy_Palette(G3dResTex *from, G3dResTex *to, const char *from_name, const char *to_name);
void G3dTexCopy_Image(G3dResTex *from, G3dResTex *to, const char *from_name, const char *to_name);

#endif
