/* The field actors' body looks (body_look.h). */
#include "body_look.h"

#include "clean.h"

/* The ModelLoaderTask.state of a task that is queued. */
#define BODY_LOOK_TASK_QUEUED 1

extern u8 data_021c9c2c[]; /* the looks' table */

extern ModelLoaderTask *func_0205d0c8(void *table, unsigned char look);
extern VramRegion *func_0205d0d4(void *table, unsigned char look);
extern int func_0205d0e0(void *table, unsigned char look);
extern void *func_021077e8(u8 *file); /* the file's texture resource */
extern int func_020b9eec(ModelLoaderTask *task, void *texture, int flag);

/* func_0205cfac: the task of the entry `look` names. */
ModelLoaderTask *BodyLook_Task(unsigned char *look)
{
    return func_0205d0c8(data_021c9c2c, *look);
}
CLEAN_AS(func_0205cfac, BodyLook_Task)

/* func_0205cfc0: the VRAM region of the entry `look` names. */
VramRegion *BodyLook_Region(unsigned char *look)
{
    return func_0205d0d4(data_021c9c2c, *look);
}
CLEAN_AS(func_0205cfc0, BodyLook_Region)

/* func_0205cfd4: the texture file of the entry `look` names, as an address. */
int BodyLook_File(unsigned char *look)
{
    return func_0205d0e0(data_021c9c2c, *look);
}
CLEAN_AS(func_0205cfd4, BodyLook_File)

/* func_0205cfe8: whether the look's texture is in VRAM (its task done); when the task is
 * neither done nor queued, the file's texture is queued (FALSE until it is done). */
int BodyLook_PollUpload(void *look)
{
    ModelLoaderTask *task = BodyLook_Task(look);
    u8 state = task->state;
    if (state == MODEL_LOADER_TASK_DONE) {
        return 1;
    }
    if (state != BODY_LOOK_TASK_QUEUED) {
        u8 *file = (u8 *) (uintptr_t) BodyLook_File(look);
        func_020b9eec(task, func_021077e8(file), 1);
    }
    return 0;
}
CLEAN_AS(func_0205cfe8, BodyLook_PollUpload)

/* func_0205d034: the look's texture placed in its VRAM region (its keys given to the texture
 * resource). */
void BodyLook_PlaceTexture(void *look)
{
    void *texture = func_021077e8((u8 *) (uintptr_t) BodyLook_File(look));
    VramRegion_PlaceTexture(BodyLook_Region(look), texture);
}
CLEAN_AS(func_0205d034, BodyLook_PlaceTexture)
