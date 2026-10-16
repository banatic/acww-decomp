/* Main's code at 020ba298 (block_020ba298.h). */
#include "block_020ba298.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "player_record.h"
#include "player_records.h"

extern const u32 data_020e69a4[]; /* the class's vtable */
extern const u32 data_020da13c[]; /* the base class's (Process) */

extern u8 data_021fba68[];
extern u8 data_021f8b48[];
extern void func_020bc514(void *object);

/* The flag Block020ba298_SetPlayerFlag32 sets. */
#define BLOCK_020BA298_PLAYER_FLAG 0x32

/* func_020ba298: the destructor. */
Process *Block020ba298_Destruct(Process *process)
{
    process->vtable = data_020e69a4;
    process->vtable = data_020da13c;
    Process_Destruct(process);
    return process;
}
CLEAN_AS(func_020ba298, Block020ba298_Destruct)

/* func_020ba2b8: the destructor, then the object freed. */
Process *Block020ba298_DestructFree(Process *process)
{
    process->vtable = data_020e69a4;
    process->vtable = data_020da13c;
    Process_Destruct(process);
    Heap_FreeAux(process);
    return process;
}
CLEAN_AS(func_020ba2b8, Block020ba298_DestructFree)

/* func_020ba2e0 */
void Block020ba298_SetByte9(void)
{
    data_021fba68[9] = 1;
}
CLEAN_AS(func_020ba2e0, Block020ba298_SetByte9)

/* func_020ba2ec: when there is a player at this console, its flag 0x32 set and func_020bc514
 * run on data_021f8b48. */
void Block020ba298_SetPlayerFlag32(void)
{
    u8 *record = PlayerRecords_Current();
    if (record != NULL) {
        PlayerRecord_SetFlag(record, BLOCK_020BA298_PLAYER_FLAG);
        func_020bc514(data_021f8b48);
    }
}
CLEAN_AS(func_020ba2ec, Block020ba298_SetPlayerFlag32)

/* The sky's process (vtable data_020e69a4; sky.h): the destructors above, its creation,
 * deletion, frame and drawing below. */

#include "line_handlers.h"
#include "sky.h"
#include "star_palette.h"
#include "state_flags.h"

static_assert(sizeof(SkyProcess) == 0x60, "the sky's process");

extern u8 data_021fba88[];
extern u8 data_021fbb08[];
extern u8 data_020e54a8;
extern u8 data_021fa6b4[]; /* 0x1b6c into data_021f8b48 */
extern const u16 data_021f6cc0;
extern StarPalette data_021f7280;
extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GXS_LoadBGPltt(const void *src, u32 offset, u32 size);
extern int func_020befa0(void *files);
extern void func_020bc4f8(void *objects);
extern void func_020bc4dc(void *objects);
extern void func_020bc388(void *objects);
extern void func_020bc380(void *objects);
extern void func_020bc1bc(void *objects);
extern void func_020bbe8c(void *sound);
extern void func_020bbe94(void *sound);
extern int func_020bbee0(void *sound);
extern void func_01ffceb8(void);
extern void func_020bad44(void);
extern void func_020bab04(void);
extern void func_020baad8(void);

/* func_020ba310 */
unsigned char Block020ba298_Byte10(void)
{
    return data_021fba88[0x10];
}
CLEAN_AS(func_020ba310, Block020ba298_Byte10)

/* func_020ba31c: byte 8 of data_021fbb08 set when `second`, else byte 7. */
void Block020ba298_SetByte7Or8(int second)
{
    if (second) {
        data_021fbb08[8] = 1;
    } else {
        data_021fbb08[7] = 1;
    }
}
CLEAN_AS(func_020ba31c, Block020ba298_SetByte7Or8)

/* func_020ba334 */
void Block020ba298_SetByte6(void)
{
    data_021fbb08[6] = 1;
}
CLEAN_AS(func_020ba334, Block020ba298_SetByte6)

/* func_020ba8d8 (vtable slot 3): the deletion: the line handler removed, both backdrops set
 * from data_021f6cc0, every buffer of the sky freed, the sky's objects and the stars' twinkling
 * stopped and the sound released; the line handler's answer. */
int SkyProcess_Delete(SkyProcess *process)
{
    Sky *sky = &data_021f75b0;
    int removed = LineHandlers_Remove(&data_021f6d2c);
    GX_LoadBGPltt(&data_021f6cc0, 0, 2);
    GXS_LoadBGPltt(&data_021f6cc0, 0, 2);

    if (sky->screen_data != NULL) {
        Heap_FreeCurrent(sky->screen_data);
    }
    sky->screen_data = NULL;
    if (sky->change_screen_data != NULL) {
        Heap_FreeCurrent(sky->change_screen_data);
    }
    sky->change_screen_data = NULL;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (sky->hour_colors[i][j] != NULL) {
                Heap_FreeCurrent(sky->hour_colors[i][j]);
            }
            sky->hour_colors[i][j] = NULL;
        }
    }
    for (int k = 0; k < 3; k++) {
        if (sky->palettes[k] != NULL) {
            Heap_FreeCurrent(sky->palettes[k]);
            sky->palettes[k] = NULL;
        }
    }

    if (data_021f6cd8 != 0) {
        func_020bc4dc(data_021f8b48);
    }
    StarPalette_Cancel(&data_021f7280);
    func_020bbe8c(&process->sound);
    return removed;
}
CLEAN_AS(func_020ba8d8, SkyProcess_Delete)

/* func_020ba9b4 (vtable slot 9): the drawing: the sky's objects drawn when the sky is. */
int SkyProcess_Draw(void)
{
    if (data_021f6cd8 != 0) {
        func_020bc1bc(data_021f8b48);
    }
    return 1;
}
CLEAN_AS(func_020ba9b4, SkyProcess_Draw)

/* func_020ba9d8 (vtable slot 6): a frame: when the sky is drawn the stars twinkle (unless state
 * flag 1 is set) and the objects run, else they run without it; the hour's weather; the
 * sound. */
int SkyProcess_Execute(SkyProcess *process)
{
    if (data_021f6cd8 != 0) {
        if (!StateFlags_Test1()) {
            StarPalette_Update(&data_021f7280);
        }
        func_020bc388(data_021f8b48);
    } else {
        func_020bc380(data_021f8b48);
    }
    Sky_UpdateHour(&data_021f75b0);
    func_020bbe94(&process->sound);
    return 1;
}
CLEAN_AS(func_020ba9d8, SkyProcess_Execute)

/* func_020baa28 (vtable slot 0): the creation. The sky is drawn when data_020e54a8 is 0: its
 * objects' files read, the sky shown on the sub screen, its objects started and its line
 * handler added (Sky_Frame each frame); otherwise only the colours are loaded and the handler
 * runs Sky_FrameHidden. The sound starts when the handler was added; its answer. */
int SkyProcess_Create(SkyProcess *process)
{
    int added = 0;
    data_021f6cd8 = data_020e54a8 == 0 ? 1 : 0;
    Sky_Reset(&data_021f75b0);

    if (data_021f6cd8 != 0) {
        if (func_020befa0(data_021fa6b4) && Sky_ShowOn(SKY_SCREEN_SUB)) {
            func_020bc4f8(data_021f8b48);
            added = LineHandlers_Add(&data_021f6d2c, (int) (uintptr_t) func_01ffceb8, (int) (uintptr_t) func_020bad44,
                                     (int) (uintptr_t) func_020bab04);
        }
    } else if (Sky_LoadColors(SKY_SCREEN_SUB)) {
        added = LineHandlers_Add(&data_021f6d2c, 0, 0, (int) (uintptr_t) func_020baad8);
    }

    if (added) {
        func_020bbee0(&process->sound);
    }
    return added;
}
CLEAN_AS(func_020baa28, SkyProcess_Create)
