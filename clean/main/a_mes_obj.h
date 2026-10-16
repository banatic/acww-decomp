/* The OBJ characters and palettes of /a_mes/ (the files a_mes_obj_ncg.bin, a_mes_obj_ncl.bin
 * and their variants a_mes_ten0..3_obj_*.bin), kept in one object (data_021c1284, made by
 * __sinit_020c4248): loaded from the file into the current heap or into the object's own
 * buffer, uploaded to the OBJ VRAM of one or both screens, and freed again.
 *
 * The parts loaded on their own:
 * - the window: 2 rows of 20 characters (0x280 bytes each) at OBJ character offset 0x1000,
 *   or the whole sheet (0x3000 bytes) there, with 9 palettes (4 to 11 and 15);
 * - 2 rows of 8 characters (0x100 bytes each) at 0x1180, kept in the object's buffer: shown
 *   with the window of style 2 while the touch screen controls the game, and switched by
 *   func_0208b034, which leaves the upload pending until AMesObj_UploadPending;
 * - the icon of ScreenIcon (screen_icon.h), 2 rows of 2 characters at 0x38c0, one block per
 *   variant;
 * - the icon of WirelessIcon (wireless_icon.h), 2 rows of 8 characters at 0x3300.
 * Rows of the sheet in the file, as in VRAM, are 0x400 bytes (32 characters) apart.
 *
 * Which file a part comes from depends on a kind: 0 to 3, or 4 for the style of the current
 * scene (AMesObj_Style), and for kinds 0 and 1 on the object's `variant`. */
#ifndef CLEAN_MAIN_A_MES_OBJ_H
#define CLEAN_MAIN_A_MES_OBJ_H

#include "types.h"

/* Where an upload goes: both screens, the main screen's OBJ VRAM (GX), the sub screen's
 * (GXS), or neither. */
#define AMES_SCREENS_BOTH 0
#define AMES_SCREENS_MAIN 1
#define AMES_SCREENS_SUB 2
#define AMES_SCREENS_NONE 3

/* The kind that stands for the current scene's style. */
#define AMES_KIND_SCENE 4

/* data_021c1284 */
typedef struct AMesObj {
    u8 file[0x48];         /* NitroSDK's FSFile */
    u8 *palettes;          /* 0x48: from the heap, or NULL */
    u8 *chars;             /* 0x4c: from the heap, or NULL */
    u8 extra_chars[0x200]; /* 0x50: 2 rows of 8 characters */
    u32 pending_screens;   /* 0x250: where extra_chars still go, AMES_SCREENS_NONE for nowhere */
    u8 ready;              /* 0x254: set once the scene's graphics are in place */
    u8 variant;            /* 0x255: picks the other file for kinds 0 and 1 */
} AMesObj;

void AMesObj_FreeScreenIcon(AMesObj *obj);
void AMesObj_UploadScreenIcon(AMesObj *obj);
int AMesObj_LoadScreenIcon(AMesObj *obj, int mode);
void AMesObj_FreeWirelessIcon(AMesObj *obj);
void AMesObj_UploadWirelessIcon(AMesObj *obj);
int AMesObj_LoadWirelessIcon(AMesObj *obj, int wfc);
void AMesObj_UploadExtraChars(AMesObj *obj, int screens);
int AMesObj_LoadExtraChars(AMesObj *obj, int alternate);
void AMesObj_UploadWindowChars(AMesObj *obj, int screens);
void AMesObj_FreeWindowChars(AMesObj *obj);
int AMesObj_LoadWindowChars(AMesObj *obj, int kind);
void AMesObj_UploadSheet(AMesObj *obj, u32 screens);
void AMesObj_UploadPalettes(AMesObj *obj, u32 screens);
void AMesObj_FreeChars(AMesObj *obj);
void AMesObj_FreePalettes(AMesObj *obj);
int AMesObj_LoadSheet(AMesObj *obj);
int AMesObj_LoadPalettes(AMesObj *obj, int kind);
const char *AMesObj_CharsPath(const AMesObj *obj, int kind);
const char *AMesObj_PalettesPath(const AMesObj *obj, int kind);
void AMesObj_InitFile(void *file);
void AMesObj_ShowScreenIcon(AMesObj *obj, int mode);
void AMesObj_ShowWirelessIcon(AMesObj *obj, int wfc);
void AMesObj_ShowExtraChars(AMesObj *obj, int alternate, int defer, int screens);
void AMesObj_ShowWindow(AMesObj *obj, int kind, int screens);
void AMesObj_ShowSheet(AMesObj *obj, int screens);
void AMesObj_ClearReady(void);
void AMesObj_SetReady(void);
u8 AMesObj_IsReady(void);
u8 AMesObj_Style(void);
void AMesObj_UploadPending(void);
void AMesObj_SetScreenIcon(int mode);
void AMesObj_SetWirelessIcon(int wfc);
u8 AMesObj_Variant(void);
void AMesObj_SetVariant(u8 variant);
void AMesObj_SetExtraChars(int alternate, int defer, int screens);
void AMesObj_SetWindow(int kind, int screens);
void AMesObj_SetSheetSub(void);
void AMesObj_SetSheetBoth(void);
AMesObj *AMesObj_Destruct(AMesObj *obj);
AMesObj *AMesObj_Construct(AMesObj *obj);

#endif
