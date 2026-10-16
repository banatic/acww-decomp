/* The member at 0x2a0 of the field's sound object (music_queue.h, vtable data_020da2f4): the
 * music of the current scene, from the table of scene musics, asked of the music queue at
 * priority 0x11 when the scene starts and dropped when it ends, unless the scene being gone to
 * has the same music.
 *
 * In scenes 0x1a to 0x1f, while the clock (the object's member at 0x24c) reads from 22:49:50 to
 * 22:50:00 a request of priority 0x10 with word 0xc8 is added, and from 22:50:00 to midnight
 * music 0x51 at priority 0x0f; not when the player's record has flag 0x23 or flag 1. */
#ifndef CLEAN_MAIN_SCENE_MUSIC_H
#define CLEAN_MAIN_SCENE_MUSIC_H

#include "music_queue.h"
#include "types.h"

#define SCENE_MUSIC_NO_SCENE 0x3f

typedef struct SceneMusic {
    const u32 *vtable;
    Obj021c526c *owner; /* 0x04 */
    u8 scene;           /* 0x08: SCENE_MUSIC_NO_SCENE: none */
    u8 unk_09;
    u16 music;            /* 0x0a: MUSIC_NONE: none asked for */
    u8 late_value_added;  /* 0x0c: the request of priority 0x10 */
    u8 late_music_added;  /* 0x0d: music 0x51 */
    u8 late_music_forced; /* 0x0e: music 0x51 asked for whatever the clock reads */
    u8 active;            /* 0x0f: between a scene's start and its end */
    u8 keep_music;        /* 0x10: the scene's end leaves the music */
    u8 unk_11[3];
} SceneMusic;

void SceneMusic_CheckLateHour(SceneMusic *self);
void *SceneMusic_Clock(void);
void SceneMusic_ClearLate(SceneMusic *self);
void SceneMusic_UpdateScene(SceneMusic *self);
void SceneMusic_Stop(SceneMusic *self);
void SceneMusic_Start(SceneMusic *self, int scene);
int SceneMusic_SameForNext(void);
u16 SceneMusic_ForScene(u8 scene);
void SceneMusic_SetKeep(SceneMusic *self, int keep);
void SceneMusic_OnSceneEnd(SceneMusic *self);
void SceneMusic_OnSceneStart(SceneMusic *self);
void SceneMusic_ForceLateMusic(SceneMusic *self);
void SceneMusic_Reset(SceneMusic *self);
void SceneMusic_Execute(SceneMusic *self);
void SceneMusic_Delete(SceneMusic *self);
void SceneMusic_Create(SceneMusic *self);
SceneMusic *SceneMusic_DestructDelete(SceneMusic *self);
void SceneMusic_Destruct(SceneMusic *self);
void SceneMusic_Construct(SceneMusic *self, Obj021c526c *owner);

#endif
