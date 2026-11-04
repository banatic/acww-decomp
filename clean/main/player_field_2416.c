/* A player record's object at 0x2416 (player_field_2416.h). */
#include "player_field_2416.h"

#include "calendar.h"
#include "clean.h"

static_assert(offsetof(PlayerField2416, tailor_talk_days) == 0x08 && offsetof(PlayerField2416, fashion_score) == 0x0e,
              "field 2416");
static_assert(sizeof(PlayerField2416) == PLAYER_FIELD_2416_SIZE, "field 2416");
static_assert(offsetof(PlayerField2416, job_end) == 0x04 && offsetof(PlayerField2416, resets) == 0x0d, "field 2416");

/* func_02088a60: the count of forged paintings claimed raised by one.
 * BUG: the cap at 255 is tested after the byte was raised, so 255 wraps to 0.
 * BUGFIX: test before raising. */
void PlayerField2416_RaiseForgeryClaims(PlayerField2416 *field)
{
#ifdef BUGFIX
    if (field->forgery_claims < PLAYER_FIELD_2416_FORGERY_CLAIMS_MAX) {
        field->forgery_claims++;
    }
#else
    field->forgery_claims = (u8) (field->forgery_claims + 1);
#endif
}
CLEAN_AS(func_02088a60, PlayerField2416_RaiseForgeryClaims)

/* func_02088a74 */
int PlayerField2416_ForgeryClaims(PlayerField2416 *field)
{
    return field->forgery_claims;
}
CLEAN_AS(func_02088a74, PlayerField2416_ForgeryClaims)

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
void PlayerField2416_ClearAcorns(PlayerField2416 *field)
{
    field->acorn_points = 0;
    field->acorn_level = 0;
}
CLEAN_AS(func_02088ac0, PlayerField2416_ClearAcorns)

/* func_02088ac8: the tally in bits 2-5 cleared. */
void PlayerField2416_ClearFireworksGifts(PlayerField2416 *field)
{
    field->flags &= (u8) ~PLAYER_FIELD_2416_FIREWORKS_GIFTS_MASK;
}
CLEAN_AS(func_02088ac8, PlayerField2416_ClearFireworksGifts)

/* func_02088ad4: the tally raised by one, up to 10.
 * QUIRK: it is raised within its four bits before the cap is tested, so 15 (never reached)
 * would wrap to 0. */
void PlayerField2416_RaiseFireworksGifts(PlayerField2416 *field)
{
    u32 tally =
        (((field->flags & PLAYER_FIELD_2416_FIREWORKS_GIFTS_MASK) >> PLAYER_FIELD_2416_FIREWORKS_GIFTS_SHIFT) + 1) & 0xf;
    if (tally > PLAYER_FIELD_2416_FIREWORKS_GIFTS_MAX) {
        tally = PLAYER_FIELD_2416_FIREWORKS_GIFTS_MAX;
    }
    field->flags =
        (u8) ((field->flags & ~PLAYER_FIELD_2416_FIREWORKS_GIFTS_MASK) | (tally << PLAYER_FIELD_2416_FIREWORKS_GIFTS_SHIFT));
}
CLEAN_AS(func_02088ad4, PlayerField2416_RaiseFireworksGifts)

/* func_02088b14 */
int PlayerField2416_FireworksGifts(PlayerField2416 *field)
{
    return (field->flags & PLAYER_FIELD_2416_FIREWORKS_GIFTS_MASK) >> PLAYER_FIELD_2416_FIREWORKS_GIFTS_SHIFT;
}
CLEAN_AS(func_02088b14, PlayerField2416_FireworksGifts)

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
void PlayerField2416_AddFashionScore(PlayerField2416 *field, u8 amount)
{
    u8 count = (u8) (field->fashion_score + amount);
    if (count > PLAYER_FIELD_2416_FASHION_SCORE_MAX) {
        count = PLAYER_FIELD_2416_FASHION_SCORE_MAX;
    }
    field->fashion_score = count;
}
CLEAN_AS(func_02088b50, PlayerField2416_AddFashionScore)

/* func_02088b64 */
int PlayerField2416_FashionScore(PlayerField2416 *field)
{
    return field->fashion_score;
}
CLEAN_AS(func_02088b64, PlayerField2416_FashionScore)

/* func_02088b68: the count at 0x0d raised by one, up to 6.
 * QUIRK: it is raised within its byte before the cap is tested, so 255 would wrap to 0. */
void PlayerField2416_RaiseResets(PlayerField2416 *field)
{
    u8 count = (u8) (field->resets + 1);
    if (count > PLAYER_FIELD_2416_RESETS_MAX) {
        count = PLAYER_FIELD_2416_RESETS_MAX;
    }
    field->resets = count;
}
CLEAN_AS(func_02088b68, PlayerField2416_RaiseResets)

/* func_02088b7c */
int PlayerField2416_Resets(PlayerField2416 *field)
{
    return field->resets;
}
CLEAN_AS(func_02088b7c, PlayerField2416_Resets)

/* func_02088b80: the level raised by one, up to 12.
 * QUIRK: it is raised within its byte before the cap is tested, so 255 would wrap to 0. */
void PlayerField2416_RaiseAcornLevel(PlayerField2416 *field)
{
    u8 level = (u8) (field->acorn_level + 1);
    if (level > PLAYER_FIELD_2416_ACORN_LEVEL_MAX) {
        level = PLAYER_FIELD_2416_ACORN_LEVEL_MAX;
    }
    field->acorn_level = level;
}
CLEAN_AS(func_02088b80, PlayerField2416_RaiseAcornLevel)

/* func_02088b94 */
int PlayerField2416_AcornLevel(PlayerField2416 *field)
{
    return field->acorn_level;
}
CLEAN_AS(func_02088b94, PlayerField2416_AcornLevel)

/* func_02088b98: `amount` points added, up to 255.
 * QUIRK: only the top is capped; a negative sum is kept in the byte as its low 8 bits. */
void PlayerField2416_AddAcornPoints(PlayerField2416 *field, int amount)
{
    int points = field->acorn_points + amount;
    if (points > PLAYER_FIELD_2416_ACORN_POINTS_MAX) {
        points = PLAYER_FIELD_2416_ACORN_POINTS_MAX;
    }
    field->acorn_points = (u8) points;
}
CLEAN_AS(func_02088b98, PlayerField2416_AddAcornPoints)

/* func_02088ba8 */
int PlayerField2416_AcornPoints(PlayerField2416 *field)
{
    return field->acorn_points;
}
CLEAN_AS(func_02088ba8, PlayerField2416_AcornPoints)

/* func_02088bac: `amount` added to the count at 0x0a, up to 16.
 * QUIRK: the sum is kept in the byte before the cap is tested, so a sum past 255 wraps and
 * stays under the cap. */
void PlayerField2416_AddHaircuts(PlayerField2416 *field, int amount)
{
    u8 count = (u8) (field->haircuts + amount);
    if (count > PLAYER_FIELD_2416_HAIRCUTS_MAX) {
        count = PLAYER_FIELD_2416_HAIRCUTS_MAX;
    }
    field->haircuts = count;
}
CLEAN_AS(func_02088bac, PlayerField2416_AddHaircuts)

/* func_02088bc0 */
int PlayerField2416_Haircuts(PlayerField2416 *field)
{
    return field->haircuts;
}
CLEAN_AS(func_02088bc0, PlayerField2416_Haircuts)

/* func_02088bc4: the count at 0x09 set, up to 15. */
void PlayerField2416_SetCoffees(PlayerField2416 *field, u8 count)
{
    field->coffees = count > PLAYER_FIELD_2416_COFFEES_MAX ? PLAYER_FIELD_2416_COFFEES_MAX : count;
}
CLEAN_AS(func_02088bc4, PlayerField2416_SetCoffees)

/* func_02088bd4 */
int PlayerField2416_Coffees(PlayerField2416 *field)
{
    return field->coffees;
}
CLEAN_AS(func_02088bd4, PlayerField2416_Coffees)

/* func_02088bd8: the byte at 0x08 set to the low 8 bits of `value`. */
void PlayerField2416_SetTailorTalkDays(PlayerField2416 *field, int value)
{
    field->tailor_talk_days = (u8) value;
}
CLEAN_AS(func_02088bd8, PlayerField2416_SetTailorTalkDays)

/* func_02088bdc */
int PlayerField2416_TailorTalkDays(PlayerField2416 *field)
{
    return field->tailor_talk_days;
}
CLEAN_AS(func_02088bdc, PlayerField2416_TailorTalkDays)

/* func_02088be0: the second date becomes today (its fourth byte is left as it is). */
void PlayerField2416_SetJobEndToday(PlayerField2416 *field)
{
    Date today;
    Calendar_Today(&today);
    field->job_end.year = today.year;
    field->job_end.month = today.month;
    field->job_end.day = today.day;
}
CLEAN_AS(func_02088be0, PlayerField2416_SetJobEndToday)

/* func_02088c04: the second date's address. */
int PlayerField2416_JobEndDate(PlayerField2416 *field)
{
    return (int) (intptr_t) &field->job_end;
}
CLEAN_AS(func_02088c04, PlayerField2416_JobEndDate)

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
