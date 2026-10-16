/* Questions about the scene (scene_query.h). */
#include "scene_query.h"

#include "clean.h"

/* The group of scenes 0x11-0x18, Nook's scenes and the group 0x20-0x29. */
#define SCENE_QUERY_GROUP_11_FIRST 0x11
#define SCENE_QUERY_GROUP_11_LAST 0x18
#define SCENE_QUERY_NOOK_FIRST 0x1a
#define SCENE_QUERY_NOOK_LAST 0x1f
#define SCENE_QUERY_GROUP_20_FIRST 0x20
#define SCENE_QUERY_GROUP_20_LAST 0x29
#define SCENE_QUERY_NOT_IN_GROUP (-1)
/* The scenes SceneQuery_IsOrdinary leaves out besides 6-8. */
#define SCENE_QUERY_SPECIAL_LATE_FIRST 0x2c
#define SCENE_QUERY_SPECIAL_LATE_LAST 0x2f
#define SCENE_QUERY_SPECIAL_FIRST 0x0c
#define SCENE_QUERY_SPECIAL_COUNT 3
/* The first season with snow. */
#define SCENE_QUERY_SNOW_SEASON 9
/* The modes of data_020e54a8 that are the field: 0 outdoors, 1 in a room. */
#define SCENE_QUERY_MODE_OUTDOORS 0
#define SCENE_QUERY_MODE_ROOM 1

extern u8 data_021f6a14[]; /* main's object for the touch screen's picks and the shadows */
extern u8 data_021ebcc8[]; /* the town layout; bits 2-7 of its byte 8 are the season */
extern u8 data_020e54b0;   /* the previous scene */
extern u8 data_020e54ac;   /* the current scene */
extern u8 data_020e54a8;   /* the mode */

/* Whether the scene is one of 6-8. */
extern int func_020b67c0(int scene);

/* func_020b6590: the object at data_021f6a14, as an address. */
int SceneQuery_FieldObject(void)
{
    return (int) (uintptr_t) data_021f6a14;
}
CLEAN_AS(func_020b6590, SceneQuery_FieldObject)

/* func_020b6598: whether the town's season has snow. */
int SceneQuery_IsSnowSeason(void)
{
    unsigned int season = (unsigned int) (data_021ebcc8[8] >> 2);
    return SceneQuery_SeasonHasSnow((int) season);
}
CLEAN_AS(func_020b6598, SceneQuery_IsSnowSeason)

/* func_020b65ac: whether `season` has snow (9 and later). */
int SceneQuery_SeasonHasSnow(int season)
{
    return season >= SCENE_QUERY_SNOW_SEASON;
}
CLEAN_AS(func_020b65ac, SceneQuery_SeasonHasSnow)

/* func_020b65b8 */
unsigned char SceneQuery_Previous(void)
{
    return data_020e54b0;
}
CLEAN_AS(func_020b65b8, SceneQuery_Previous)

/* func_020b65c4 */
unsigned char SceneQuery_Current(void)
{
    return data_020e54ac;
}
CLEAN_AS(func_020b65c4, SceneQuery_Current)

/* func_020b65d0: on the field (modes 0 and 1), whether the current scene is ordinary
 * (SceneQuery_IsOrdinary); 0 off the field. */
int SceneQuery_OnOrdinaryField(void)
{
    u8 mode = data_020e54a8;
    if (mode == SCENE_QUERY_MODE_OUTDOORS || mode == SCENE_QUERY_MODE_ROOM) {
        return SceneQuery_IsOrdinary(SceneQuery_Current());
    }
    return 0;
}
CLEAN_AS(func_020b65d0, SceneQuery_OnOrdinaryField)

/* func_020b660c: whether `scene` is none of 6-8, 0x2c-0x2f and 0x0c-0x0e.
 * QUIRK: the last range is tested on the low byte of `scene` - 0x0c, as the callers pass a
 * byte. */
int SceneQuery_IsOrdinary(int scene)
{
    if (func_020b67c0(scene) != 0) {
        return 0;
    }
    if (scene >= SCENE_QUERY_SPECIAL_LATE_FIRST && scene <= SCENE_QUERY_SPECIAL_LATE_LAST) {
        return 0;
    }
    if ((u8) ((unsigned int) scene - SCENE_QUERY_SPECIAL_FIRST) < SCENE_QUERY_SPECIAL_COUNT) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_020b660c, SceneQuery_IsOrdinary)

/* func_020b6640 */
int SceneQuery_CurrentIs31(void)
{
    return SceneQuery_Is31(SceneQuery_Current());
}
CLEAN_AS(func_020b6640, SceneQuery_CurrentIs31)

/* func_020b6654: whether `scene` is 0x31. */
int SceneQuery_Is31(int scene)
{
    return scene == 0x31;
}
CLEAN_AS(func_020b6654, SceneQuery_Is31)

/* func_020b6660 */
int SceneQuery_CurrentIs0(void)
{
    return SceneQuery_Is0(SceneQuery_Current());
}
CLEAN_AS(func_020b6660, SceneQuery_CurrentIs0)

/* func_020b6674: whether `scene` is 0. */
int SceneQuery_Is0(int scene)
{
    return scene == 0;
}
CLEAN_AS(func_020b6674, SceneQuery_Is0)

/* func_020b6680 */
int SceneQuery_CurrentIn11(void)
{
    return SceneQuery_In11(SceneQuery_Current());
}
CLEAN_AS(func_020b6680, SceneQuery_CurrentIn11)

/* func_020b6694: whether `scene` is one of 0x11-0x18. */
int SceneQuery_In11(int scene)
{
    return SceneQuery_IndexIn11((unsigned int) scene) != SCENE_QUERY_NOT_IN_GROUP;
}
CLEAN_AS(func_020b6694, SceneQuery_In11)

/* func_020b66b0 */
int SceneQuery_CurrentIndexIn11(void)
{
    return SceneQuery_IndexIn11(SceneQuery_Current());
}
CLEAN_AS(func_020b66b0, SceneQuery_CurrentIndexIn11)

/* func_020b66c4: the index of `scene` in 0x11-0x18, -1 outside it. */
int SceneQuery_IndexIn11(unsigned int scene)
{
    if (scene >= SCENE_QUERY_GROUP_11_FIRST && scene <= SCENE_QUERY_GROUP_11_LAST) {
        return (int) (scene - SCENE_QUERY_GROUP_11_FIRST);
    }
    return SCENE_QUERY_NOT_IN_GROUP;
}
CLEAN_AS(func_020b66c4, SceneQuery_IndexIn11)

/* func_020b66d8 */
int SceneQuery_CurrentIn20(void)
{
    return SceneQuery_In20(SceneQuery_Current());
}
CLEAN_AS(func_020b66d8, SceneQuery_CurrentIn20)

/* func_020b66ec: whether `scene` is one of 0x20-0x29. */
int SceneQuery_In20(unsigned int scene)
{
    return SceneQuery_IndexIn20(scene) != SCENE_QUERY_NOT_IN_GROUP;
}
CLEAN_AS(func_020b66ec, SceneQuery_In20)

/* func_020b6708 */
int SceneQuery_CurrentIndexIn20(void)
{
    return SceneQuery_IndexIn20(SceneQuery_Current());
}
CLEAN_AS(func_020b6708, SceneQuery_CurrentIndexIn20)

/* func_020b671c: the index of `scene` in 0x20-0x29, -1 outside it. */
int SceneQuery_IndexIn20(unsigned int scene)
{
    if (scene >= SCENE_QUERY_GROUP_20_FIRST && scene <= SCENE_QUERY_GROUP_20_LAST) {
        return (int) (scene - SCENE_QUERY_GROUP_20_FIRST);
    }
    return SCENE_QUERY_NOT_IN_GROUP;
}
CLEAN_AS(func_020b671c, SceneQuery_IndexIn20)

/* func_020b6730 */
int SceneQuery_CurrentInNook(void)
{
    return SceneQuery_InNook(SceneQuery_Current());
}
CLEAN_AS(func_020b6730, SceneQuery_CurrentInNook)

/* func_020b6744: whether `scene` is one of Nook's, 0x1a-0x1f. */
int SceneQuery_InNook(unsigned int scene)
{
    return SceneQuery_IndexInNook(scene) != SCENE_QUERY_NOT_IN_GROUP;
}
CLEAN_AS(func_020b6744, SceneQuery_InNook)

/* func_020b6760 */
int SceneQuery_CurrentIndexInNook(void)
{
    return SceneQuery_IndexInNook(SceneQuery_Current());
}
CLEAN_AS(func_020b6760, SceneQuery_CurrentIndexInNook)

/* func_020b6774: the index of `scene` in Nook's scenes, -1 outside them. */
int SceneQuery_IndexInNook(unsigned int scene)
{
    if (scene >= SCENE_QUERY_NOOK_FIRST && scene <= SCENE_QUERY_NOOK_LAST) {
        return (int) (scene - SCENE_QUERY_NOOK_FIRST);
    }
    return SCENE_QUERY_NOT_IN_GROUP;
}
CLEAN_AS(func_020b6774, SceneQuery_IndexInNook)
