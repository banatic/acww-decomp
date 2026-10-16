/* The field actors' body looks (FIELD_ACTOR_BODY_LOOK, a slot byte at 0x389 of the actor):
 * each names one of four entries of the table at data_021c9c2c, which holds a body texture
 * file (func_0205d0e0), the VRAM region it is placed in (func_0205d0d4) and the queued task
 * that takes it to VRAM (func_0205d0c8, model_loader.h). */
#ifndef CLEAN_MAIN_BODY_LOOK_H
#define CLEAN_MAIN_BODY_LOOK_H

#include "main/model_loader.h"
#include "main/vram_region.h"
#include "types.h"

ModelLoaderTask *BodyLook_Task(unsigned char *look);
VramRegion *BodyLook_Region(unsigned char *look);
int BodyLook_File(unsigned char *look);
int BodyLook_PollUpload(void *look);
void BodyLook_PlaceTexture(void *look);

#endif
