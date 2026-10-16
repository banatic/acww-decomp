/* Main's side of the town's snowballs and snowmen (snowmen.h). */
#include "snowmen.h"

#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/mail.h"
#include "main/player_records.h"

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

/* Overlay 3: whether one of its balls guides an actor pushing it. */
extern int func_ov003_022361bc(Vec3 *point, s16 *yaw, int *step, fx32 push, s16 angle);
extern u32 func_020644cc(int range);                 /* a random number below `range` */
extern int func_020996ac(int player);                /* the player's catalog */
extern int func_0203cdcc(int catalog, u16 *item);    /* whether the catalog has the item */
extern int func_02099870(int player);                /* the player's part func_02066024 takes */
extern void func_02066694(MailLetter *letter);       /* an empty letter */
extern void func_02066688(MailLetter *letter);       /* its destructor */
extern void *func_02062f90(void *object, u16 *item); /* the item's name, built */
extern void *func_02062f4c(void *object);            /* destroyed */
extern int func_0203d7c4(int index, void *object);   /* a message argument */
extern void func_02066024(MailLetter *letter, void *sender, const char *name, const void *a, const void *b, int c);
extern u16 func_02065ed0(MailLetter *letter, u16 item, int a); /* the item the letter carries */
extern int func_020b65ac(int season);                          /* whether snow lies in the season */
extern u16 *func_02037e0c(u8 *acre, int x, int z, u8 layer);   /* the code of tile (x, z), or 0 */
extern int func_0204bb54(u16 *code);                           /* a snowman's map object */
extern int func_0204bb2c(u16 *code);                           /* the snowman's number */
/* The record's day, sizes and face, today's date (before 6:00 the day before), not aged, on
 * the map. */
extern void func_020b0970(SnowmenRecord *record, u16 head_size, u16 body_size, int face);
extern int func_020b0a20(SnowmenRecord *record);  /* whether it is recorded */
extern void func_020b0a3c(SnowmenRecord *record); /* cleared */
extern int func_020b0918(SnowmenRecord *record);  /* the head's size, melted */
extern int func_020b08c0(SnowmenRecord *record);  /* the body's size, melted */
extern int func_020b08b8(SnowmenRecord *record);  /* the face */
extern int func_020b0860(SnowmenRecord *record);  /* the days from the day it was built to today */

/* The sender of the gift letter: the gift's index and its item. */
typedef struct SnowmenGiftSender {
    u8 gift;
    u8 unused;
    u16 item;
} SnowmenGiftSender;

static int snowmen_snow_season(void)
{
    return func_020b65ac((data_021ebcc8[8] >> 2) & 0x3f);
}

/* func_020b03c0: outdoors, whether one of overlay 3's balls guides an actor that pushes with
 * `push` (above 0) at `angle` (to `point`, `yaw` and `step`); 0 otherwise. */
int Snowmen_GuidePush(Vec3 *point, s16 *yaw, int *step, fx32 push, s16 angle)
{
    if (data_020e54a8 == 0 && push > 0) {
        return func_ov003_022361bc(point, yaw, step, push, angle);
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
    return func_0203cdcc(func_020996ac((int) (uintptr_t) player), &item) == 0;
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
        int pick = (int) func_020644cc(missing);
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
    Snowmen_MailGiftItem(func_020644cc(SNOWMEN_GIFTS));
}
CLEAN_AS(func_020b0400, Snowmen_MailGift)

/* func_020b048c: a letter from the snowman ("sp_npc_snowman") naming and carrying gift `gift`,
 * waiting at the post office for this system's player. Nothing for an index past the series
 * or without a player. */
void Snowmen_MailGiftItem(u32 gift)
{
    SnowmenGiftSender sender;
    u8 name[0x28];
    MailLetter letter;

    if (gift >= SNOWMEN_GIFTS) {
        return;
    }
    sender.item = data_020d1e74[gift];
    u8 *player = PlayerRecords_Current();
    if (player == NULL) {
        return;
    }
    func_02066694(&letter);
    sender.gift = (u8) gift;
    func_02062f90(name, &sender.item);
    func_0203d7c4(SNOWMEN_GIFT_NAME_ARG, name);
    func_02066024(&letter, &sender, data_020e41dc, data_020e41d4, data_020e41d8, func_02099870((int) (uintptr_t) player));
    func_02065ed0(&letter, sender.item, 1);
    Mail_HoldAtPostOffice(&letter, 0);
    func_02062f4c(name);
    func_02066688(&letter);
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
    if (number < SNOWMEN_COUNT && func_020b0a20(&records[number]) != 0) {
        records[number].on_map = 0;
    }
}
CLEAN_AS(func_020b0540, Snowmen_TakeOffMap)

/* func_020b0568: whether all three snowmen are recorded (no room for another). */
int Snowmen_AllRecorded(SnowmenRecord *records)
{
    for (u32 i = 0; i < SNOWMEN_COUNT; i++) {
        if (func_020b0a20(&records[i]) == 0) {
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
    if (func_020b0a20(record) == 0) {
        return 0;
    }
    if (head_size != NULL) {
        *head_size = func_020b0918(record);
    }
    if (body_size != NULL) {
        *body_size = func_020b08c0(record);
    }
    if (face != NULL) {
        *face = func_020b08b8(record);
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
        if (func_020b0a20(record) == 0) {
            func_020b0970(record, (u16) head_size, (u16) body_size, face);
            return (int) i;
        }
    }
    return -1;
}
CLEAN_AS(func_020b060c, Snowmen_Add)

/* func_020b0650: forgets a recorded snowman; whether it was recorded. */
int Snowmen_Forget(SnowmenRecord *records, u32 number)
{
    if (number < SNOWMEN_COUNT && func_020b0a20(&records[number]) != 0) {
        func_020b0a3c(&records[number]);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_020b0650, Snowmen_Forget)

/* func_020b0678 */
void Snowmen_ForgetAll(SnowmenRecord *records)
{
    for (u32 i = 0; i < SNOWMEN_COUNT; i++) {
        func_020b0a3c(&records[i]);
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
                func_020b0a3c(record);
            }
            continue;
        }
        if (func_020b0a20(record) == 0) {
            continue;
        }
        int days = func_020b0860(record);
        if (record->on_map == 0) {
            if (days != 0) {
                func_020b0a3c(record);
            }
        } else if (days >= SNOWMEN_MELT_DAYS || days < 0) {
            if (Snowmen_RemoveObject((int) i) != 0) {
                func_020b0a3c(record);
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
                    u16 *code = func_02037e0c(acre, tile_x, tile_z, SNOWMEN_LAYER);
                    if (code != NULL && func_0204bb54(code) != 0 && number == func_0204bb2c(code)) {
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
