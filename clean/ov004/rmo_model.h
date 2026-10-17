/* The parts the RMO family of overlay 4's room objects (rmo_object.h) is built from: the holder
 * of a /roomObj/ archive (RmoModel: the archive, its model and up to 13 animations of each
 * kind), the holder of its textures (RmoTexture: a copy of a .nsbtx file's texture resource),
 * the loading of both into a model object, and the calls the objects make on their sound
 * emitter (the base class of autoload_2/sound_emitter_class.h, at 0x250 of an RmoObject).
 *
 * An archive "/roomObj/<name>.arc" is mounted as "RMO" for the time of loading; its model is
 * "RMO:a/bmd/bmd0" and its animations "RMO:a/bca/bca<i>" (joints), "RMO:a/bma/bma<i>"
 * (materials) and "RMO:a/bta/bta<i>" (texture coordinates), read from 0 up to the first one
 * missing. The archive stays in the room's heap (data_021c9b24) until released; the texture
 * file "/roomObj/<name>.nsbtx" is read into the current heap, its textures put in VRAM and a
 * copy of the resource kept in the room's heap. */
#ifndef CLEAN_OV004_RMO_MODEL_H
#define CLEAN_OV004_RMO_MODEL_H

#include "autoload_2/sound_emitter_class.h"
#include "autoload_2/vector.h"
#include "main/model_object.h"
#include "main/sound_emitter.h"
#include "ov004/rmo_object.h"
#include "types.h"

int RmoSound_PlayEx(SoundEmitter *emitter, int number);
int RmoSound_Play(SoundEmitter *emitter, int number);
void RmoSound_Vfunc10(SoundEmitter *emitter);
void RmoSound_UpdateAt(SoundEmitter *emitter, const Vec3 *position);
void RmoSound_Stop(SoundEmitter *emitter);
SoundEmitterObject *RmoSound_Destruct(SoundEmitterObject *emitter);
SoundEmitterObject *RmoSound_Construct(SoundEmitterObject *emitter);

void *RmoTexture_Texture(RmoTexture *texture);
void RmoTexture_Release(RmoTexture *texture);
int RmoTexture_Load(RmoTexture *texture, const char *path);
void RmoTexture_Destruct(RmoTexture *texture);
void RmoTexture_Construct(RmoTexture *texture);

u8 *RmoModel_Model(RmoModel *model);
const u8 *RmoModel_TextureAnim(RmoModel *model, int index);
const u8 *RmoModel_MaterialAnim(RmoModel *model, int index);
const u8 *RmoModel_JointAnim(RmoModel *model, int index);
void RmoModel_Release(RmoModel *model);
int RmoModel_Load(RmoModel *model, const char *path);
void RmoModel_Clear(RmoModel *model);
RmoModel *RmoModel_Destruct(RmoModel *model);
RmoModel *RmoModel_Construct(RmoModel *model);

void RmoModel_ReleaseWithTexture(RmoModel *model, RmoTexture *texture);
int RmoModel_LoadNamed(const char *name, ModelObject *object, RmoModel *model, RmoTexture *texture);
int RmoModel_LoadWithTexture(const char *archive, const char *texture_path, ModelObject *object, RmoModel *model,
                             RmoTexture *texture);

#endif
