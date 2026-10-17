/* The taxi of overlay 68 (a room object of overlay 4's RMO family, ov004/rmo_object.h; vtable
 * data_ov068_022778f4, 0x5a4 bytes), built from three /roomObj/ archives: the car "obj_taxi"
 * (the family's body, with a texture animation and a material animation of its own), its
 * figure "obj_taxi_fig" and its handle "obj_taxi_hdl". Only one exists at a time: overlay 51
 * reaches it through data_ov068_022787fc (Taxi_StartFigure, Taxi_StopRain).
 *
 * The car's materials "m_rainA", "m_rainB" and "m_splash" are drawn with an alpha it keeps;
 * the handle plays the animation matching the one overlay 51's speaker plays. Three states:
 *
 *   0 rain:      alpha 31, the car's animations looping; sounds 0x886 and 0x887 at frames 0
 *                and 0x1c of the car's animation.
 *   1 rain ends: the same, the alpha counting down by one every third frame; at 0, state 2.
 *   2 dry:       alpha 0, the car's animations played once from where they are; nothing more.
 *
 * Starting it also starts the sounds 0x884 and 0x885, which its release stops. */
#ifndef CLEAN_OV068_TAXI_H
#define CLEAN_OV068_TAXI_H

#include "main/model_anim.h"
#include "ov004/rmo_object.h"
#include "types.h"

#define TAXI_STATES 3

typedef struct Taxi {
    RmoObject base;            /* 0x000: the car */
    ModelAnim material_anim;   /* 0x290: the car's material animation (bma) */
    ModelAnim texture_anim;    /* 0x2b0: the car's texture animation (bta) */
    RmoAnimatedModel figure;   /* 0x2d0: "obj_taxi_fig" */
    RmoModel figure_model;     /* 0x388 */
    RmoTexture figure_texture; /* 0x42c */
    u8 figure_plays;           /* 0x430: the figure's animation steps once Taxi_StartFigure ran */
    u8 pad_431[3];
    RmoAnimatedModel handle;   /* 0x434: "obj_taxi_hdl" */
    RmoModel handle_model;     /* 0x4ec */
    RmoTexture handle_texture; /* 0x590 */
    s32 state;                 /* 0x594: 0-2 */
    u16 frames;                /* 0x598: counted in state 1 */
    s16 alpha;                 /* 0x59a: of the rain materials, 31 down to 0 */
    s16 materials[3];          /* 0x59c: the indices of "m_rainA", "m_rainB" and "m_splash" */
    u8 pad_5a2[2];
} Taxi;

void Taxi_PlayPartAnim(Taxi *self, int anim, RmoAnimatedModel *model, RmoModel *source, u8 flags, fx32 speed, u16 start,
                       u16 frames);
void Taxi_OnMaterial(void);
int Taxi_StartFigure(void);
int Taxi_StopRain(void);
void Taxi_UpdateDry(void);
int Taxi_EnterDry(Taxi *self);
void Taxi_UpdateRainEnds(Taxi *self);
int Taxi_EnterRainEnds(Taxi *self);
void Taxi_PlaySounds(Taxi *self);
int Taxi_EnterRain(Taxi *self);
void Taxi_UpdateState(Taxi *self);
int Taxi_SetState(Taxi *self, int state);
void Taxi_RestartCar(Taxi *self, int flags);
void Taxi_Load(Taxi *self);
int Taxi_Release(Taxi *self);
int Taxi_Draw(Taxi *self);
int Taxi_Update(Taxi *self);
int Taxi_Start(Taxi *self);
Taxi *Taxi_Delete(Taxi *self);
Taxi *Taxi_Destruct(Taxi *self);
Taxi *Taxi_Construct(Taxi *self);
struct TaxiRenderState;
void Taxi_SetModelHooks(struct TaxiRenderState *state);
const Taxi *Taxi_MaterialHook(struct TaxiRenderState *state);

#endif
