/* The catchphrase of one of the town's villagers (villager_catchphrase.h). */
#include "villager_catchphrase.h"

#include "clean.h"
#include "text_string.h"
#include "villager_checks.h"

extern const char data_020e1968[]; /* "st_itchy" */

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern VillagerCatchphraseText *func_02082164(VillagerCatchphraseText *text); /* constructor */
extern VillagerCatchphraseText *func_0208214c(VillagerCatchphraseText *text); /* destructor */
/* Up to `count` (at most 4) of the text's characters copied to `dst`. */
extern void func_02082114(VillagerCatchphraseText *text, u16 *dst, int count);
/* The wide text set from `count` characters. */
extern void func_020a8874(VillagerCatchphraseText *text, const u16 *chars, int count);
/* The wide text set from an 8-bit text, and an 8-bit text from a wide one. */
extern int func_020a87e0(VillagerCatchphraseText *text, void *label);
extern int func_020a8a70(void *label, VillagerCatchphraseText *text, int a, int b);
extern void func_020a8c1c(void *label);                                /* an 8-bit text emptied */
extern int func_020b4a20(void *label, u8 *message, const char *group); /* a message of a group */
extern u32 func_020644cc(int bound);                                   /* a random number below `bound` */

static u16 *villager_catchphrase_of(u8 *villager)
{
    return (u16 *) (void *) (villager + VILLAGER_CATCHPHRASE);
}

/* func_02080a4c: the catchphrase emptied, then set from the first `count` characters (at most
 * four). */
void VillagerCatchphrase_Set(u8 *villager, const u16 *chars, int count)
{
    MI_CpuFill8(villager_catchphrase_of(villager), 0, VILLAGER_CATCHPHRASE_LENGTH * 2);
    if (count > VILLAGER_CATCHPHRASE_LENGTH) {
        count = VILLAGER_CATCHPHRASE_LENGTH;
    }
    MI_CpuCopy8(chars, villager_catchphrase_of(villager), (u32) count * 2);
}
CLEAN_AS(func_02080a4c, VillagerCatchphrase_Set)

/* func_02080a7c: the catchphrase set from the text's first four characters. */
void VillagerCatchphrase_SetFromText(u8 *villager, VillagerCatchphraseText *text)
{
    func_02082114(text, villager_catchphrase_of(villager), VILLAGER_CATCHPHRASE_LENGTH);
}
CLEAN_AS(func_02080a7c, VillagerCatchphrase_SetFromText)

/* func_02080a94: the catchphrase set from an 8-bit text. */
void VillagerCatchphrase_SetFromLabel(u8 *villager, void *label)
{
    VillagerCatchphraseText text;
    func_02082164(&text);
    TextString_ClearWide((TextObject *) (void *) &text);
    func_020a87e0(&text, label);
    VillagerCatchphrase_SetFromText(villager, &text);
    func_0208214c(&text);
}
CLEAN_AS(func_02080a94, VillagerCatchphrase_SetFromLabel)

/* func_02080ac8: the text cleared and set to the catchphrase. */
void VillagerCatchphrase_ToText(u8 *villager, VillagerCatchphraseText *text)
{
    TextString_ClearWide((TextObject *) (void *) text);
    func_020a8874(text, villager_catchphrase_of(villager), VILLAGER_CATCHPHRASE_LENGTH);
}
CLEAN_AS(func_02080ac8, VillagerCatchphrase_ToText)

/* func_02080af0: the 8-bit text emptied and set to what the villager says as its catchphrase:
 * with `itchy` and the villager the state table names at 0x160 (VillagerCheck_IsIndex160), a
 * random one of the lines of "st_itchy"; else its catchphrase. */
void VillagerCatchphrase_ToLabel(u8 *villager, void *label, int itchy)
{
    VillagerCatchphraseText text;
    func_02082164(&text);
    func_020a8c1c(label);
    if (itchy != 0 && VillagerCheck_IsIndex160(villager)) {
        u8 line = (u8) func_020644cc(VILLAGER_CATCHPHRASE_ITCHY_LINES);
        func_020b4a20(label, &line, data_020e1968);
    } else {
        VillagerCatchphrase_ToText(villager, &text);
        func_020a8a70(label, &text, 0, 0);
    }
    func_0208214c(&text);
}
CLEAN_AS(func_02080af0, VillagerCatchphrase_ToLabel)

/* func_02080b50: the catchphrase cleared. */
void VillagerCatchphrase_Clear(u8 *villager)
{
    MI_CpuFill8(villager_catchphrase_of(villager), 0, VILLAGER_CATCHPHRASE_LENGTH * 2);
}
CLEAN_AS(func_02080b50, VillagerCatchphrase_Clear)
