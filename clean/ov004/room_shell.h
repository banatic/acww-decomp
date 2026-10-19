/* The model of the room itself in overlay 4 (vtable 0x02255ac8; data_ov004_022589fc points to
 * it from its start, RoomShell_Create, to its release): the walls and the floor of the
 * room shown, with their wallpaper and carpet (main/room_interior.h), a clock's hands and a
 * window. These functions are the part of its code between the telephone and the rest of it:
 *
 * - the hooks its model runs while drawn (set by RoomShell_SetModelHooks, which the model's
 *   init hook is): a material's goes to vtable slot 0x4c (RoomShell_MaterialHook), the one
 *   after a node's description to slot 0x48 (RoomShell_NodeDescHook). The material hook sets
 *   the texture matrix and repeat of the wallpaper's or the carpet's material while its code
 *   is one of 0x1188 to 0x11a7; the node hook turns the clock's hands (nodes "kh_j" and
 *   "km_j"), keeps where the hour hand's node is, and where node "hasu1" is (at height
 *   0x3700);
 * - the diffuse colour of material "wd", from the sky (RoomShell_WdDiffuse);
 * - the boards of the room (obj_etc_board, room_etc_board.h) made from the scene's map
 *   (RoomShell_SpawnBoards);
 * - the wallpaper's and the carpet's two item codes, a fallback code while there is none. */
#ifndef CLEAN_OV004_ROOM_SHELL_H
#define CLEAN_OV004_ROOM_SHELL_H

#include "main/g3d_render.h"
#include "autoload_2/process.h"
#include "autoload_2/vector.h"
#include "main/collision_box.h"
#include "main/material_bind.h"
#include "main/sound_emitter.h"
#include "room_object_methods.h" /* G3dRenderState */
#include "room_shell_members.h"
#include "room_surface.h"
#include "types.h"

/* The size of the parts at 0x128 (the wallpaper's) and 0x1228 (the carpet's) up to the
 * material each draws on. */
#define ROOM_SHELL_WALLPAPER_SIZE 0x10f4
#define ROOM_SHELL_CARPET_SIZE 0x20f4

typedef struct RoomShell {
    Process base;                         /* 0x0000 */
    RoomShellModel model;                 /* 0x0050: the room's model */
    RoomShellMaterialAnim material_anim;  /* 0x0108: its material animation */
    RoomWallpaper wallpaper;              /* 0x0128 */
    RoomCarpet carpet;                    /* 0x1228 */
    CollisionBox boxes[ROOM_SHELL_BOXES]; /* 0x3328 */
    CollisionBox box;                     /* 0x3460: scene 10's */
    RoomShellTouch touch;                 /* 0x34fc */
    s8 hour_hand_node;                    /* 0x3520: node "kh_j" */
    s8 minute_hand_node;                  /* 0x3521: node "km_j" */
    s8 size;                              /* 0x3522: the room's size, 4, 6 or 8 */
    s8 hasu1_node;                        /* 0x3523: node "hasu1" */
    u8 unk_3524[4];
    Vec3 hour_hand_position; /* 0x3528: the hour hand's node's translation, kept while drawn */
    SoundSource sound;       /* 0x3534: the clock's tick, at the hour hand */
    s8 wd_material;          /* 0x3540: material "wd", -1 for none */
    u8 pad_3541[3];
} RoomShell;

void RoomShell_SetModelHooks(G3dRenderState *state);
int RoomShell_RunNodeDescHook(G3dRenderState *state);
int RoomShell_RunMaterialHook(G3dRenderState *state);
short RoomShell_WdDiffuse(RoomShell *self);
void RoomShell_SpawnBoards(RoomShell *self);
void RoomShell_MaterialHook(RoomShell *self, u32 material, G3dRenderState *state);
void RoomShell_NodeDescHook(RoomShell *self, int node, G3dRenderState *state);
u16 *RoomShell_WallpaperCode(void);
u16 *RoomShell_WallpaperCode2(void);
u16 *RoomShell_CarpetCode(void);
u16 *RoomShell_CarpetCode2(void);
u16 *RoomShell_SetCarpet(u16 *item, int mode, int with_sound);
u16 *RoomShell_SetWallpaper(u16 *item, int mode, int with_sound);
void RoomShell_LightMaterials(RoomShell *self, u8 *model);
void RoomShell_ResetMatrix(RoomShell *self);
void RoomShell_LoadModel(RoomShell *self);
void RoomShell_LoadSurfaces(RoomShell *self);
void RoomShell_SceneSurfaces(RoomShell *self, u16 *wallpaper, int *wallpaper_mode, u16 *carpet, int *carpet_mode);
void RoomShell_MeasureSize(RoomShell *self);
int RoomShell_Release(RoomShell *self);
int RoomShell_Draw(RoomShell *self);
int RoomShell_Execute(RoomShell *self);
int RoomShell_Create(RoomShell *self);
RoomShell *RoomShell_Delete(RoomShell *self);
RoomShell *RoomShell_Destruct(RoomShell *self);
RoomShell *RoomShell_Construct(RoomShell *self);
void RoomShell_New(void);

#endif
