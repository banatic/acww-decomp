/* More questions about the scene (scene_kinds.h). */
#include "scene_kinds.h"

#include "autoload_2/process.h"
#include "clean.h"
#include "main/scene_place.h"
#include "main/scene_query.h"
#include "main/scene_setup.h"

/* The player's house rooms. */
#define SCENE_KINDS_HOUSE_FIRST 1
#define SCENE_KINDS_HOUSE_LAST 5
#define SCENE_KINDS_NO_HOUSE_ROOM (-1)
/* The group 6-8. */
#define SCENE_KINDS_GROUP_6_FIRST 6
#define SCENE_KINDS_GROUP_6_COUNT 3
/* The modes of data_020e54a8 that are the field: 0 outdoors, 1 in a room. */
#define SCENE_KINDS_MODE_OUTDOORS 0
#define SCENE_KINDS_MODE_ROOM 1
/* The process class of the process between scenes (scene_change.h). */
#define SCENE_KINDS_CHANGE_CLASS 5

/* The running scene's setup (scene_setup.h), NULL between scenes. */
extern SceneSetup *data_021f6948;
/* The running scene's process. */
extern Process *data_021f42f4;
/* The mode: 0 outdoors, 1 in a room, 2 between scenes. */
extern u8 data_020e54a8;
/* Each scene's sound kind (0-3), by scene. */
extern const u8 data_020d2150[SCENE_PLACE_SCENES];

/* func_020b6788 */
int SceneKinds_CurrentIsSession(void)
{
    return SceneKinds_IsSession(SceneQuery_Current());
}
CLEAN_AS(func_020b6788, SceneKinds_CurrentIsSession)

/* func_020b679c: whether `scene` is 6 or 7. */
int SceneKinds_IsSession(int scene)
{
    return scene == SCENE_KINDS_SESSION_FIRST || scene == SCENE_KINDS_SESSION_SECOND;
}
CLEAN_AS(func_020b679c, SceneKinds_IsSession)

/* func_020b67ac */
int SceneKinds_CurrentIn6To8(void)
{
    return SceneKinds_In6To8(SceneQuery_Current());
}
CLEAN_AS(func_020b67ac, SceneKinds_CurrentIn6To8)

/* func_020b67c0: whether `scene` is one of 6-8.
 * QUIRK: tested on the low byte of `scene` - 6, as the callers pass a byte. */
int SceneKinds_In6To8(int scene)
{
    return (u8) ((unsigned int) scene - SCENE_KINDS_GROUP_6_FIRST) < SCENE_KINDS_GROUP_6_COUNT;
}
CLEAN_AS(func_020b67c0, SceneKinds_In6To8)

/* func_020b67d4 */
int SceneKinds_CurrentIsHouseRoom(void)
{
    return SceneKinds_IsHouseRoom(SceneQuery_Current());
}
CLEAN_AS(func_020b67d4, SceneKinds_CurrentIsHouseRoom)

/* func_020b67e8: whether `scene` is one of the house rooms, 1-5. */
int SceneKinds_IsHouseRoom(unsigned int scene)
{
    return SceneKinds_HouseRoomIndex(scene) != SCENE_KINDS_NO_HOUSE_ROOM;
}
CLEAN_AS(func_020b67e8, SceneKinds_IsHouseRoom)

/* func_020b6804 */
int SceneKinds_CurrentHouseRoomIndex(void)
{
    return SceneKinds_HouseRoomIndex(SceneQuery_Current());
}
CLEAN_AS(func_020b6804, SceneKinds_CurrentHouseRoomIndex)

/* func_020b6818: the house room's index (`scene` - 1), -1 outside them. */
int SceneKinds_HouseRoomIndex(unsigned int scene)
{
    if (scene >= SCENE_KINDS_HOUSE_FIRST && scene <= SCENE_KINDS_HOUSE_LAST) {
        return (int) (scene - SCENE_KINDS_HOUSE_FIRST);
    }
    return SCENE_KINDS_NO_HOUSE_ROOM;
}
CLEAN_AS(func_020b6818, SceneKinds_HouseRoomIndex)

/* func_020b682c: the running scene's setup end (SceneSetup.end), as an address; 0 between
 * scenes. */
int SceneKinds_SetupEnd(void)
{
    const SceneSetup *setup = data_021f6948;
    if (setup == NULL) {
        return 0;
    }
    return (int) (uintptr_t) setup->end;
}
CLEAN_AS(func_020b682c, SceneKinds_SetupEnd)

/* func_020b6840: the current scene's sound kind (data_020d2150), which the sound code picks
 * its settings by. 0 when no scene process runs, when the scene is not one of the scenes
 * (ScenePlace_IsScene), and off the field (modes other than 0 and 1) unless `between_scenes`
 * is set and the running process is the one between scenes (class 5). */
int SceneKinds_SoundKind(int between_scenes)
{
    const Process *process = data_021f42f4;
    if (process == NULL) {
        return 0;
    }
    int on_field = data_020e54a8 == SCENE_KINDS_MODE_OUTDOORS || data_020e54a8 == SCENE_KINDS_MODE_ROOM;
    if (!on_field && (between_scenes == 0 || process->class_id != SCENE_KINDS_CHANGE_CLASS)) {
        return 0;
    }
    int scene = SceneQuery_Current();
    if (ScenePlace_IsScene((unsigned int) scene) == 0) {
        return 0;
    }
    return data_020d2150[scene];
}
CLEAN_AS(func_020b6840, SceneKinds_SoundKind)
