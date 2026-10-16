/* The display of a scene on the field: set up when a scene starts (SceneDisplay_SetUp: the
 * VRAM banks, both engines' modes and planes, the texture managers, the model cache and the
 * caution window), taken down when it ends, and the 3D fog the scene draws with.
 *
 * The fog's settings (SceneFog, data_021f69ec) are reset when the scene has finished starting
 * (SceneDisplay_ResetFog: on outdoors, off in the rooms) and applied to the 3D engine before
 * each frame's drawing (SceneDisplay_ApplyFog); func_020bc078 changes the offset and
 * func_020bbf0c the alpha.
 *
 * SceneDisplay_AfterVBlank is the third hook of the display hooks a scene runs with
 * (data_021f693c, vtable data_020e550c, display_frame.h). */
#ifndef CLEAN_MAIN_SCENE_DISPLAY_H
#define CLEAN_MAIN_SCENE_DISPLAY_H

#include "types.h"

#define SCENE_FOG_TABLE_SIZE 0x20

typedef struct SceneFog {
    u8 table[SCENE_FOG_TABLE_SIZE]; /* 0x00: the density table (G3X_SetFogTable) */
    u8 enabled;                     /* 0x20 */
    u8 slope;                       /* 0x21: GXFogSlope */
    u16 offset;                     /* 0x22: the depth the fog starts at */
    u16 color;                      /* 0x24: RGB555 */
    u8 alpha;                       /* 0x26: 0-31 */
} SceneFog;

void SceneDisplay_AfterVBlank(void);
void SceneDisplay_SetFogTable(int unused, const u8 *table);
void SceneDisplay_SetFogOffset(unsigned int offset);
void SceneDisplay_SetFogAlpha(int alpha);
void SceneDisplay_TearDown(void);
void SceneDisplay_SetUp(void);
void SceneDisplay_ApplyFog(void *unused);
void SceneDisplay_ResetFog(void *unused);

#endif
