/* The OBJ characters and palettes of /ab_all/ (ab_all_obj_ncg.bin, ab_all_obj_ncl.bin): loaded
 * into the current heap and uploaded to both screens' OBJ VRAM. */
#ifndef CLEAN_MAIN_AB_ALL_OBJ_H
#define CLEAN_MAIN_AB_ALL_OBJ_H

#include "types.h"

/* data_0213ff20 */
typedef struct AbAllObj {
    u8 file[0x48];  /* NitroSDK's FSFile */
    void *palettes; /* 0x48: ab_all_obj_ncl.bin, or NULL */
    void *chars;    /* 0x4c: ab_all_obj_ncg.bin, or NULL */
} AbAllObj;

void AbAllObj_UploadChars(AbAllObj *obj);
void AbAllObj_UploadPalettes(AbAllObj *obj);
void AbAllObj_FreeChars(AbAllObj *obj);
void AbAllObj_FreePalettes(AbAllObj *obj);
int AbAllObj_LoadChars(AbAllObj *obj);
int AbAllObj_LoadPalettes(AbAllObj *obj);
void AbAllObj_InitFile(void *file);
void AbAllObj_LoadAndUpload(void);
AbAllObj *AbAllObj_Destruct(AbAllObj *obj);
void AbAllObj_Init(AbAllObj *obj);

#endif
