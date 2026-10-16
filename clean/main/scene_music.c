/* The music of the current scene (scene_music.h). */
#include "scene_music.h"

#include "clean.h"
#include "player_record.h"
#include "player_records.h"

static_assert(sizeof(SceneMusic) == 0x14, "scene music size");
static_assert(offsetof(SceneMusic, music) == 0x0a, "scene music music");
static_assert(offsetof(SceneMusic, keep_music) == 0x10, "scene music keep");

/* The music asked for in the late hour, and the priorities of the late requests. */
#define SCENE_MUSIC_LATE_MUSIC 0x51
#define SCENE_MUSIC_LATE_MUSIC_PRIORITY 0x0f
#define SCENE_MUSIC_LATE_VALUE_PRIORITY 0x10
/* The priority of the scene's music. */
#define SCENE_MUSIC_PRIORITY 0x11
/* The entries of the table of scene musics (it ends at data_020c9fcc). */
#define SCENE_MUSIC_ENTRIES 29

typedef struct SceneMusicEntry {
    u8 scene;
    u8 unk_01;
    u16 music;
} SceneMusicEntry;

/* The object of the running process 0x020da334. */
extern Obj021c526c *data_021c526c;
extern const SceneMusicEntry data_020c9f58[SCENE_MUSIC_ENTRIES];

/* The current scene; the scene table at data_021f69d0 and its first byte, the scene being gone
 * to. */
extern u8 func_020b65c4(void);
extern void *func_020b5e10(void);
extern int func_020b5e84(u8 *table);
/* Whether the clock reads from h1:m1:s1 (included) to h2:m2:s2 (excluded), across midnight
 * when the second is earlier. */
extern u32 func_0203736c(void *clock, u32 h1, u32 m1, u32 s1, u32 h2, u32 m2, u32 s2);

/* func_02036584: in scenes 0x1a to 0x1f, unless the player's record has flag 0x23 or flag 1:
 * from 22:49:50 to 22:50:00 a request of priority 0x10 with word 0xc8 added (once), and from
 * 22:50:00 to midnight, or at once when it is forced, music 0x51 asked for (once). */
void SceneMusic_CheckLateHour(SceneMusic *self)
{
    u8 *record = PlayerRecords_Current();
    int flagged = 0;
    u8 scene;
    void *clock;

    if (record != NULL && (PlayerRecord_TestFlag(record, 0x23) != 0 || PlayerRecord_TestFlag(record, 1) != 0)) {
        flagged = 1;
    }
    scene = func_020b65c4();
    if (flagged || scene < 0x1a || scene > 0x1f) {
        return;
    }

    clock = SceneMusic_Clock();
    if (self->late_value_added == 0) {
        if (func_0203736c(clock, 22, 49, 50, 22, 50, 0) != 0) {
            Music_AddValue(SCENE_MUSIC_LATE_VALUE_PRIORITY, 0xc8, 0);
            self->late_value_added = 1;
        }
    }
    if (self->late_music_added == 0) {
        if (func_0203736c(clock, 22, 50, 0, 0, 0, 0) != 0 || self->late_music_forced != 0) {
            Music_Add(SCENE_MUSIC_LATE_MUSIC_PRIORITY, SCENE_MUSIC_LATE_MUSIC, 0x7f, 0);
            self->late_music_added = 1;
        }
    }
}
CLEAN_AS(func_02036584, SceneMusic_CheckLateHour)

/* func_02036648: the object's member at 0x24c, the clock. */
void *SceneMusic_Clock(void)
{
    return data_021c526c->unk_24c;
}
CLEAN_AS(func_02036648, SceneMusic_Clock)

/* func_0203665c: the late requests dropped and the forcing cleared. */
void SceneMusic_ClearLate(SceneMusic *self)
{
    if (self->late_value_added != 0) {
        Music_DropPriority(SCENE_MUSIC_LATE_VALUE_PRIORITY);
        self->late_value_added = 0;
    }
    if (self->late_music_added != 0) {
        Music_DropMusic(SCENE_MUSIC_LATE_MUSIC);
        self->late_music_added = 0;
    }
    self->late_music_forced = 0;
}
CLEAN_AS(func_0203665c, SceneMusic_ClearLate)

/* func_0203668c: when the scene has changed, its music asked for in place of the one before
 * when they differ. */
void SceneMusic_UpdateScene(SceneMusic *self)
{
    int scene = func_020b65c4();

    if (self->scene == scene) {
        return;
    }
    if (self->music != SceneMusic_ForScene((u8) scene)) {
        SceneMusic_Stop(self);
        SceneMusic_Start(self, scene);
    }
    self->scene = (u8) scene;
}
CLEAN_AS(func_0203668c, SceneMusic_UpdateScene)

/* func_020366c0: the music asked for dropped. */
void SceneMusic_Stop(SceneMusic *self)
{
    if (self->music != MUSIC_NONE) {
        Music_DropMusic(self->music);
        self->music = MUSIC_NONE;
    }
}
CLEAN_AS(func_020366c0, SceneMusic_Stop)

/* func_020366e0: the music of `scene` asked for at priority 0x11 (volume 0x38 for music 1, else
 * full; byte 0x10 set for musics 0x14 and 0x5c).
 * QUIRK: a scene without music still asks for MUSIC_NONE.
 * REQUIRES: scene < 0x100 (the ROM's table search compares the whole word; the game passes a
 * scene byte). */
void SceneMusic_Start(SceneMusic *self, int scene)
{
    int music = SceneMusic_ForScene((u8) scene);
    int volume = music == 1 ? 0x38 : 0x7f;
    int flag = music == 0x14 || music == 0x5c;

    Music_Add(SCENE_MUSIC_PRIORITY, music, volume, flag);
    self->music = (u16) music;
}
CLEAN_AS(func_020366e0, SceneMusic_Start)

/* func_02036714: whether the current scene and the scene being gone to have the same music, and
 * one. */
int SceneMusic_SameForNext(void)
{
    int current = func_020b65c4();
    int next = func_020b5e84(func_020b5e10());
    u16 current_music = SceneMusic_ForScene((u8) current);
    u16 next_music = SceneMusic_ForScene((u8) next);

    return current_music == next_music && current_music != MUSIC_NONE;
}
CLEAN_AS(func_02036714, SceneMusic_SameForNext)

/* func_02036754: the music of `scene` in the table, MUSIC_NONE when it is not there. */
u16 SceneMusic_ForScene(u8 scene)
{
    int i;

    for (i = 0; i < SCENE_MUSIC_ENTRIES; i++) {
        if (data_020c9f58[i].scene == scene) {
            return data_020c9f58[i].music;
        }
    }
    return MUSIC_NONE;
}
CLEAN_AS(func_02036754, SceneMusic_ForScene)

/* func_02036784: whether the scene's end leaves the music (Music2d0_Start and
 * Music2d0_Finish). */
void SceneMusic_SetKeep(SceneMusic *self, int keep)
{
    self->keep_music = (u8) keep;
}
CLEAN_AS(func_02036784, SceneMusic_SetKeep)

/* func_02036788: the scene's end (Music_OnSceneEnd): unless the music is kept, it is dropped
 * with the late requests, the scene forgotten, and music 0x51 forced for the next scene when it
 * was asked for and the member at 0x2d0 has its byte 0x0b set. */
void SceneMusic_OnSceneEnd(SceneMusic *self)
{
    if (self->keep_music == 0) {
        int carry = self->late_music_added != 0 && Music2d0_Is0bSet(Music_Object2d0()) != 0;

        SceneMusic_Stop(self);
        self->scene = SCENE_MUSIC_NO_SCENE;
        SceneMusic_ClearLate(self);
        self->late_music_forced = (u8) carry;
    }
    self->active = 0;
}
CLEAN_AS(func_02036788, SceneMusic_OnSceneEnd)

/* func_020367cc: the scene's start (Music_OnSceneStart): active, and the frame's work done. */
void SceneMusic_OnSceneStart(SceneMusic *self)
{
    self->active = 1;
    SceneMusic_UpdateScene(self);
    SceneMusic_CheckLateHour(self);
}
CLEAN_AS(func_020367cc, SceneMusic_OnSceneStart)

/* func_020367e4: music 0x51 forced (overlay 50). */
void SceneMusic_ForceLateMusic(SceneMusic *self)
{
    self->late_music_forced = 1;
}
CLEAN_AS(func_020367e4, SceneMusic_ForceLateMusic)

/* func_020367ec: the music and the late requests dropped and every mark cleared. */
void SceneMusic_Reset(SceneMusic *self)
{
    SceneMusic_Stop(self);
    self->scene = SCENE_MUSIC_NO_SCENE;
    SceneMusic_ClearLate(self);
    self->keep_music = 0;
    self->active = 0;
}
CLEAN_AS(func_020367ec, SceneMusic_Reset)

/* func_0203680c: the frame: while active, the scene's music and the late hour checked. */
void SceneMusic_Execute(SceneMusic *self)
{
    if (self->active != 0) {
        SceneMusic_UpdateScene(self);
        SceneMusic_CheckLateHour(self);
    }
}
CLEAN_AS(func_0203680c, SceneMusic_Execute)

/* func_02036828: the deletion: the reset. */
void SceneMusic_Delete(SceneMusic *self)
{
    SceneMusic_Reset(self);
}
CLEAN_AS(func_02036828, SceneMusic_Delete)

/* func_02036830: the creation: no scene, no music, no mark. */
void SceneMusic_Create(SceneMusic *self)
{
    self->scene = SCENE_MUSIC_NO_SCENE;
    self->music = MUSIC_NONE;
    self->late_value_added = 0;
    self->late_music_added = 0;
    self->late_music_forced = 0;
    self->active = 0;
    self->keep_music = 0;
}
CLEAN_AS(func_02036830, SceneMusic_Create)
