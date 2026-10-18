/* The sound of the current scene: one object at data_0213fff0, of a class chosen from the
 * scene number (func_020b65c4), the time of day and a few checks of the game's state when
 * the scene starts (SceneSound_Create). The classes live in autoload_2 next to the sound
 * layer, are 8 bytes long (one 0x20 and one 0x38) and share the base vtable at 0x0213efb4:
 * start (slot 3: load the scene's sounds, after saving the sound heap's level), the frame's
 * update (slot 4), stopping (slot 5), unloading (slot 6: back to the saved level) and the
 * keyboard's mode (slot 7).
 *
 * Also here: the start-up of the sound layer and its part of each frame. */
#ifndef CLEAN_MAIN_SCENE_SOUND_H
#define CLEAN_MAIN_SCENE_SOUND_H

#include "types.h"

struct SceneSound;

typedef struct SceneSoundVtable {
    const void *destruct;                                         /* 0x00 */
    void (*destruct_delete)(struct SceneSound *sound);            /* 0x04 */
    const void *unk_08;                                           /* 0x08 */
    void (*start)(struct SceneSound *sound);                      /* 0x0c */
    void (*update)(struct SceneSound *sound, int value);          /* 0x10 */
    void (*stop)(struct SceneSound *sound);                       /* 0x14 */
    void (*unload)(struct SceneSound *sound);                     /* 0x18 */
    int (*set_keyboard_mode)(struct SceneSound *sound, int mode); /* 0x1c */
    void (*vfunc_20)(struct SceneSound *sound);                   /* 0x20 */
    void (*vfunc_24)(struct SceneSound *sound, int value);        /* 0x24: nothing in the base */
} SceneSoundVtable;

typedef struct SceneSound {
    const SceneSoundVtable *vtable;
    s8 unk_04[4];
} SceneSound;

void SceneSound_Vfunc24(int value);
void SceneSound_BaseVfunc24(void);
void SceneSound_Vfunc20(void);
int SceneSound_SetKeyboardMode(int mode);
void SceneSound_Stop(void);
void SceneSound_Delete(void);
void SceneSound_Create(void);
void SoundLayer_Frame(void);
void SoundLayer_Init(void);

#endif
