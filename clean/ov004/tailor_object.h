/* A room object of the RMO family (rmo_object.h) built from /roomObj/obj_tailor1, with a second
 * animated model built from /roomObj/obj_tailor2 (TailorObject_Start loads both). Only one
 * exists at a time: data_ov004_02258558 points to it from its start to its release. Overlay 4's
 * code outside it reads and sets the second model's frame through these functions, and asks
 * whether its state byte is 0 or 3.
 *
 * Its class has vtable 0x02255538 and 0x440 bytes. At its start the second model's material
 * "w" takes the texture of a piece of clothing (ClothTexture_Load, item_texture.h) drawn from
 * item list kind 2 (item_lists.h) with a dated random source set to today, so it shows the same
 * cloth all day. Its state (TailorObjectState) runs or stops the models: overlay 4's code
 * outside it asks for both (TailorObject_RunCurrent, TailorObject_StopCurrent). */
#ifndef CLEAN_OV004_TAILOR_OBJECT_H
#define CLEAN_OV004_TAILOR_OBJECT_H

#include "main/model_anim.h"
#include "main/vram_copy_task.h"
#include "rmo_object.h"
#include "types.h"

typedef struct TailorObject {
    RmoObject base;              /* 0x000: base.unk_24c[0] is its state byte (TailorObjectState) */
    RmoAnimatedModel part;       /* 0x290: obj_tailor2's model */
    RmoModel part_model;         /* 0x348 */
    RmoTexture part_texture;     /* 0x3ec */
    VramCopyMaterial cloth_copy; /* 0x3f0: the cloth's texture over the part's material "w" */
    ModelAnim body_anim;         /* 0x418: obj_tailor1's first texture animation, on the body */
    u8 unk_438[4];               /* 0x438 */
    fx32 stop_time;              /* 0x43c: time since TAILOR_OBJECT_STOPPING began, 20.12 frames */
} TailorObject;

/* Its states (TailorObject.base.unk_24c[0]), each with an entry and an update called through
 * tables of member pointers (member_pointer.h). */
enum TailorObjectState {
    TAILOR_OBJECT_IDLE = 0,     /* the models stand still */
    TAILOR_OBJECT_STARTING = 1, /* the part runs; the body and its animation run from the next frame */
    TAILOR_OBJECT_RUNNING = 2,  /* the part's sound plays in a window of each turn of its animation */
    TAILOR_OBJECT_STOPPING = 3, /* the part stands still; the body and its animation slow down */
    TAILOR_OBJECT_STATE_COUNT = 4
};

int TailorObject_PartFrame(void);
void TailorObject_SetPartFrame(int frame);
int TailorObject_InState0Or3(void);
int TailorObject_StopCurrent(void);
int TailorObject_RunCurrent(void);
void TailorObject_UpdateStopping(TailorObject *self);
int TailorObject_EnterStopping(TailorObject *self);
void TailorObject_UpdateRunning(TailorObject *self);
int TailorObject_EnterRunning(TailorObject *self);
void TailorObject_UpdateStarting(TailorObject *self);
int TailorObject_EnterStarting(TailorObject *self);
void TailorObject_UpdateIdle(TailorObject *self);
int TailorObject_EnterIdle(TailorObject *self);
void TailorObject_UpdateState(TailorObject *self);
int TailorObject_SetState(TailorObject *self, unsigned int state);
int TailorObject_Release(TailorObject *self);
int TailorObject_Draw(TailorObject *self);
int TailorObject_Update(TailorObject *self);
int TailorObject_Start(TailorObject *self);
TailorObject *TailorObject_Delete(TailorObject *self);
TailorObject *TailorObject_Destruct(TailorObject *self);
TailorObject *TailorObject_Construct(TailorObject *self);
void TailorObject_Create(void);

#endif
