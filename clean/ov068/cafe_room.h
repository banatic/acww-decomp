/* The room object of overlay 68 built from the /roomObj/ archives "obj_ms_cafe" and
 * "obj_cf_chr" (a room object of overlay 4's RMO family, ov004/rmo_object.h; vtable
 * data_ov068_02277f3c, include/cpp/ov068/Obj_ov068_02277f3c.h). Only one exists at a time:
 * data_ov068_022788b0 points to it while it runs.
 *
 * Besides its body it holds a second part from "obj_cf_chr" (CafeRoom.chr, drawn once loaded).
 * Its mode (the RMO object's byte 0x24c, set through its vtable slot 0x60 and told to the
 * game's shared value by func_ov004_0222c558) picks the alpha its body's materials fade to:
 * 1 in mode 0, 31 in mode 1. Each mode has an entry, which may refuse it, and an update, both
 * called through tables of C++ pointers to member functions. */
#ifndef CLEAN_OV068_CAFE_ROOM_H
#define CLEAN_OV068_CAFE_ROOM_H

#include "ov004/rmo_object.h"
#include "types.h"

#define CAFE_ROOM_MODES 2
#define CAFE_ROOM_ALPHA_FADED 1    /* mode 0 */
#define CAFE_ROOM_ALPHA_SHOWN 0x1f /* mode 1 */

typedef struct CafeRoom {
    RmoObject base;   /* 0x000: base.unk_24c[0] is its mode */
    s32 alpha;        /* 0x290: of the body's materials, moved to target_alpha */
    s32 target_alpha; /* 0x294 */
    u8 has_chr;       /* 0x298: chr was loaded */
    u8 pad_299[3];
    RmoAnimatedModel chr;   /* 0x29c: "obj_cf_chr" */
    RmoModel chr_model;     /* 0x354 */
    RmoTexture chr_texture; /* 0x3f8 */
} CafeRoom;

void CafeRoom_UpdateShown(CafeRoom *self);
int CafeRoom_EnterShown(CafeRoom *self);
void CafeRoom_UpdateFaded(CafeRoom *self);
int CafeRoom_EnterFaded(CafeRoom *self);
void CafeRoom_UpdateMode(CafeRoom *self);
int CafeRoom_SetMode(CafeRoom *self, unsigned int mode);
int CafeRoom_Release(CafeRoom *self);
int CafeRoom_Draw(CafeRoom *self);
int CafeRoom_Update(CafeRoom *self);
int CafeRoom_Start(CafeRoom *self);
CafeRoom *CafeRoom_DestructDelete(CafeRoom *self);
CafeRoom *CafeRoom_Destruct(CafeRoom *self);
CafeRoom *CafeRoom_Construct(CafeRoom *self);
void CafeRoom_New(void);

#endif
