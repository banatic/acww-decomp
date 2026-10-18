/* The items that wash up on the town's beach (town_beach.h). */
#include "town_beach.h"

#include "bottle_mail.h"
#include "calendar.h"
#include "clean.h"
#include "scene_query.h"
#include "session.h"
#include "main_random.h"
#include "session_players.h"
#include "town_acre_count.h"
#include "town_place.h"

extern TownDay data_021c779c;
extern NetSession *data_020ccf94;
/* The weights (out of 100) of the beach items 0x1554-0x155c. */
extern const int data_020cac9c[TOWN_BEACH_ITEM_KINDS];

/* A player's actor, as far as it is read here. */
typedef struct TownBeachActor {
    u8 unk_00[0x5c];
    int x; /* 0x5c */
    int y;
    int z; /* 0x64 */
} TownBeachActor;

#define TOWN_BEACH_THIS_PLAYER 4
#define TOWN_BEACH_PLAYERS 4
#define TOWN_BEACH_ACRE_SHIFT 17 /* a position's acre (in the map) */

static AcreMap *TownBeach_Map(void)
{
    return (AcreMap *) (uintptr_t) AcreMap_Town();
}

/* func_02046ebc: the bottle put on the beach, trying each beach acre from one drawn at random;
 * whether it was. */
int TownBeach_PutBottle(int town)
{
    u32 acre_x = MainRandom_Below(TOWN_BEACH_ACRE_ROW);
    AcreMap *map = TownBeach_Map();
    for (int i = 0; i < 4; i++) {
        if (TownPlace_PutInAcre((void *) (uintptr_t) town, map, (int) acre_x + 1, TOWN_BEACH_ACRE_ROW, BOTTLE_ITEM,
                                func_02048e34, 0) != 0) {
            return 1;
        }
        acre_x = (acre_x + 1) & 3;
    }
    return 0;
}
CLEAN_AS(func_02046ebc, TownBeach_PutBottle)

/* func_02046f14: each beach acre filled up to two items (an item that finds no free tile is not
 * tried again), and the time noted. */
void TownBeach_Fill(TownDay *town, AcreMap *map)
{
    int wide = map->acres_wide - 2;
    for (int acre_x = 0; acre_x < wide; acre_x++) {
        int missing = TOWN_BEACH_FILL - data_021c779c.acres.acres[acre_x][TOWN_DAY_BEACH_ROW].beach_items;
        for (; missing > 0; missing--) {
            u16 item = (u16) TownBeach_DrawItem(town);
            TownPlace_PutInAcre(town, map, acre_x + 1, TOWN_BEACH_ACRE_ROW, item, func_02048e34, 0);
        }
    }
    Calendar_Now(&data_021c779c.beach_time);
}
CLEAN_AS(func_02046f14, TownBeach_Fill)

/* func_02046f7c: the beach looked at (by the host when linked). */
void TownBeach_Update(int town)
{
    if (Session_IsLinked(data_020ccf94)) {
        TownBeach_UpdateLinked(town);
    } else {
        TownBeach_UpdateAlone(town);
    }
}
CLEAN_AS(func_02046f7c, TownBeach_Update)

/* Whether the time is a new one, with the minutes ending in 3. */
static int TownBeach_IsWashTime(Time now)
{
    const Time *last = &data_021c779c.beach_time;
    if (now.minute == last->minute && now.hour == last->hour) {
        return 0;
    }
    return now.minute % 10 == TOWN_BEACH_MINUTE_DIGIT;
}

/* func_02046fa4: on the host, at a new time with the minutes ending in 3, an item washes up on
 * a beach acre drawn at random unless one of the players in scene 0 or 0x31 is on the beach. */
void TownBeach_UpdateLinked(int town)
{
    struct {
        u8 scene; /* func_02096614's answer */
        u8 unk_01;
        Time now;
    } at;
    if (Session_IsLocalSlot(data_020ccf94, 0) == 0) {
        return;
    }
    Calendar_Now(&at.now);
    if (!TownBeach_IsWashTime(at.now)) {
        return;
    }
    int on_beach = 0;
    for (int player = 0; player < TOWN_BEACH_PLAYERS; player++) {
        int x[2];
        int z;
        if (SessionPlayers_ScenePoint(&at.scene, x, &z, -1, player) == 0) {
            continue;
        }
        if (SceneQuery_Is0(at.scene) == 0 && SceneQuery_Is31(at.scene) == 0) {
            continue;
        }
        if ((z >> TOWN_BEACH_ACRE_SHIFT) == TOWN_BEACH_ACRE_ROW) {
            on_beach = 1;
            break;
        }
    }
    if (!on_beach) {
        AcreMap *map = TownBeach_Map();
        int acre_x = (int) MainRandom_Below(TOWN_BEACH_ACRE_ROW);
        TownBeach_WashUp(town, map, acre_x);
    }
    data_021c779c.beach_time = at.now;
}
CLEAN_AS(func_02046fa4, TownBeach_UpdateLinked)

/* func_02047050: at a new time with the minutes ending in 3, an item washes up on a beach acre
 * drawn at random, unless this console's player stands on that acre. Nothing (the time still
 * noted) when the player has no actor. */
void TownBeach_UpdateAlone(int town)
{
    Time now;
    Calendar_Now(&now);
    if (!TownBeach_IsWashTime(now)) {
        return;
    }
    const TownBeachActor *actor = SessionPlayers_ActorOf(TOWN_BEACH_THIS_PLAYER);
    if (actor != NULL) {
        AcreMap *map = TownBeach_Map();
        int acre_x = (int) MainRandom_Below(TOWN_BEACH_ACRE_ROW);
        int on_x = actor->x >> TOWN_BEACH_ACRE_SHIFT;
        int on_z = actor->z >> TOWN_BEACH_ACRE_SHIFT;
        if (on_z != TOWN_BEACH_ACRE_ROW || on_x != acre_x + 1) {
            TownBeach_WashUp(town, map, acre_x);
        }
    }
    data_021c779c.beach_time = now;
}
CLEAN_AS(func_02047050, TownBeach_UpdateAlone)

/* func_020470c0: beach acre `acre_x` (from 0) counted again, and an item put there while it
 * holds fewer than four. */
void TownBeach_WashUp(int town, AcreMap *map, int acre_x)
{
    TownAcreCount_CountInner(&data_021c779c.acres, map, acre_x, 3);
    if (data_021c779c.acres.acres[acre_x][TOWN_DAY_BEACH_ROW].beach_items < TOWN_BEACH_MOST) {
        u16 item = (u16) TownBeach_DrawItem((TownDay *) (uintptr_t) town);
        TownPlace_PutInAcre((void *) (uintptr_t) town, map, acre_x + 1, TOWN_BEACH_ACRE_ROW, item, func_02048e34, 0);
    }
}
CLEAN_AS(func_020470c0, TownBeach_WashUp)

/* func_02047114: a beach item drawn by the weights of data_020cac9c. */
int TownBeach_DrawItem(TownDay *town)
{
    (void) town;
    int left = (int) MainRandom_Below(100);
    int item = TOWN_BEACH_FIRST_ITEM;
    for (int i = 0; i < TOWN_BEACH_ITEM_KINDS; i++) {
        left -= data_020cac9c[i];
        if (left < 0) {
            break;
        }
        item++;
    }
    return (u16) item;
}
CLEAN_AS(func_02047114, TownBeach_DrawItem)
