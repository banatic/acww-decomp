/* The catchphrase of one of the town's villagers (villager_catchphrase.h). */
#include "villager_catchphrase.h"

#include "clean.h"
#include "text_string.h"
#include "villager_checks.h"
#include "main_random.h"
#include "message_reader.h"
#include "small_texts.h"
#include "text_base.h"

extern const char data_020e1968[]; /* "st_itchy" */

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

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
    CatchphraseWide_CopyOut((CatchphraseWide *) text, villager_catchphrase_of(villager), VILLAGER_CATCHPHRASE_LENGTH);
}
CLEAN_AS(func_02080a7c, VillagerCatchphrase_SetFromText)

/* func_02080a94: the catchphrase set from an 8-bit text. */
void VillagerCatchphrase_SetFromLabel(u8 *villager, void *label)
{
    VillagerCatchphraseText text;
    CatchphraseWide_Construct((CatchphraseWide *) &text);
    TextString_ClearWide((TextObject *) (void *) &text);
    TextBase_BytesToWide((WideTextBase *) &text, label);
    VillagerCatchphrase_SetFromText(villager, &text);
    CatchphraseWide_Destruct((CatchphraseWide *) &text);
}
CLEAN_AS(func_02080a94, VillagerCatchphrase_SetFromLabel)

/* func_02080ac8: the text cleared and set to the catchphrase. */
void VillagerCatchphrase_ToText(u8 *villager, VillagerCatchphraseText *text)
{
    TextString_ClearWide((TextObject *) (void *) text);
    TextBase_SetWide(text, villager_catchphrase_of(villager), VILLAGER_CATCHPHRASE_LENGTH);
}
CLEAN_AS(func_02080ac8, VillagerCatchphrase_ToText)

/* func_02080af0: the 8-bit text emptied and set to what the villager says as its catchphrase:
 * with `itchy` and the villager the state table names at 0x160 (VillagerCheck_IsIndex160), a
 * random one of the lines of "st_itchy"; else its catchphrase. */
void VillagerCatchphrase_ToLabel(u8 *villager, void *label, int itchy)
{
    VillagerCatchphraseText text;
    CatchphraseWide_Construct((CatchphraseWide *) &text);
    TextBase_Clear(label);
    if (itchy != 0 && VillagerCheck_IsIndex160(villager)) {
        u8 line = (u8) MainRandom_Below(VILLAGER_CATCHPHRASE_ITCHY_LINES);
        MessageReader_LoadMessage((int) (uintptr_t) label, &line, (int) (uintptr_t) data_020e1968);
    } else {
        VillagerCatchphrase_ToText(villager, &text);
        TextBase_WideToBytes(label, (WideTextBase *) &text, 0, 0);
    }
    CatchphraseWide_Destruct((CatchphraseWide *) &text);
}
CLEAN_AS(func_02080af0, VillagerCatchphrase_ToLabel)

/* func_02080b50: the catchphrase cleared. */
void VillagerCatchphrase_Clear(u8 *villager)
{
    MI_CpuFill8(villager_catchphrase_of(villager), 0, VILLAGER_CATCHPHRASE_LENGTH * 2);
}
CLEAN_AS(func_02080b50, VillagerCatchphrase_Clear)
