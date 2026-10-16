/* Main's side of the town's snowballs and snowmen (overlay 3's balls: ov003/snowman.h).
 *
 * Main keeps the three snowmen of the town (data_021f3b56, a SnowmenRecord each, handed to
 * these functions as `records`) and the two loose balls' positions and sizes from one visit to
 * the next (data_021f4ae8, Snowmen_LooseBalls). A snowman stands on the town's map as a map
 * object (func_0204bb54 recognises it, func_0204bb2c gives its number) in one of the 4 x 4
 * inner acres.
 *
 * A snowman is recorded when a ball is put on another (Snowmen_Add): the day it was built (the
 * day turns at 6:00), the sizes of its head and body and its face. Each day (Snowmen_Melt) a
 * snowman ages a day, and one three days old, or built on a later day than today, is taken off
 * the map and forgotten; one no longer on the map is forgotten once a day has passed. Out of the
 * snow season all of them go. A snowman of the best proportions (face 0) sends this system's
 * player a letter with an item of the snow series (Snowmen_MailGift). */
#ifndef CLEAN_MAIN_SNOWMEN_H
#define CLEAN_MAIN_SNOWMEN_H

#include "autoload_2/vector.h"
#include "types.h"

#define SNOWMEN_COUNT 3
#define SNOWMEN_LOOSE_BALLS 2
#define SNOWMEN_GIFTS 13

/* A snowman as main keeps it. `built` holds the day it was built: the year (from 2000) in bits
 * 0-6, the month in bits 7-10 and the day in bits 11-15. `sizes` holds the head's size in bits
 * 0-6 and the body's in bits 7-13 (each in steps of 0x80 of fx32), and the face in bits 14-15.
 * A snowman is recorded while both sizes are nonzero. */
typedef struct SnowmenRecord {
    u16 built;
    u16 sizes;
    u8 age;    /* days since it was built, set each day while it stands */
    u8 on_map; /* 1 while its map object stands in the town */
} SnowmenRecord;

/* A loose ball between visits. */
typedef struct SnowmenLooseBall {
    Vec3 position;
    fx32 size;
} SnowmenLooseBall;

int Snowmen_GuidePush(Vec3 *point, s16 *yaw, int *step, fx32 push, s16 angle);
SnowmenLooseBall *Snowmen_LooseBalls(void);
void Snowmen_MailGift(void);
void Snowmen_MailGiftItem(u32 gift);
void Snowmen_ResetLooseBalls(SnowmenLooseBall *balls);
void Snowmen_TakeOffMap(SnowmenRecord *records, u32 number);
int Snowmen_AllRecorded(SnowmenRecord *records);
int Snowmen_Get(SnowmenRecord *records, u32 number, int *head_size, int *body_size, int *face, u8 *year, u8 *month, u8 *day);
int Snowmen_Add(SnowmenRecord *records, int head_size, int body_size, int face);
int Snowmen_Forget(SnowmenRecord *records, u32 number);
void Snowmen_ForgetAll(SnowmenRecord *records);
void Snowmen_Melt(SnowmenRecord *records);
int Snowmen_RemoveObject(int number);
int Snowmen_FindObject(int *x, int *z, int number);

int Snowmen_DestructRecords(SnowmenRecord *records);
SnowmenRecord *Snowmen_ConstructRecords(SnowmenRecord *records);
int Snowmen_RecordAge(SnowmenRecord *record);
int Snowmen_RecordFace(SnowmenRecord *record);
int Snowmen_RecordBody(SnowmenRecord *record);
int Snowmen_RecordHead(SnowmenRecord *record);
void Snowmen_Record(SnowmenRecord *record, u16 head_size, u16 body_size, int face);
int Snowmen_IsRecorded(SnowmenRecord *record);
void Snowmen_ClearRecord(SnowmenRecord *record);
void Snowmen_DestructRecord(void *record);
void Snowmen_ConstructRecord(void *record);
SnowmenLooseBall *Snowmen_DestructLooseBalls(SnowmenLooseBall *balls);
void Snowmen_DestructLooseBall(void *ball);
void Snowmen_ConstructLooseBall(SnowmenLooseBall *ball);

#endif
