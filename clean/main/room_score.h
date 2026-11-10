/* The score of a room's furniture: the points RoomScore_Total gives one or more rooms (the
 * five of the player's house, or the room of a villager's house), the bonuses it found, and
 * the "ev_happyroom" letters it can send the town's players about them (room_score_mail.c).
 *
 * A room is a map of acres of one acre (acre_map.h) whose tiles hold item codes on two
 * layers; RoomScore_Bounds finds the square the room's floor covers. Its furniture (the codes
 * 0x3000-0x4fff, item_code.h) is scored by what furniture_info.h tells of each piece:
 *   - its points (func_0206226c of FurnitureInfo_ListGroup);
 *   - the groups it belongs to (FurnitureInfo_ItemSeries and _IndexInSeries): a group of kind
 *     0 complete with all 12 pieces scores 30000, with its first 10 and a wallpaper or carpet
 *     of the group 25000, with its first 10 20000 (RoomScore_Kind0Sets); a complete group of
 *     kind 1 with the wallpaper and the carpet of the group 3000 per piece and 3000 more, with
 *     those but incomplete 3000 (RoomScore_Kind1Sets); a complete group of kind 2 1000 per
 *     piece (RoomScore_Kind2Sets). The best of each group is kept in data_021c9854;
 *   - the share of the pieces with one value of FurnitureInfo_ItemEra or _ItemFeel
 *     (RoomScore_EraFeelBonus), with one of the values of FurnitureInfo_ColorA and _ColorB
 *     (RoomScore_ColorBonus), a collection of 8 or more
 *     instruments, paintings, models or plants (FurnitureInfo_ItemTheme, RoomScore_CollectionBonus), all four categories 1-4 of FurnitureInfo_Category
 *     (RoomScore_MarkCategories), each piece of a kind marked in the indoor data counted once
 *     at 7777 (RoomScore_MarkSpecialItems);
 *   - the feng shui: the pieces along the low-x (west) columns, the high-z (south) rows and
 *     the high-x (east) columns of the room whose FurnitureInfo_ColorA or _ColorB is yellow,
 *     green and red there (RoomScoreFengShui, 100 each);
 *   - less 100 for each piece at an edge that faces it, 1 for each item of kind 1 on the floor
 *     (RoomScore_WallPenalty).
 *
 * A room asks a RoomScoreSource for its map, wallpaper and carpet: the player's house's rooms
 * (data_020dd3b8) or the villager's room (data_020dd3a4, made for the score in
 * data_021c95f0). */
#ifndef CLEAN_MAIN_ROOM_SCORE_H
#define CLEAN_MAIN_ROOM_SCORE_H

#include "acre_map.h"
#include "types.h"

/* The square a room's floor covers, in tiles, and its wallpaper and carpet. */
typedef struct RoomScoreRoom {
    int left;      /* 0x00: the least x */
    int top;       /* 0x04: the least z */
    int right;     /* 0x08: the greatest x */
    int bottom;    /* 0x0c: the greatest z */
    u16 wallpaper; /* 0x10: an item code, 0xfff1 for none */
    u16 carpet;    /* 0x12 */
} RoomScoreRoom;

/* Where the rooms come from: an object whose vtable gives, for room `index`, its map (slot
 * 0), its wallpaper (slot 1) and its carpet (slot 2), the last two as a halfword returned
 * through a pointer. */
typedef struct RoomScoreSource {
    const u32 *vtable;
} RoomScoreSource;

/* A room's feng shui: the pieces of a color counted along three of its sides
 * (RoomScore_CountFengShui). */
typedef struct RoomScoreFengShui {
    u8 yellow_west; /* color 1 (yellow), in the two columns of the least x */
    u8 green_south; /* color 4 (green), in the two rows of the greatest z */
    u8 red_east;    /* color 2 (red), in the two columns of the greatest x */
} RoomScoreFengShui;

/* The bonuses RoomScore_Total reports (its `bonuses`, and RoomScore_SetBonusFlags). */
#define ROOM_SCORE_KIND0_FULL 0x1         /* a group of kind 0 at 30000 */
#define ROOM_SCORE_KIND0_TEN_AND_WALL 0x2 /* at 25000 */
#define ROOM_SCORE_KIND0_TEN 0x4          /* at 20000 */
#define ROOM_SCORE_KIND1 0x8              /* a group of kind 1 over 3000 */
#define ROOM_SCORE_KIND2 0x10             /* groups of kind 2 for 3000 (5000 for the letter) */
#define ROOM_SCORE_CATEGORIES 0x20        /* all four categories */
#define ROOM_SCORE_FENG_SHUI 0x40         /* 500 (2000) from the feng shui */
#define ROOM_SCORE_COLORS 0x80            /* 2000 (6000) from RoomScore_ColorBonus */
#define ROOM_SCORE_ERA_FEEL 0x100         /* 2000 (6000) from RoomScore_EraFeelBonus */
#define ROOM_SCORE_COLLECTION 0x200       /* 3000 (3200) from a collection (RoomScore_CollectionBonus) */
#define ROOM_SCORE_SPECIAL 0x400          /* 7000 from the special items */
#define ROOM_SCORE_LOOSE_ITEMS 0x800      /* the letter's only: items of kind 1 on the floor */
#define ROOM_SCORE_FACING_WALL 0x1000     /* the letter's only: furniture facing an edge */
#define ROOM_SCORE_BONUS_BITS 13

/* RoomScore_Kind0Sets with no group at its best: the count of the groups. */
#define ROOM_SCORE_GROUPS 0x4a

int RoomScore_Bounds(int *left, int *right, int *top, int *bottom, AcreMap *map);
void RoomScore_MarkSpecialItems(RoomScoreRoom *room, AcreMap *map);
int RoomScore_WallPenalty(RoomScoreRoom *room, AcreMap *map, u8 *facing, u8 *loose);
int RoomScore_CollectionBonus(RoomScoreRoom *room, AcreMap *map, int *theme);
int RoomScore_EraFeelBonus(RoomScoreRoom *room, AcreMap *map, int *first, int *second);
int RoomScore_ColorBonus(RoomScoreRoom *room, AcreMap *map);
int RoomScore_FengShuiBonus(RoomScoreRoom *room, RoomScoreFengShui *edges);
int RoomScore_ItemPoints(RoomScoreRoom *room, AcreMap *map);
void RoomScore_MarkCategories(RoomScoreRoom *room, AcreMap *map);
int RoomScore_Kind2Sets(RoomScoreRoom *room, AcreMap *map);
int RoomScore_Kind1Sets(RoomScoreRoom *room, AcreMap *map);
int RoomScore_Kind0Sets(RoomScoreRoom *room, AcreMap *map, u32 *most);
int RoomScore_Total(RoomScoreRoom *room, u16 *bonuses, int *theme, int *first, int *second, RoomScoreSource *source, int count,
                    int first_index, u8 judge);
u32 RoomScore_ScoreVillager(RoomScoreRoom *room, int villager, u16 *bonuses, int *theme, int *first, int *second);
void RoomScore_JudgeHouse(RoomScoreRoom *room);
int RoomScore_Advice(RoomScoreRoom *room, int *count);
void RoomScore_DestructRoom(RoomScoreRoom *room);
void RoomScore_InitRoom(RoomScoreRoom *room);
int RoomScore_SpecialItemsScore(const u32 *marks);

void RoomScore_VillagerCarpet(u16 *out, RoomScoreSource *source, int villager);
void RoomScore_VillagerWallpaper(u16 *out, RoomScoreSource *source, int villager);
u32 RoomScore_VillagerMap(void);
RoomScoreSource *RoomScore_DestructVillagerSource(RoomScoreSource *source);
RoomScoreSource *RoomScore_ConstructVillagerSource(RoomScoreSource *source);
void RoomScore_HouseCarpet(u16 *out, RoomScoreSource *source, int room);
void RoomScore_HouseWallpaper(u16 *out, RoomScoreSource *source, int room);
void RoomScore_HouseMap(RoomScoreSource *source, int room);
RoomScoreSource *RoomScore_DestructHouseSource(RoomScoreSource *source);
RoomScoreSource *RoomScore_ConstructHouseSource(RoomScoreSource *source);
void RoomScore_DestructSource(RoomScoreSource *source);
void RoomScore_ConstructSource(RoomScoreSource *source);

void RoomScore_CountFengShui(RoomScoreFengShui *edges, AcreMap *map);
int RoomScore_CountInside(int unused, AcreMap *map, u32 left, u32 right, u32 top, u32 bottom, int value);
int RoomScoreFengShui_RedEast(const RoomScoreFengShui *edges);
int RoomScoreFengShui_GreenSouth(const RoomScoreFengShui *edges);
int RoomScoreFengShui_YellowWest(const RoomScoreFengShui *edges);
void RoomScoreFengShui_Destruct(RoomScoreFengShui *edges);
int RoomScoreFengShui_Construct(RoomScoreFengShui *edges);
void RoomScoreFengShui_Clear(RoomScoreFengShui *edges);
void RoomScore_CountHouseFengShui(void);
u8 RoomScore_HouseRedEast(void);
u8 RoomScore_HouseGreenSouth(void);
u8 RoomScore_HouseYellowWest(void);
int RoomScore_HouseFengShui(void);

/* room_score_mail.c */
int RoomScoreMail_SendWelcome(void);
void RoomScoreMail_SendPrize(RoomScoreRoom *room, int total);
int RoomScoreMail_SendJudgment(RoomScoreRoom *room, int message, int total, int group, int theme);

#endif
