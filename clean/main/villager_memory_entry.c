/* The parts of one memory a villager keeps of a player (villager_memory_entry.h). */
#include "villager_memory_entry.h"

#include <string.h>

#include "clean.h"
#include "date_time.h"
#include "text_string.h"
#include "main_random.h"
#include "player_id.h"
#include "small_texts.h"
#include "text_base.h"
#include "town_name.h"

/* Where the parts villager_memories.h leaves unnamed are. */
#define VILLAGER_MEMORY_DRAWN 0x70
#define VILLAGER_MEMORY_VALUES 0x74
#define VILLAGER_MEMORY_VALUES_SIZE 8
/* How many numbers VillagerMemoryEntry_DrawUnused draws from. */
#define VILLAGER_MEMORY_DRAW_COUNT 32

#define NO_ITEM 0xfff1 /* an empty item */

/* A text of six wide characters (func_02094f7c builds it, vtable data_020e2f54; 0x1c bytes),
 * as long as what the villager calls the player. */
typedef struct VillagerMemoryNicknameText {
    u32 words[7];
} VillagerMemoryNicknameText;

extern const NpcIdHead data_021dc7aa; /* this town (number and name) */
extern const u8 data_021f3b68[];      /* type 12's values, packed (player_messages.h) */

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

static u8 *memory_at(VillagerMemory *memory, int offset)
{
    return (u8 *) memory + offset;
}

static int has_flag(const VillagerMemory *memory, u16 flag)
{
    return (memory->flags & flag) != 0;
}

static void set_flag(VillagerMemory *memory, u16 flag)
{
    memory->flags |= flag;
}

static void clear_flag(VillagerMemory *memory, u16 flag)
{
    memory->flags &= (u16) ~flag;
}

static int days_in_row(const VillagerMemory *memory)
{
    return (memory->flags & VILLAGER_MEMORY_DAYS_MASK) >> VILLAGER_MEMORY_DAYS_SHIFT;
}

/* ---- Flags */

/* func_02081988 */
int VillagerMemoryEntry_Bit7(VillagerMemory *memory)
{
    return has_flag(memory, VILLAGER_MEMORY_BIT_7);
}
CLEAN_AS(func_02081988, VillagerMemoryEntry_Bit7)

/* func_0208199c */
void VillagerMemoryEntry_ClearBit7(VillagerMemory *memory)
{
    clear_flag(memory, VILLAGER_MEMORY_BIT_7);
}
CLEAN_AS(func_0208199c, VillagerMemoryEntry_ClearBit7)

/* func_020819ac */
void VillagerMemoryEntry_SetBit7(VillagerMemory *memory)
{
    set_flag(memory, VILLAGER_MEMORY_BIT_7);
}
CLEAN_AS(func_020819ac, VillagerMemoryEntry_SetBit7)

/* func_020819bc */
int VillagerMemoryEntry_Bit6(VillagerMemory *memory)
{
    return has_flag(memory, VILLAGER_MEMORY_BIT_6);
}
CLEAN_AS(func_020819bc, VillagerMemoryEntry_Bit6)

/* func_020819d0 */
void VillagerMemoryEntry_ClearBit6(VillagerMemory *memory)
{
    clear_flag(memory, VILLAGER_MEMORY_BIT_6);
}
CLEAN_AS(func_020819d0, VillagerMemoryEntry_ClearBit6)

/* func_020819e0 */
void VillagerMemoryEntry_SetBit6(VillagerMemory *memory)
{
    set_flag(memory, VILLAGER_MEMORY_BIT_6);
}
CLEAN_AS(func_020819e0, VillagerMemoryEntry_SetBit6)

/* func_020819f0 */
int VillagerMemoryEntry_Bit4(VillagerMemory *memory)
{
    return has_flag(memory, VILLAGER_MEMORY_BIT_4);
}
CLEAN_AS(func_020819f0, VillagerMemoryEntry_Bit4)

/* func_02081a04 */
void VillagerMemoryEntry_SetBit4(VillagerMemory *memory)
{
    set_flag(memory, VILLAGER_MEMORY_BIT_4);
}
CLEAN_AS(func_02081a04, VillagerMemoryEntry_SetBit4)

/* func_02081a14: one of the numbers 0-31 not drawn yet for this player, at random, marked as
 * drawn; once the last one is drawn all start over. A word with all 32 marked (which this never
 * leaves) also starts over. */
int VillagerMemoryEntry_DrawUnused(VillagerMemory *memory)
{
    u32 *drawn = (u32 *) (void *) memory_at(memory, VILLAGER_MEMORY_DRAWN);
    if (*drawn == 0xffffffffu) {
        *drawn = 0;
    }
    int left = 0;
    for (int i = 0; i < VILLAGER_MEMORY_DRAW_COUNT; i++) {
        if (((*drawn >> i) & 1) == 0) {
            left++;
        }
    }
    int skip = MainRandom_Below(left);
    int pick = 0;
    for (int i = 0; i < VILLAGER_MEMORY_DRAW_COUNT; i++) {
        if (((*drawn >> i) & 1) == 0) {
            if (skip == 0) {
                pick = i;
                break;
            }
            skip--;
        }
    }
    if (left == 1) {
        *drawn = 0;
    }
    *drawn |= 1u << pick;
    return pick;
}
CLEAN_AS(func_02081a14, VillagerMemoryEntry_DrawUnused)

/* func_02081a80 */
void VillagerMemoryEntry_SetImpression(VillagerMemory *memory, u8 impression)
{
    memory->byte_6d = impression;
}
CLEAN_AS(func_02081a80, VillagerMemoryEntry_SetImpression)

/* func_02081a88: the villager's impression of the player (villager_impression.h). */
u8 VillagerMemoryEntry_Impression(VillagerMemory *memory)
{
    return memory->byte_6d;
}
CLEAN_AS(func_02081a88, VillagerMemoryEntry_Impression)

/* func_02081a90: the 8 bytes at 0x74 copied from `values`, and marked set. */
void VillagerMemoryEntry_SetValues(VillagerMemory *memory, const void *values)
{
    set_flag(memory, VILLAGER_MEMORY_VALUES_SET);
    memcpy(memory_at(memory, VILLAGER_MEMORY_VALUES), values, VILLAGER_MEMORY_VALUES_SIZE);
}
CLEAN_AS(func_02081a90, VillagerMemoryEntry_SetValues)

/* func_02081aa8 */
int VillagerMemoryEntry_ValuesSet(VillagerMemory *memory)
{
    return has_flag(memory, VILLAGER_MEMORY_VALUES_SET);
}
CLEAN_AS(func_02081aa8, VillagerMemoryEntry_ValuesSet)

/* ---- The item */

/* func_02081abc: the address of the item (0x6a). */
int VillagerMemoryEntry_Item(VillagerMemory *memory)
{
    return (int) (uintptr_t) &memory->item;
}
CLEAN_AS(func_02081abc, VillagerMemoryEntry_Item)

/* func_02081ac0 */
void VillagerMemoryEntry_SetItem(VillagerMemory *memory, const u16 *item)
{
    memory->item = *item;
}
CLEAN_AS(func_02081ac0, VillagerMemoryEntry_SetItem)

/* ---- The two texts of 10 characters */

/* func_02081ac8: the text at 0x3e emptied, then set from up to 10 characters, and marked set.
 * REQUIRES: length >= 0; the game copies (length * 2) bytes taken as unsigned otherwise. */
void VillagerMemoryEntry_SetText3E(VillagerMemory *memory, const u16 *text, int length)
{
    MI_CpuFill8(memory->text_3e, 0, sizeof(memory->text_3e));
    if (length > VILLAGER_MEMORY_TEXT_LENGTH) {
        length = VILLAGER_MEMORY_TEXT_LENGTH;
    }
    MI_CpuCopy8(text, memory->text_3e, (u32) length * 2);
    set_flag(memory, VILLAGER_MEMORY_TEXT_3E_SET);
}
CLEAN_AS(func_02081ac8, VillagerMemoryEntry_SetText3E)

/* func_02081b00: the wide text emptied, then set from the 10 characters at 0x3e. */
void VillagerMemoryEntry_Text3EToWide(VillagerMemory *memory, void *wide)
{
    TextString_ClearWide((TextObject *) wide);
    TextBase_SetWide(wide, memory->text_3e, VILLAGER_MEMORY_TEXT_LENGTH);
}
CLEAN_AS(func_02081b00, VillagerMemoryEntry_Text3EToWide)

/* func_02081b24: the text at 0x3e converted to 8 bits into the label. */
void VillagerMemoryEntry_Text3EToLabel(VillagerMemory *memory, void *label)
{
    VillagerMemoryWide wide;
    VillagerMemoryWide_Construct(&wide);
    VillagerMemoryEntry_Text3EToWide(memory, &wide);
    TextBase_WideToBytes(label, (WideTextBase *) &wide, 0, 0);
    VillagerMemoryWide_Destruct(&wide);
}
CLEAN_AS(func_02081b24, VillagerMemoryEntry_Text3EToLabel)

/* func_02081b54 */
int VillagerMemoryEntry_Text3ESet(VillagerMemory *memory)
{
    return has_flag(memory, VILLAGER_MEMORY_TEXT_3E_SET);
}
CLEAN_AS(func_02081b54, VillagerMemoryEntry_Text3ESet)

/* func_02081b68: the text at 0x2a emptied, then set from up to 10 characters, and marked set.
 * REQUIRES: length >= 0, as for VillagerMemoryEntry_SetText3E. */
void VillagerMemoryEntry_SetText2A(VillagerMemory *memory, const u16 *text, int length)
{
    MI_CpuFill8(memory->text_2a, 0, sizeof(memory->text_2a));
    if (length > VILLAGER_MEMORY_TEXT_LENGTH) {
        length = VILLAGER_MEMORY_TEXT_LENGTH;
    }
    MI_CpuCopy8(text, memory->text_2a, (u32) length * 2);
    set_flag(memory, VILLAGER_MEMORY_TEXT_2A_SET);
}
CLEAN_AS(func_02081b68, VillagerMemoryEntry_SetText2A)

/* func_02081ba0: the wide text emptied, then set from the 10 characters at 0x2a. */
void VillagerMemoryEntry_Text2AToWide(VillagerMemory *memory, void *wide)
{
    TextString_ClearWide((TextObject *) wide);
    TextBase_SetWide(wide, memory->text_2a, VILLAGER_MEMORY_TEXT_LENGTH);
}
CLEAN_AS(func_02081ba0, VillagerMemoryEntry_Text2AToWide)

/* func_02081bc4: the text at 0x2a converted to 8 bits into the label; gives what the wide
 * text's destructor gives (the wide text's address).
 * QUIRK: the wide text is set from the characters twice; it is a different class (vtable
 * data_020e194c) from the one VillagerMemoryEntry_Text3EToLabel uses, of the same size. */
void *VillagerMemoryEntry_Text2AToLabel(VillagerMemory *memory, void *label)
{
    VillagerMemoryWide wide;
    Wide10Text_Construct((Wide10Text *) &wide);
    VillagerMemoryEntry_Text2AToWide(memory, &wide);
    TextBase_SetWide(&wide, memory->text_2a, VILLAGER_MEMORY_TEXT_LENGTH);
    TextBase_WideToBytes(label, (WideTextBase *) &wide, 0, 0);
    return Wide10Text_Destruct((Wide10Text *) &wide);
}
CLEAN_AS(func_02081bc4, VillagerMemoryEntry_Text2AToLabel)

/* func_02081c00 */
int VillagerMemoryEntry_Text2ASet(VillagerMemory *memory)
{
    return has_flag(memory, VILLAGER_MEMORY_TEXT_2A_SET);
}
CLEAN_AS(func_02081c00, VillagerMemoryEntry_Text2ASet)

/* ---- What the villager calls the player */

/* func_02081c14: emptied, then set from up to 6 characters.
 * REQUIRES: length >= 0, as for VillagerMemoryEntry_SetText3E. */
void VillagerMemoryEntry_SetNicknameChars(VillagerMemory *memory, const u16 *chars, int length)
{
    MI_CpuFill8(memory->nickname, 0, sizeof(memory->nickname));
    if (length > VILLAGER_MEMORY_NICKNAME_LENGTH) {
        length = VILLAGER_MEMORY_NICKNAME_LENGTH;
    }
    MI_CpuCopy8(chars, memory->nickname, (u32) length * 2);
}
CLEAN_AS(func_02081c14, VillagerMemoryEntry_SetNicknameChars)

/* func_02081c40: set from the label, converted to 16 bits; gives what the text's destructor
 * gives (its address). */
void *VillagerMemoryEntry_SetNickname(VillagerMemory *memory, void *label)
{
    VillagerMemoryNicknameText text;
    PlayerIdWideText_Construct((PlayerIdWideText *) &text);
    TextBase_BytesToWide((WideTextBase *) &text, label);
    PlayerIdWideText_CopyOut((PlayerIdWideText *) &text, memory->nickname, VILLAGER_MEMORY_NICKNAME_LENGTH);
    return PlayerIdWideText_Destruct((PlayerIdWideText *) &text);
}
CLEAN_AS(func_02081c40, VillagerMemoryEntry_SetNickname)

/* func_02081c70: the wide text emptied, then set from the 6 characters. */
void VillagerMemoryEntry_NicknameToWide(VillagerMemory *memory, void *wide)
{
    TextString_ClearWide((TextObject *) wide);
    TextBase_SetWide(wide, memory->nickname, VILLAGER_MEMORY_NICKNAME_LENGTH);
}
CLEAN_AS(func_02081c70, VillagerMemoryEntry_NicknameToWide)

/* func_02081c94: converted to 8 bits into the label. */
void VillagerMemoryEntry_NicknameToLabel(VillagerMemory *memory, void *label)
{
    VillagerMemoryNicknameText text;
    PlayerIdWideText_Construct((PlayerIdWideText *) &text);
    VillagerMemoryEntry_NicknameToWide(memory, &text);
    TextBase_WideToBytes(label, (WideTextBase *) &text, 0, 0);
    PlayerIdWideText_Destruct((PlayerIdWideText *) &text);
}
CLEAN_AS(func_02081c94, VillagerMemoryEntry_NicknameToLabel)

/* ---- The letter held, and how fond the villager is */

/* func_02081cc4 */
void VillagerMemoryEntry_SetLetterHeld(VillagerMemory *memory)
{
    set_flag(memory, VILLAGER_MEMORY_LETTER_HELD);
}
CLEAN_AS(func_02081cc4, VillagerMemoryEntry_SetLetterHeld)

/* func_02081cd8 */
int VillagerMemoryEntry_LetterHeld(VillagerMemory *memory)
{
    return has_flag(memory, VILLAGER_MEMORY_LETTER_HELD);
}
CLEAN_AS(func_02081cd8, VillagerMemoryEntry_LetterHeld)

/* func_02081cec: the fondness moved by `delta`, kept within -128 to 127; gives the new one. */
s8 VillagerMemoryEntry_ChangeFondness(VillagerMemory *memory, int delta)
{
    int fondness = memory->fondness + delta;
    if (fondness > INT8_MAX) {
        fondness = INT8_MAX;
    } else if (fondness < INT8_MIN) {
        fondness = INT8_MIN;
    }
    VillagerMemoryEntry_SetFondness(memory, (u8) (s8) fondness);
    return (s8) fondness;
}
CLEAN_AS(func_02081cec, VillagerMemoryEntry_ChangeFondness)

/* func_02081d18 */
void VillagerMemoryEntry_SetFondness(VillagerMemory *memory, u8 fondness)
{
    memory->fondness = (s8) fondness;
}
CLEAN_AS(func_02081d18, VillagerMemoryEntry_SetFondness)

/* func_02081d20 */
int VillagerMemoryEntry_Fondness(VillagerMemory *memory)
{
    return memory->fondness;
}
CLEAN_AS(func_02081d20, VillagerMemoryEntry_Fondness)

/* ---- The player, the town and the date */

/* func_02081d28: whether the memory's player is `player`: the same town (number and name),
 * then the same player number and name. */
int VillagerMemoryEntry_IsPlayer(const VillagerMemory *memory, const DesignCreator *player)
{
    if (memory->player.town_id != player->town_id) {
        return 0;
    }
    if (memcmp(memory->player.town_name, player->town_name, sizeof(player->town_name)) != 0) {
        return 0;
    }
    return PlayerId_SamePlayer(&memory->player, player) != 0;
}
CLEAN_AS(func_02081d28, VillagerMemoryEntry_IsPlayer)

/* func_02081d60 */
DesignCreator *VillagerMemoryEntry_Player(VillagerMemory *memory)
{
    return &memory->player;
}
CLEAN_AS(func_02081d60, VillagerMemoryEntry_Player)

/* func_02081d64: the address of the town (0x5c). */
int VillagerMemoryEntry_Town(VillagerMemory *memory)
{
    return (int) (uintptr_t) &memory->town;
}
CLEAN_AS(func_02081d64, VillagerMemoryEntry_Town)

/* func_02081d68: the villager grows fonder of the player by one more than the days in a row it
 * has met the player (at most 4); gives the new fondness. */
int VillagerMemoryEntry_RaiseFondness(VillagerMemory *memory)
{
    int days = days_in_row(memory);
    if (days > VILLAGER_MEMORY_DAYS_MAX) {
        days = VILLAGER_MEMORY_DAYS_MAX;
    }
    return VillagerMemoryEntry_ChangeFondness(memory, (s8) (days + 1));
}
CLEAN_AS(func_02081d68, VillagerMemoryEntry_RaiseFondness)

/* func_02081d88: the days in a row counted for a meeting at `now`: kept when the last meeting
 * was the same day, one more when it was the day before, else (no valid last date, a last date
 * not before `now`, or a gap) back to 0; at most 4. Gives 1 for a meeting on a new day, 0 for
 * one on the same day. */
int VillagerMemoryEntry_CountDays(VillagerMemory *memory, const DateTime *now)
{
    const DateTime *last = (const DateTime *) (uintptr_t) VillagerMemoryEntry_When(memory);
    int days = 0;
    int new_day = 1;

    if (DateTime_IsInvalid(last) == 0 && DateTime_Compare(now, last,
                                                          DATE_TIME_YEAR | DATE_TIME_MONTH | DATE_TIME_DAY | DATE_TIME_HOUR |
                                                              DATE_TIME_MINUTE | DATE_TIME_SECOND) == 1) {
        int apart = DateTime_DaysBetween(last, now);
        if (apart == 0) {
            days = days_in_row(memory);
            new_day = 0;
        } else if (apart == 1) {
            days = days_in_row(memory) + 1;
        }
    }
    if (days > VILLAGER_MEMORY_DAYS_MAX) {
        days = VILLAGER_MEMORY_DAYS_MAX;
    }
    memory->flags = (u16) ((memory->flags & ~VILLAGER_MEMORY_DAYS_MASK) | (days << VILLAGER_MEMORY_DAYS_SHIFT));
    return new_day;
}
CLEAN_AS(func_02081d88, VillagerMemoryEntry_CountDays)

/* func_02081e10: the address of the date of the last meeting (0x54). */
int VillagerMemoryEntry_When(VillagerMemory *memory)
{
    return (int) (uintptr_t) &memory->when;
}
CLEAN_AS(func_02081e10, VillagerMemoryEntry_When)

/* func_02081e14: the memory updated for a meeting: the player copied in when given and set;
 * the days in a row counted, and on a new day the villager grows fonder; then the town (this
 * town when NULL) and the date (the clock's when NULL) kept, and type 12's values. */
void VillagerMemoryEntry_Update(VillagerMemory *memory, const DesignCreator *player, const NpcIdHead *town,
                                const DateTime *now)
{
    DateTime clock = {0};

    if (player != NULL && PlayerId_IsSet((DesignCreator *) player)) {
        PlayerId_Copy(&memory->player, player);
    }
    if (town == NULL) {
        town = &data_021dc7aa;
    }
    if (now == NULL) {
        DateTime_Now(&clock);
        now = &clock;
    }
    if (VillagerMemoryEntry_CountDays(memory, now)) {
        VillagerMemoryEntry_RaiseFondness(memory);
    }
    TownName_Copy((TownName *) ((NpcIdHead *) (uintptr_t) VillagerMemoryEntry_Town(memory)), (const TownName *) town);
    MI_CpuCopy8(now, (void *) (uintptr_t) VillagerMemoryEntry_When(memory), sizeof(DateTime));
    VillagerMemoryEntry_SetValues(memory, data_021f3b68);
}
CLEAN_AS(func_02081e14, VillagerMemoryEntry_Update)

/* func_02081e94: the memory taken for the player, when it is set: emptied, updated for a
 * meeting, and the villager calls the player by its name. Gives whether it was taken. */
int VillagerMemoryEntry_Take(VillagerMemory *memory, const DesignCreator *player, const NpcIdHead *town, const DateTime *now)
{
    if (!PlayerId_IsSet((DesignCreator *) player)) {
        return 0;
    }
    VillagerMemoryEntry_Clear(memory);
    VillagerMemoryEntry_Update(memory, player, town, now);
    MI_CpuCopy8((const void *) (uintptr_t) PlayerId_Name((int) (uintptr_t) player), memory->nickname,
                sizeof(memory->nickname));
    return 1;
}
CLEAN_AS(func_02081e94, VillagerMemoryEntry_Take)

/* func_02081edc: whether the memory is in use (its player is set). */
int VillagerMemoryEntry_InUse(VillagerMemory *memory)
{
    return PlayerId_IsSet(VillagerMemoryEntry_Player(memory));
}
CLEAN_AS(func_02081edc, VillagerMemoryEntry_InUse)

/* ---- Construction */

/* func_02081ef0: every byte 0, the player emptied, the date 0 and no item. */
void VillagerMemoryEntry_Clear(VillagerMemory *memory)
{
    MI_CpuFill8(memory, 0, sizeof(*memory));
    PlayerId_Clear(&memory->player);
    memset(&memory->when, 0, sizeof(memory->when));
    memory->item = NO_ITEM;
}
CLEAN_AS(func_02081ef0, VillagerMemoryEntry_Clear)

/* func_02081f18: the destructor, the town then the player. */
VillagerMemory *VillagerMemoryEntry_Destruct(VillagerMemory *memory)
{
    TownName_Destruct(&memory->town);
    PlayerId_Destruct(&memory->player);
    return memory;
}
CLEAN_AS(func_02081f18, VillagerMemoryEntry_Destruct)

/* func_02081f30: the constructor, then emptied. */
VillagerMemory *VillagerMemoryEntry_Construct(VillagerMemory *memory)
{
    PlayerId_Construct(&memory->player);
    memset(&memory->when, 0, sizeof(memory->when));
    TownName_Construct(&memory->town);
    memory->item = NO_ITEM;
    VillagerMemoryEntry_Clear(memory);
    return memory;
}
CLEAN_AS(func_02081f30, VillagerMemoryEntry_Construct)
