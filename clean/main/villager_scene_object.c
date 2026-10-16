/* The scene object of a town villager (villager_scene_object.h). */
#include "villager_scene_object.h"

#include "clean.h"
#include "session.h"
#include "villager_town.h"

#define VILLAGER_SCENE_OBJECT_EVENT 0x640    /* u8 */
#define VILLAGER_SCENE_OBJECT_WORD_644 0x644 /* u32 */
#define VILLAGER_SCENE_OBJECT_BYTE_648 0x648 /* u8 */

extern NetSession *data_020ccf94;

static u32 *villager_scene_object_word_644(void *object)
{
    return (u32 *) (void *) ((u8 *) object + VILLAGER_SCENE_OBJECT_WORD_644);
}

/* func_0201cddc */
u8 VillagerSceneObject_Event(u8 *object)
{
    return object[VILLAGER_SCENE_OBJECT_EVENT];
}
CLEAN_AS(func_0201cddc, VillagerSceneObject_Event)

/* func_0201cde8: the event going on (VillagerTown_CurrentEvent), unless others share the
 * session (no event, 11). */
void VillagerSceneObject_SetEvent(u8 *object)
{
    object[VILLAGER_SCENE_OBJECT_EVENT] = VILLAGER_SCENE_OBJECT_NO_EVENT;
    if (Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot) == 0) {
        object[VILLAGER_SCENE_OBJECT_EVENT] = (u8) VillagerTown_CurrentEvent();
    }
}
CLEAN_AS(func_0201cde8, VillagerSceneObject_SetEvent)

/* func_0201ce18: whether the word at 0x644 is not 0. */
u32 VillagerSceneObject_HasWord644(void *object)
{
    return *villager_scene_object_word_644(object) != 0;
}
CLEAN_AS(func_0201ce18, VillagerSceneObject_HasWord644)

/* func_0201ce2c (slot 0xbc) */
int VillagerSceneObject_VfuncBc(void *object)
{
    (void) object;
    return 0;
}
CLEAN_AS(func_0201ce2c, VillagerSceneObject_VfuncBc)

/* func_0201ce30 (slot 0xb8) */
int VillagerSceneObject_VfuncB8(void *object)
{
    (void) object;
    return 0;
}
CLEAN_AS(func_0201ce30, VillagerSceneObject_VfuncB8)

/* func_0201ce34 (slot 0xb4) */
int VillagerSceneObject_VfuncB4(void *object)
{
    (void) object;
    return 0;
}
CLEAN_AS(func_0201ce34, VillagerSceneObject_VfuncB4)

/* func_0201ce38 */
u8 VillagerSceneObject_Byte648(u8 *object)
{
    return object[VILLAGER_SCENE_OBJECT_BYTE_648];
}
CLEAN_AS(func_0201ce38, VillagerSceneObject_Byte648)

/* func_0201ce44 */
void VillagerSceneObject_SetByte648(u8 *object, u8 value)
{
    object[VILLAGER_SCENE_OBJECT_BYTE_648] = value;
}
CLEAN_AS(func_0201ce44, VillagerSceneObject_SetByte648)

/* func_0201ce50 */
u32 VillagerSceneObject_Word644(u32 *object)
{
    return *villager_scene_object_word_644(object);
}
CLEAN_AS(func_0201ce50, VillagerSceneObject_Word644)

/* func_0201ce5c */
void VillagerSceneObject_SetWord644(u32 *object, u32 value)
{
    *villager_scene_object_word_644(object) = value;
}
CLEAN_AS(func_0201ce5c, VillagerSceneObject_SetWord644)
