/* Main's side of the town's snowballs and snowmen (snowmen.h). */
#include "snowmen.h"

#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/calendar.h"
#include "main/mail.h"
#include "main/player_records.h"
#include "acre_record.h"
#include "date_time.h"
#include "item_record.h"
#include "letter.h"
#include "mail_text.h"
#include "main_random.h"
#include "map_code.h"
#include "name_texts.h"
#include "ov003/snowman.h"
#include "player_record.h"
#include "scene_query.h"

static_assert(sizeof(SnowmenRecord) == 6, "snowmen record");
static_assert(sizeof(SnowmenLooseBall) == 0x10, "snowmen loose ball");

/* The fields of SnowmenRecord's `built` and `sizes`. */
#define SNOWMEN_YEAR(built) ((built) & 0x7fu)
#define SNOWMEN_MONTH(built) (((built) >> 7) & 0xfu)
#define SNOWMEN_DAY(built) (((built) >> 11) & 0x1fu)
#define SNOWMEN_HEAD(sizes) ((sizes) & 0x7fu)
#define SNOWMEN_BODY(sizes) (((sizes) >> 7) & 0x7fu)
#define SNOWMEN_FACE(sizes) (((sizes) >> 14) & 3u)

/* A loose ball's size between visits when it was never saved. */
#define SNOWMEN_BALL_SIZE 0x800
/* A snowman this many days old melts. */
#define SNOWMEN_MELT_DAYS 3
/* The inner acres of the town, where snowmen stand, and an acre's tiles. */
#define SNOWMEN_FIRST_ACRE 1
#define SNOWMEN_LAST_ACRE 4
#define SNOWMEN_ACRE_TILES 16
#define SNOWMEN_LAYER 0
/* The season from which on snow lies (see snowmen_snow_season). */
#define SNOWMEN_SEASON_SNOW 9

/* The gift letter: the argument its item's name goes to. */
#define SNOWMEN_GIFT_NAME_ARG 1

/* 1 while the field is a room. */
extern u8 data_020e54a8;
/* The loose balls between visits. */
extern SnowmenLooseBall data_021f4ae8[SNOWMEN_LOOSE_BALLS];
/* The town layout's (town_layout.h) settings are its byte 8 (0x021ebcd0); bits 2-7 the
 * season. */
extern u8 data_021ebcc8[];
/* The snow series items, the gifts of a snowman of the best proportions. */
extern const u16 data_020d1e74[SNOWMEN_GIFTS];
/* The gift letter's sender "sp_npc_snowman" and the two values func_02066024 takes with it. */
extern const char data_020e41dc[];
extern const u8 data_020e41d4[];
extern const u8 data_020e41d8[];

/* The sender of the gift letter: the gift's index and its item. */
typedef struct SnowmenGiftSender {
    u8 gift;
    u8 unused;
    u16 item;
} SnowmenGiftSender;

static int snowmen_snow_season(void)
{
    return SceneQuery_SeasonHasSnow((data_021ebcc8[8] >> 2) & 0x3f);
}

/* func_020b03c0: outdoors, whether one of overlay 3's balls guides an actor that pushes with
 * `push` (above 0) at `angle` (to `point`, `yaw` and `step`); 0 otherwise. */
int Snowmen_GuidePush(Vec3 *point, s16 *yaw, int *step, fx32 push, s16 angle)
{
    if (data_020e54a8 == 0 && push > 0) {
        return Snowman_PushAny(point, yaw, step, push, angle);
    }
    return 0;
}
CLEAN_AS(func_020b03c0, Snowmen_GuidePush)

/* func_020b03f8 */
SnowmenLooseBall *Snowmen_LooseBalls(void)
{
    return data_021f4ae8;
}
CLEAN_AS(func_020b03f8, Snowmen_LooseBalls)

/* Whether the catalog lacks gift `gift`. */
static int snowmen_gift_missing(u8 *player, u32 gift)
{
    u16 item = data_020d1e74[gift];
    return ItemRecord_Has((ItemRecord *) (void *) (PlayerRecord_ItemRecord((u8 *) (uintptr_t) player)), &item) == 0;
}

/* func_020b0400: mails this system's player one of the snow series at random, picked among
 * those its catalog lacks when there are any. Nothing without a player. */
void Snowmen_MailGift(void)
{
    u8 *player = PlayerRecords_Current();
    if (player == NULL) {
        return;
    }
    int missing = 0;
    for (u32 i = 0; i < SNOWMEN_GIFTS; i++) {
        if (snowmen_gift_missing(player, i)) {
            missing++;
        }
    }
    if (missing != 0) {
        int pick = (int) MainRandom_Below(missing);
        int seen = 0;
        for (u32 i = 0; i < SNOWMEN_GIFTS; i++) {
            if (snowmen_gift_missing(player, i)) {
                if (seen == pick) {
                    Snowmen_MailGiftItem(i);
                    return;
                }
                seen++;
            }
        }
    }
    Snowmen_MailGiftItem(MainRandom_Below(SNOWMEN_GIFTS));
}
CLEAN_AS(func_020b0400, Snowmen_MailGift)

/* func_020b048c: a letter from the snowman ("sp_npc_snowman") naming and carrying gift `gift`,
 * waiting at the post office for this system's player. Nothing for an index past the series
 * or without a player. */
void Snowmen_MailGiftItem(u32 gift)
{
    SnowmenGiftSender sender;
    u8 name[0x28];
    Letter letter;

    if (gift >= SNOWMEN_GIFTS) {
        return;
    }
    sender.item = data_020d1e74[gift];
    u8 *player = PlayerRecords_Current();
    if (player == NULL) {
        return;
    }
    Letter_Construct(&letter);
    sender.gift = (u8) gift;
    NameText_ConstructItem((NameText *) (void *) name, &sender.item);
    MailText_SetPartText(SNOWMEN_GIFT_NAME_ARG, name);
    Letter_WriteSpecialToPlayer(&letter, (const u8 *) &sender, data_020e41dc, data_020e41d4, data_020e41d8,
                                PlayerRecord_Player((u8 *) (uintptr_t) player));
    Letter_SetItem(&letter, sender.item, 1);
    Mail_HoldAtPostOffice(&letter, 0);
    NameText_Destruct((NameText *) (void *) name);
    Letter_Destruct(&letter);
}
CLEAN_AS(func_020b048c, Snowmen_MailGiftItem)

/* func_020b0518: both loose balls at the origin, of the starting size. */
void Snowmen_ResetLooseBalls(SnowmenLooseBall *balls)
{
    for (u32 i = 0; i < SNOWMEN_LOOSE_BALLS; i++) {
        balls[i].position.x = 0;
        balls[i].position.y = 0;
        balls[i].position.z = 0;
        balls[i].size = SNOWMEN_BALL_SIZE;
    }
}
CLEAN_AS(func_020b0518, Snowmen_ResetLooseBalls)

/* func_020b0540: a recorded snowman no longer stands on the map. */
void Snowmen_TakeOffMap(SnowmenRecord *records, u32 number)
{
    if (number < SNOWMEN_COUNT && Snowmen_IsRecorded(&records[number]) != 0) {
        records[number].on_map = 0;
    }
}
CLEAN_AS(func_020b0540, Snowmen_TakeOffMap)

/* func_020b0568: whether all three snowmen are recorded (no room for another). */
int Snowmen_AllRecorded(SnowmenRecord *records)
{
    for (u32 i = 0; i < SNOWMEN_COUNT; i++) {
        if (Snowmen_IsRecorded(&records[i]) == 0) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_020b0568, Snowmen_AllRecorded)

/* func_020b0594: a recorded snowman's sizes (melted by its age), face and the day it was built,
 * each to the place given unless NULL. Whether it is recorded. */
int Snowmen_Get(SnowmenRecord *records, u32 number, int *head_size, int *body_size, int *face, u8 *year, u8 *month, u8 *day)
{
    if (number >= SNOWMEN_COUNT) {
        return 0;
    }
    SnowmenRecord *record = &records[number];
    if (Snowmen_IsRecorded(record) == 0) {
        return 0;
    }
    if (head_size != NULL) {
        *head_size = Snowmen_RecordHead(record);
    }
    if (body_size != NULL) {
        *body_size = Snowmen_RecordBody(record);
    }
    if (face != NULL) {
        *face = Snowmen_RecordFace(record);
    }
    if (year != NULL) {
        *year = (u8) SNOWMEN_YEAR(record->built);
    }
    if (month != NULL) {
        *month = (u8) SNOWMEN_MONTH(record->built);
    }
    if (day != NULL) {
        *day = (u8) SNOWMEN_DAY(record->built);
    }
    return 1;
}
CLEAN_AS(func_020b0594, Snowmen_Get)

/* func_020b060c: records a snowman built today in the first free record; its number, or -1
 * when all are taken. */
int Snowmen_Add(SnowmenRecord *records, int head_size, int body_size, int face)
{
    for (u32 i = 0; i < SNOWMEN_COUNT; i++) {
        SnowmenRecord *record = &records[i];
        if (Snowmen_IsRecorded(record) == 0) {
            Snowmen_Record(record, (u16) head_size, (u16) body_size, face);
            return (int) i;
        }
    }
    return -1;
}
CLEAN_AS(func_020b060c, Snowmen_Add)

/* func_020b0650: forgets a recorded snowman; whether it was recorded. */
int Snowmen_Forget(SnowmenRecord *records, u32 number)
{
    if (number < SNOWMEN_COUNT && Snowmen_IsRecorded(&records[number]) != 0) {
        Snowmen_ClearRecord(&records[number]);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_020b0650, Snowmen_Forget)

/* func_020b0678 */
void Snowmen_ForgetAll(SnowmenRecord *records)
{
    for (u32 i = 0; i < SNOWMEN_COUNT; i++) {
        Snowmen_ClearRecord(&records[i]);
    }
}
CLEAN_AS(func_020b0678, Snowmen_ForgetAll)

/* func_020b0698: the day's turn. Out of the snow season every snowman's map object goes and
 * all are forgotten. In it, each recorded snowman: one no longer on the map is forgotten once
 * built on another day; one standing is taken off the map and forgotten when three or more days
 * old (or built after today), and otherwise ages. */
void Snowmen_Melt(SnowmenRecord *records)
{
    int snow = snowmen_snow_season();
    for (u32 i = 0; i < SNOWMEN_COUNT; i++) {
        SnowmenRecord *record = &records[i];
        if (snow == 0) {
            if (Snowmen_RemoveObject((int) i) != 0) {
                Snowmen_ClearRecord(record);
            }
            continue;
        }
        if (Snowmen_IsRecorded(record) == 0) {
            continue;
        }
        int days = Snowmen_RecordAge(record);
        if (record->on_map == 0) {
            if (days != 0) {
                Snowmen_ClearRecord(record);
            }
        } else if (days >= SNOWMEN_MELT_DAYS || days < 0) {
            if (Snowmen_RemoveObject((int) i) != 0) {
                Snowmen_ClearRecord(record);
            }
        } else {
            record->age = (u8) days;
        }
    }
}
CLEAN_AS(func_020b0698, Snowmen_Melt)

/* func_020b0730: snowman `number`'s map object off the town's map, when it stands there.
 * QUIRK: always answers 1. */
int Snowmen_RemoveObject(int number)
{
    int x, z;
    if (Snowmen_FindObject(&x, &z, number) != 0) {
        AcreMap *town = (AcreMap *) (uintptr_t) AcreMap_Town();
        u16 none = ACRE_MAP_ITEM_NONE;
        AcreTile_SetItem(town, &none, x, z, SNOWMEN_LAYER);
        return 1;
    }
    return 1;
}
CLEAN_AS(func_020b0730, Snowmen_RemoveObject)

/* func_020b076c: the tile (on the whole town map) of snowman `number`'s map object, searched
 * acre by acre through the inner acres, row by row; whether it was found.
 * REQUIRES: the town's map exists. */
int Snowmen_FindObject(int *x, int *z, int number)
{
    AcreMap *town = (AcreMap *) (uintptr_t) AcreMap_Town();
    for (int acre_z = SNOWMEN_FIRST_ACRE; acre_z <= SNOWMEN_LAST_ACRE; acre_z++) {
        for (int acre_x = SNOWMEN_FIRST_ACRE; acre_x <= SNOWMEN_LAST_ACRE; acre_x++) {
            u32 wide = (u32) town->acres_wide;
            u32 high = (u32) town->acres_high;
            if ((u32) acre_x >= wide || (u32) acre_z >= high || town->acres == NULL) {
                continue;
            }
            u8 *acre = town->acres + ((u32) acre_z * wide + (u32) acre_x) * ACRE_MAP_ACRE_SIZE;
            for (int tile_z = 0; tile_z < SNOWMEN_ACRE_TILES; tile_z++) {
                for (int tile_x = 0; tile_x < SNOWMEN_ACRE_TILES; tile_x++) {
                    u16 *code = AcreRecord_Tile((AcreRecord *) (void *) acre, tile_x, tile_z, SNOWMEN_LAYER);
                    if (code != NULL && MapCode_IsSnowman(code) != 0 && number == MapCode_SnowmanIndex(code)) {
                        AcreTile_TileOfAcre(x, z, acre_x, acre_z, tile_x, tile_z);
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
CLEAN_AS(func_020b076c, Snowmen_FindObject)

/* The record arrays' element functions and the C++ array helpers that run them. The element
 * functions are handed to the game, so they go by their symbols. */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void func_020b0a80(void *record); /* a record's destructor */
extern void func_020b0a84(void *record); /* a record's constructor */
extern void func_020b0aa4(void *ball);   /* a loose ball's destructor */
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_MulFunc(fx32 a, fx32 b);

/* The snowmen's day starts at 6:00: before it, it is still the day before. */
#define SNOWMEN_DAY_START_HOUR 6
/* One in 20.12 fixed point: a snowman's sizes are kept in steps of 0x80 of it. */
#define SNOWMEN_FX_ONE 0x1000
#define SNOWMEN_SIZE_STEP 0x80

/* Today's date and time for the snowmen, the day starting at 6:00. */
static void snowmen_today(DateTime *now)
{
    *now = (DateTime){0};
    DateTime_Now(now);
    if (now->hour < SNOWMEN_DAY_START_HOUR) {
        DateTime_SubtractDays(now, 1);
    }
}

/* A recorded size as fx32, the empty size counting as one, shrunk by the snowman's age: whole
 * on the day it was built, three quarters the day after, half the day after that. */
static fx32 snowmen_melted_size(u32 steps, u8 age)
{
    fx32 size = (fx32) (steps * SNOWMEN_SIZE_STEP);
    if (size == 0) {
        size = SNOWMEN_FX_ONE;
    }
    fx32 scale = SNOWMEN_FX_ONE;
    if (age == 1) {
        scale = FX_Div(3 * SNOWMEN_FX_ONE, 4 * SNOWMEN_FX_ONE);
    } else if (age == 2) {
        scale = FX_Div(SNOWMEN_FX_ONE, 2 * SNOWMEN_FX_ONE);
    }
    if (scale > SNOWMEN_FX_ONE) {
        scale = SNOWMEN_FX_ONE;
    }
    return FX_MulFunc(size, scale);
}

/* func_020b081c: the destructor of the three records (registered for data_021f3b56); returns
 * them. */
int Snowmen_DestructRecords(SnowmenRecord *records)
{
    __cxa_vec_cleanup(records, SNOWMEN_COUNT, sizeof(SnowmenRecord), func_020b0a80);
    return (int) (uintptr_t) records;
}
CLEAN_AS(func_020b081c, Snowmen_DestructRecords)

/* func_020b0838: the constructor of the three records. */
SnowmenRecord *Snowmen_ConstructRecords(SnowmenRecord *records)
{
    __cxa_vec_ctor(records, SNOWMEN_COUNT, sizeof(SnowmenRecord), func_020b0a84, func_020b0a80);
    return records;
}
CLEAN_AS(func_020b0838, Snowmen_ConstructRecords)

/* func_020b0860: the days from the day the snowman was built to today (negative when built on a
 * later day). */
int Snowmen_RecordAge(SnowmenRecord *record)
{
    DateTime now;
    snowmen_today(&now);
    Date today = {now.day, now.month, now.year, 0};
    Date built = {(u8) SNOWMEN_DAY(record->built), (u8) SNOWMEN_MONTH(record->built), (u8) SNOWMEN_YEAR(record->built), 0};
    return Calendar_DaysFrom(&today, &built);
}
CLEAN_AS(func_020b0860, Snowmen_RecordAge)

/* func_020b08b8 */
int Snowmen_RecordFace(SnowmenRecord *record)
{
    return (int) SNOWMEN_FACE(record->sizes);
}
CLEAN_AS(func_020b08b8, Snowmen_RecordFace)

/* func_020b08c0: the body's size in fx32, melted by the snowman's age. */
int Snowmen_RecordBody(SnowmenRecord *record)
{
    return snowmen_melted_size(SNOWMEN_BODY(record->sizes), record->age);
}
CLEAN_AS(func_020b08c0, Snowmen_RecordBody)

/* func_020b0918: the head's size in fx32, melted by the snowman's age. */
int Snowmen_RecordHead(SnowmenRecord *record)
{
    return snowmen_melted_size(SNOWMEN_HEAD(record->sizes), record->age);
}
CLEAN_AS(func_020b0918, Snowmen_RecordHead)

/* func_020b0970: records a snowman built today with sizes in fx32 (kept in steps of 0x80) and
 * its face; not aged, standing on the map. */
void Snowmen_Record(SnowmenRecord *record, u16 head_size, u16 body_size, int face)
{
    record->sizes = (u16) (((head_size / SNOWMEN_SIZE_STEP) & 0x7fu) | (((body_size / SNOWMEN_SIZE_STEP) & 0x7fu) << 7) |
                           (((u32) face & 3u) << 14));
    record->age = 0;
    DateTime now;
    snowmen_today(&now);
    record->built = (u16) ((now.year & 0x7fu) | ((now.month & 0xfu) << 7) | ((now.day & 0x1fu) << 11));
    record->on_map = 1;
}
CLEAN_AS(func_020b0970, Snowmen_Record)

/* func_020b0a20: whether the record holds a snowman (both sizes nonzero). */
int Snowmen_IsRecorded(SnowmenRecord *record)
{
    return SNOWMEN_HEAD(record->sizes) != 0 && SNOWMEN_BODY(record->sizes) != 0;
}
CLEAN_AS(func_020b0a20, Snowmen_IsRecorded)

/* func_020b0a3c: the record emptied.
 * QUIRK: the age stays. */
void Snowmen_ClearRecord(SnowmenRecord *record)
{
    record->built = 0;
    record->sizes = 0;
    record->on_map = 0;
}
CLEAN_AS(func_020b0a3c, Snowmen_ClearRecord)

/* func_020b0a80: a record's destructor, which does nothing. */
void Snowmen_DestructRecord(void *record)
{
    (void) record;
}
CLEAN_AS(func_020b0a80, Snowmen_DestructRecord)

/* func_020b0a84: a record's constructor, which does nothing. */
void Snowmen_ConstructRecord(void *record)
{
    (void) record;
}
CLEAN_AS(func_020b0a84, Snowmen_ConstructRecord)

/* func_020b0a88: the destructor of the two loose balls (registered for data_021f4ae8); returns
 * them. */
SnowmenLooseBall *Snowmen_DestructLooseBalls(SnowmenLooseBall *balls)
{
    __cxa_vec_cleanup(balls, SNOWMEN_LOOSE_BALLS, sizeof(SnowmenLooseBall), func_020b0aa4);
    return balls;
}
CLEAN_AS(func_020b0a88, Snowmen_DestructLooseBalls)

/* func_020b0aa4: a loose ball's destructor, which does nothing. */
void Snowmen_DestructLooseBall(void *ball)
{
    (void) ball;
}
CLEAN_AS(func_020b0aa4, Snowmen_DestructLooseBall)

/* func_020b0aa8: a loose ball's constructor: at the origin, of the starting size. */
void Snowmen_ConstructLooseBall(SnowmenLooseBall *ball)
{
    ball->position.x = 0;
    ball->position.y = 0;
    ball->position.z = 0;
    ball->size = SNOWMEN_BALL_SIZE;
}
CLEAN_AS(func_020b0aa8, Snowmen_ConstructLooseBall)
