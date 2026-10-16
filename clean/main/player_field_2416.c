/* A player record's object at 0x2416 (player_field_2416.h). */
#include "player_field_2416.h"

#include "calendar.h"
#include "clean.h"

static_assert(offsetof(PlayerField2416, byte_08) == 0x08 && offsetof(PlayerField2416, count_0e) == 0x0e, "field 2416");
static_assert(sizeof(PlayerField2416) == PLAYER_FIELD_2416_SIZE, "field 2416");
static_assert(offsetof(PlayerField2416, date_04) == 0x04 && offsetof(PlayerField2416, count_0d) == 0x0d, "field 2416");

/* func_02088a60: the claims count raised by one.
 * BUG: the cap at 255 is tested after the byte was raised, so 255 wraps to 0.
 * BUGFIX: test before raising. */
void PlayerField2416_RaiseClaims(PlayerField2416 *field)
{
#ifdef BUGFIX
    if (field->claims < PLAYER_FIELD_2416_CLAIMS_MAX) {
        field->claims++;
    }
#else
    field->claims = (u8) (field->claims + 1);
#endif
}
CLEAN_AS(func_02088a60, PlayerField2416_RaiseClaims)

/* func_02088a74 */
int PlayerField2416_Claims(PlayerField2416 *field)
{
    return field->claims;
}
CLEAN_AS(func_02088a74, PlayerField2416_Claims)

/* func_02088a78: the date becomes today. */
void PlayerField2416_SetToday(PlayerField2416 *field)
{
    Date today;
    Calendar_Today(&today);
    field->year = today.year;
    field->month = today.month;
    field->day = today.day;
}
CLEAN_AS(func_02088a78, PlayerField2416_SetToday)

/* func_02088a9c: the date (the object itself). */
PlayerField2416 *PlayerField2416_Date(PlayerField2416 *field)
{
    return field;
}
CLEAN_AS(func_02088a9c, PlayerField2416_Date)

/* func_02088aa0 */
void PlayerField2416_ClearGardening(PlayerField2416 *field)
{
    field->flags &= (u8) ~PLAYER_FIELD_2416_GARDENING;
}
CLEAN_AS(func_02088aa0, PlayerField2416_ClearGardening)

/* func_02088aac */
void PlayerField2416_SetGardening(PlayerField2416 *field)
{
    field->flags |= PLAYER_FIELD_2416_GARDENING;
}
CLEAN_AS(func_02088aac, PlayerField2416_SetGardening)

/* func_02088ab8 */
int PlayerField2416_Gardening(PlayerField2416 *field)
{
    return (field->flags & PLAYER_FIELD_2416_GARDENING) != 0;
}
CLEAN_AS(func_02088ab8, PlayerField2416_Gardening)

/* func_02088ac0: bytes 0x0b and 0x0c cleared. */
void PlayerField2416_ClearBytes0B(PlayerField2416 *field)
{
    field->byte_0b = 0;
    field->byte_0c = 0;
}
CLEAN_AS(func_02088ac0, PlayerField2416_ClearBytes0B)

/* func_02088ac8: the tally in bits 2-5 cleared. */
void PlayerField2416_ClearTally(PlayerField2416 *field)
{
    field->flags &= (u8) ~PLAYER_FIELD_2416_TALLY_MASK;
}
CLEAN_AS(func_02088ac8, PlayerField2416_ClearTally)

/* func_02088ad4: the tally raised by one, up to 10.
 * QUIRK: it is raised within its four bits before the cap is tested, so 15 (never reached)
 * would wrap to 0. */
void PlayerField2416_RaiseTally(PlayerField2416 *field)
{
    u32 tally = (((field->flags & PLAYER_FIELD_2416_TALLY_MASK) >> PLAYER_FIELD_2416_TALLY_SHIFT) + 1) & 0xf;
    if (tally > PLAYER_FIELD_2416_TALLY_MAX) {
        tally = PLAYER_FIELD_2416_TALLY_MAX;
    }
    field->flags = (u8) ((field->flags & ~PLAYER_FIELD_2416_TALLY_MASK) | (tally << PLAYER_FIELD_2416_TALLY_SHIFT));
}
CLEAN_AS(func_02088ad4, PlayerField2416_RaiseTally)

/* func_02088b14 */
int PlayerField2416_Tally(PlayerField2416 *field)
{
    return (field->flags & PLAYER_FIELD_2416_TALLY_MASK) >> PLAYER_FIELD_2416_TALLY_SHIFT;
}
CLEAN_AS(func_02088b14, PlayerField2416_Tally)

/* func_02088b1c: the insect contest's flag from bit 0 of `entered`. */
void PlayerField2416_SetInsects(PlayerField2416 *field, u32 entered)
{
    field->flags = (u8) ((field->flags & ~PLAYER_FIELD_2416_INSECTS) | ((entered & 1) << 1));
}
CLEAN_AS(func_02088b1c, PlayerField2416_SetInsects)

/* func_02088b30 */
int PlayerField2416_Insects(PlayerField2416 *field)
{
    return (field->flags & PLAYER_FIELD_2416_INSECTS) != 0;
}
CLEAN_AS(func_02088b30, PlayerField2416_Insects)

/* func_02088b38: the fishing tourney's flag from bit 0 of `entered`. */
void PlayerField2416_SetFishing(PlayerField2416 *field, int entered)
{
    field->flags = (u8) ((field->flags & ~PLAYER_FIELD_2416_FISHING) | (entered & 1));
}
CLEAN_AS(func_02088b38, PlayerField2416_SetFishing)

/* func_02088b48 */
int PlayerField2416_Fishing(PlayerField2416 *field)
{
    return (field->flags & PLAYER_FIELD_2416_FISHING) != 0;
}
CLEAN_AS(func_02088b48, PlayerField2416_Fishing)

/* func_02088b50: `amount` added to the count at 0x0e, up to 100.
 * QUIRK: the sum is kept in the byte before the cap is tested, so a sum past 255 wraps and
 * stays under the cap. */
void PlayerField2416_AddCount0E(PlayerField2416 *field, u8 amount)
{
    u8 count = (u8) (field->count_0e + amount);
    if (count > PLAYER_FIELD_2416_COUNT_0E_MAX) {
        count = PLAYER_FIELD_2416_COUNT_0E_MAX;
    }
    field->count_0e = count;
}
CLEAN_AS(func_02088b50, PlayerField2416_AddCount0E)

/* func_02088b64 */
int PlayerField2416_Count0E(PlayerField2416 *field)
{
    return field->count_0e;
}
CLEAN_AS(func_02088b64, PlayerField2416_Count0E)

/* func_02088b68: the count at 0x0d raised by one, up to 6.
 * QUIRK: it is raised within its byte before the cap is tested, so 255 would wrap to 0. */
void PlayerField2416_RaiseCount0D(PlayerField2416 *field)
{
    u8 count = (u8) (field->count_0d + 1);
    if (count > PLAYER_FIELD_2416_COUNT_0D_MAX) {
        count = PLAYER_FIELD_2416_COUNT_0D_MAX;
    }
    field->count_0d = count;
}
CLEAN_AS(func_02088b68, PlayerField2416_RaiseCount0D)

/* func_02088b7c */
int PlayerField2416_Count0D(PlayerField2416 *field)
{
    return field->count_0d;
}
CLEAN_AS(func_02088b7c, PlayerField2416_Count0D)

/* func_02088b80: the level raised by one, up to 12.
 * QUIRK: it is raised within its byte before the cap is tested, so 255 would wrap to 0. */
void PlayerField2416_RaiseLevel(PlayerField2416 *field)
{
    u8 level = (u8) (field->byte_0c + 1);
    if (level > PLAYER_FIELD_2416_LEVEL_MAX) {
        level = PLAYER_FIELD_2416_LEVEL_MAX;
    }
    field->byte_0c = level;
}
CLEAN_AS(func_02088b80, PlayerField2416_RaiseLevel)

/* func_02088b94 */
int PlayerField2416_Level(PlayerField2416 *field)
{
    return field->byte_0c;
}
CLEAN_AS(func_02088b94, PlayerField2416_Level)

/* func_02088b98: `amount` points added, up to 255.
 * QUIRK: only the top is capped; a negative sum is kept in the byte as its low 8 bits. */
void PlayerField2416_AddPoints(PlayerField2416 *field, int amount)
{
    int points = field->byte_0b + amount;
    if (points > PLAYER_FIELD_2416_POINTS_MAX) {
        points = PLAYER_FIELD_2416_POINTS_MAX;
    }
    field->byte_0b = (u8) points;
}
CLEAN_AS(func_02088b98, PlayerField2416_AddPoints)

/* func_02088ba8 */
int PlayerField2416_Points(PlayerField2416 *field)
{
    return field->byte_0b;
}
CLEAN_AS(func_02088ba8, PlayerField2416_Points)

/* func_02088bac: `amount` added to the count at 0x0a, up to 16.
 * QUIRK: the sum is kept in the byte before the cap is tested, so a sum past 255 wraps and
 * stays under the cap. */
void PlayerField2416_AddCount0A(PlayerField2416 *field, int amount)
{
    u8 count = (u8) (field->count_0a + amount);
    if (count > PLAYER_FIELD_2416_COUNT_0A_MAX) {
        count = PLAYER_FIELD_2416_COUNT_0A_MAX;
    }
    field->count_0a = count;
}
CLEAN_AS(func_02088bac, PlayerField2416_AddCount0A)

/* func_02088bc0 */
int PlayerField2416_Count0A(PlayerField2416 *field)
{
    return field->count_0a;
}
CLEAN_AS(func_02088bc0, PlayerField2416_Count0A)

/* func_02088bc4: the count at 0x09 set, up to 15. */
void PlayerField2416_SetCount09(PlayerField2416 *field, u8 count)
{
    field->count_09 = count > PLAYER_FIELD_2416_COUNT_09_MAX ? PLAYER_FIELD_2416_COUNT_09_MAX : count;
}
CLEAN_AS(func_02088bc4, PlayerField2416_SetCount09)

/* func_02088bd4 */
int PlayerField2416_Count09(PlayerField2416 *field)
{
    return field->count_09;
}
CLEAN_AS(func_02088bd4, PlayerField2416_Count09)

/* func_02088bd8: the byte at 0x08 set to the low 8 bits of `value`. */
void PlayerField2416_SetByte08(PlayerField2416 *field, int value)
{
    field->byte_08 = (u8) value;
}
CLEAN_AS(func_02088bd8, PlayerField2416_SetByte08)

/* func_02088bdc */
int PlayerField2416_Byte08(PlayerField2416 *field)
{
    return field->byte_08;
}
CLEAN_AS(func_02088bdc, PlayerField2416_Byte08)

/* func_02088be0: the second date becomes today (its fourth byte is left as it is). */
void PlayerField2416_SetDate04Today(PlayerField2416 *field)
{
    Date today;
    Calendar_Today(&today);
    field->date_04.year = today.year;
    field->date_04.month = today.month;
    field->date_04.day = today.day;
}
CLEAN_AS(func_02088be0, PlayerField2416_SetDate04Today)

/* func_02088c04: the second date's address. */
int PlayerField2416_Date04(PlayerField2416 *field)
{
    return (int) (intptr_t) &field->date_04;
}
CLEAN_AS(func_02088c04, PlayerField2416_Date04)

/* func_02088c08: the new player's reset (PlayerRecord's), which leaves the object as it is. */
void PlayerField2416_Reset(PlayerField2416 *field)
{
    (void) field;
}
CLEAN_AS(func_02088c08, PlayerField2416_Reset)

/* func_02088c0c: the destructor, which does nothing. */
void PlayerField2416_Destruct(PlayerField2416 *field)
{
    (void) field;
}
CLEAN_AS(func_02088c0c, PlayerField2416_Destruct)

/* func_02088c10: the constructor, which does nothing. */
void PlayerField2416_Construct(PlayerField2416 *field)
{
    (void) field;
}
CLEAN_AS(func_02088c10, PlayerField2416_Construct)
