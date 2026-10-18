/* The OBJ graphics of /ab_all/ (ab_all_obj.h). */
#include "ab_all_obj.h"

#include <assert.h>
#include <stddef.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "rom_file.h"

static_assert(offsetof(AbAllObj, palettes) == 0x48, "AbAllObj layout");
static_assert(offsetof(AbAllObj, chars) == 0x4c, "AbAllObj layout");

#define CHARS_SIZE 0x1000  /* 128 16-colour characters */
#define PALETTES_SIZE 0x80 /* 4 16-colour palettes */

extern const char data_020d7204[]; /* "/ab_all/ab_all_obj_ncg.bin" */
extern const char data_020d7220[]; /* "/ab_all/ab_all_obj_ncl.bin" */
extern AbAllObj data_0213ff20;

extern void DC_FlushRange(const void *start, u32 size);
extern void GX_LoadOBJ(const void *src, u32 offset, u32 size);
extern void GXS_LoadOBJ(const void *src, u32 offset, u32 size);
extern void GX_LoadOBJPltt(const void *src, u32 offset, u32 size);
extern void GXS_LoadOBJPltt(const void *src, u32 offset, u32 size);
extern void FS_InitFile(void *file);

/* func_02003038: to the start of both screens' OBJ characters. */
void AbAllObj_UploadChars(AbAllObj *obj)
{
    DC_FlushRange(obj->chars, CHARS_SIZE);
    GX_LoadOBJ(obj->chars, 0, CHARS_SIZE);
    GXS_LoadOBJ(obj->chars, 0, CHARS_SIZE);
}
CLEAN_AS(func_02003038, AbAllObj_UploadChars)

/* func_02003064: to the first OBJ palettes of both screens. */
void AbAllObj_UploadPalettes(AbAllObj *obj)
{
    DC_FlushRange(obj->palettes, PALETTES_SIZE);
    GX_LoadOBJPltt(obj->palettes, 0, PALETTES_SIZE);
    GXS_LoadOBJPltt(obj->palettes, 0, PALETTES_SIZE);
}
CLEAN_AS(func_02003064, AbAllObj_UploadPalettes)

/* func_0200308c */
void AbAllObj_FreeChars(AbAllObj *obj)
{
    if (obj->chars != NULL) {
        Heap_FreeCurrent(obj->chars);
        obj->chars = NULL;
    }
}
CLEAN_AS(func_0200308c, AbAllObj_FreeChars)

/* func_020030a4 */
void AbAllObj_FreePalettes(AbAllObj *obj)
{
    if (obj->palettes != NULL) {
        Heap_FreeCurrent(obj->palettes);
        obj->palettes = NULL;
    }
}
CLEAN_AS(func_020030a4, AbAllObj_FreePalettes)

/* func_020030bc: load the characters into the current heap; whether that worked. */
int AbAllObj_LoadChars(AbAllObj *obj)
{
    obj->chars = RomFile_LoadDefault(data_020d7204);
    return obj->chars != NULL;
}
CLEAN_AS(func_020030bc, AbAllObj_LoadChars)

/* func_020030dc: load the palettes into the current heap; whether that worked. */
int AbAllObj_LoadPalettes(AbAllObj *obj)
{
    obj->palettes = RomFile_LoadDefault(data_020d7220);
    return obj->palettes != NULL;
}
CLEAN_AS(func_020030dc, AbAllObj_LoadPalettes)

/* func_02003100: NitroSDK's FS_InitFile on the object's file. */
void AbAllObj_InitFile(void *file)
{
    FS_InitFile(file);
}
CLEAN_AS(func_02003100, AbAllObj_InitFile)

/* func_02003108: load both files of the game's object (data_0213ff20), upload what loaded to
 * both screens and free it again. */
void AbAllObj_LoadAndUpload(void)
{
    AbAllObj *obj = &data_0213ff20;

    AbAllObj_InitFile(obj->file);
    int palettes_loaded = AbAllObj_LoadPalettes(obj);
    int chars_loaded = AbAllObj_LoadChars(obj);
    if (palettes_loaded) {
        AbAllObj_UploadPalettes(obj);
    }
    if (chars_loaded) {
        AbAllObj_UploadChars(obj);
    }
    AbAllObj_FreePalettes(obj);
    AbAllObj_FreeChars(obj);
}
CLEAN_AS(func_02003108, AbAllObj_LoadAndUpload)

/* func_0200314c: the destructor; frees what is still loaded and returns the object. */
AbAllObj *AbAllObj_Destruct(AbAllObj *obj)
{
    AbAllObj_FreePalettes(obj);
    AbAllObj_FreeChars(obj);
    return obj;
}
CLEAN_AS(func_0200314c, AbAllObj_Destruct)

/* func_02003164: nothing loaded. */
void AbAllObj_Init(AbAllObj *obj)
{
    obj->palettes = NULL;
    obj->chars = NULL;
}
CLEAN_AS(func_02003164, AbAllObj_Init)
