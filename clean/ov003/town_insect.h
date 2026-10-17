/* The insects of the town in overlay 3: the eight that live in the town, two others placed
 * by events of their own, and the one each player holds or lets go.
 *
 * An insect is a record of 0x25c bytes (TownInsect). The records lie in three tables, one
 * after the other in memory:
 *
 *   data_ov003_02260994  2 records, the "event" insects (mode 2): the second is placed by the
 *                        process for kind 0x3b when main's flag data_ov003_02260538 is set
 *                        (block_02042200.c) and handed to func_ov068_0226fe00; the first is
 *                        moved to a point by TownInsect_SetEventPoint;
 *   data_ov003_02260e4c  4 records, one per player: the insect the player holds up or lets go
 *                        (mode 3; TownInsect_HeldFromMatrix, TownInsect_LetGo...);
 *   data_ov003_022617bc  8 records, the town's insects (mode 1), drawn from the month's
 *                        insect lists (insect_draw.h) and placed on a free tile of the place
 *                        their kind lives in (InsectTables_Place).
 *
 * Other code names an insect by an id of one byte: bit 4 set for a town insect, bit 5 for an
 * event insect, and its index in the low four bits.
 *
 * A record's kind is the insect's (the item 0x12b0 + kind, 0-0x37), or one of the stand-ins
 * 0x39 (what kind 0x25 is let go as; it carries effect 0x3a), 0x3a and 0x3b (caught as kinds 0xb
 * and 0x18). Its state (TOWN_INSECT_STATE_*) picks what the process's update does with it; its
 * action (TOWN_INSECT_ACTION_*) is the step of its own behaviour, run by functions of the kind
 * from the table data_ov003_0223c2ac.
 *
 * The town insects are placed from a frame counter of the process (TownInsect_UpdateTown): every
 * 60th frame a new one of the month's lists, every 40th (without a session) one of kind 0x33,
 * every 20th (without a session) the event insect of kind 0x3b. A place is a free tile of a
 * random inner acre of the town (town_tile_mask.h) that suits the kind's place
 * (TownInsect_CountTiles). While this system is in a session, the town insects follow what the
 * session's messages say of them (TownInsect_UpdateLinked). */
#ifndef CLEAN_OV003_TOWN_INSECT_H
#define CLEAN_OV003_TOWN_INSECT_H

#include "autoload_2/matrix.h"
#include "autoload_2/vector.h"
#include "main/acre_map.h"
#include "main/animated_model.h"
#include "main/catch_sphere.h"
#include "main/field_collision.h"
#include "main/frame_ctrl.h"
#include "main/model_anim.h"
#include "main/model_pool.h"
#include "main/sound_emitter.h"
#include "types.h"

#define TOWN_INSECT_TOWN_COUNT 8
#define TOWN_INSECT_EVENT_COUNT 2
#define TOWN_INSECT_HELD_COUNT 4

/* The modes the process's functions take for each table. */
#define TOWN_INSECT_MODE_TOWN 1
#define TOWN_INSECT_MODE_EVENT 2
#define TOWN_INSECT_MODE_HELD 3

/* The bits of an insect's id. */
#define TOWN_INSECT_ID_TOWN 0x10
#define TOWN_INSECT_ID_EVENT 0x20
#define TOWN_INSECT_ID_INDEX 0x0f

/* TownInsect.kind */
#define TOWN_INSECT_NO_KIND (-1)
#define TOWN_INSECT_KIND_FAILED (-10) /* a town record kept from use after a failed placing */
#define TOWN_INSECT_KIND_GLOWING 0x39 /* kind 0x25 let go; carries effect 0x3a */
#define TOWN_INSECT_KIND_3A 0x3a      /* caught as kind 0xb */
#define TOWN_INSECT_KIND_3B 0x3b      /* caught as kind 0x18 */
#define TOWN_INSECT_KINDS 0x3c        /* the kinds the tables of data_ov003_0223c144 cover */

/* TownInsect.state */
#define TOWN_INSECT_STATE_NONE 0
#define TOWN_INSECT_STATE_1 1      /* a held insect taken from its player (func_ov003_0222ffdc) */
#define TOWN_INSECT_STATE_2 2      /* run by func_ov003_0222fa20 */
#define TOWN_INSECT_STATE_ACTIVE 3 /* drawn; run by func_ov003_0222f6b0 */
#define TOWN_INSECT_STATE_LEAVING 4

/* TownInsect.action, the steps named from what sets them. */
#define TOWN_INSECT_ACTION_END 0x0a    /* removed by the process (func_ov003_0222fe18) */
#define TOWN_INSECT_ACTION_LET_GO 0x0b /* let go from a player's hand */
#define TOWN_INSECT_ACTION_HIDDEN 0x10 /* its model's alpha set to 0 */
#define TOWN_INSECT_ACTION_11 0x11
#define TOWN_INSECT_ACTION_SHOWN 0x13 /* its model's alpha set to 0x1f; what it starts with */

/* What TownInsect_Weather says of a kind in the weather of the moment. */
#define TOWN_INSECT_WEATHER_OUT 3   /* as usual */
#define TOWN_INSECT_WEATHER_AWAY 4  /* removed when out of view */
#define TOWN_INSECT_WEATHER_QUIET 5 /* TownInsect.unk_246 cleared */

/* TownInsect.unk_254 */
#define TOWN_INSECT_BYTE254_GONE 0xff
#define TOWN_INSECT_BYTE254_NEAR 0xfe /* a player or an actor came within its reach */

/* The animated model of an insect: main's model object, its frame control and its animation
 * (the 0xb8 bytes func_02055210 constructs, AnimatedModel's first part). */
typedef struct TownInsectModel {
    u8 unk_00[0x64];
    Mtx43 matrix;            /* 0x64: where it is drawn */
    u8 unk_94[8];            /* 0x94 */
    FrameCtrl frames;        /* 0x9c */
    AnimatedModelAnim *anim; /* 0xb4 */
} TownInsectModel;

typedef struct TownInsect {
    ModelAnim anim;             /* 0x000: the vtable data_ov003_0223c0ec */
    CollisionContacts contacts; /* 0x020 */
    TownInsectModel model;      /* 0x050 */
    CatchSphere sphere;         /* 0x108 */
    ModelPoolFiles files;       /* 0x130 */
    int unk_170;                /* 0x170 */
    SoundSource source;         /* 0x174: the vtable data_0213f020 */
    Mtx43 matrix;               /* 0x180: a held insect's, from its player's hand */
    u8 unk_1b0[0x1c8 - 0x1b0];
    Vec3 start;  /* 0x1c8: the position when it was placed */
    Vec3 target; /* 0x1d4: a linked insect's point from the session */
    u8 unk_1e0[0x1ec - 0x1e0];
    u8 unk_1ec[2][0xc]; /* 0x1ec: two objects of func_020012e8 */
    Vec3 position;      /* 0x204 */
    Vec3 scale;         /* 0x210 */
    int unk_21c;        /* 0x21c: the snowball it was placed by (kind 0x23); whether effect 0x3a started */
    int unk_220;        /* 0x220 */
    fx32 reach;         /* 0x224: how near a player or actor comes before unk_254 is NEAR */
    int unk_228;        /* 0x228 */
    int effect;         /* 0x22c: the handle of effect 0x3a, -1 for none */
    u16 slot;           /* 0x230: its entry of a model pool */
    s16 timer;          /* 0x232 */
    s16 unk_234;        /* 0x234 */
    u8 unk_236[2];
    s16 angle_x; /* 0x238 */
    s16 angle_y; /* 0x23a */
    s16 angle_z; /* 0x23c */
    u8 unk_23e[0x242 - 0x23e];
    s16 frames_left; /* 0x242: counted up in TOWN_INSECT_STATE_LEAVING */
    u8 unk_244[2];
    u8 unk_246; /* 0x246: cleared in TOWN_INSECT_WEATHER_QUIET, else 1 */
    u8 unk_247;
    u8 used;    /* 0x248 */
    u8 in_view; /* 0x249: within the box around the camera's point */
    u8 unk_24a;
    u8 unk_24b;
    u8 unk_24c;
    s8 kind; /* 0x24d */
    u8 unk_24e;
    u8 counter; /* 0x24f: 0-0x50 (TownInsect_StepCounter) */
    u8 state;   /* 0x250: TOWN_INSECT_STATE_* */
    u8 action;  /* 0x251: TOWN_INSECT_ACTION_* */
    u8 unk_252;
    u8 unk_253;
    u8 unk_254; /* 0x254: TOWN_INSECT_BYTE254_* or a byte of the session's messages */
    u8 unk_255;
    u8 unk_256[2];
    u8 players_near; /* 0x258: a bit for each player whose box holds it */
    u8 unk_259[3];
} TownInsect;

/* What the game keeps for each kind (data_ov003_0223c144, TOWN_INSECT_KINDS entries). */
typedef struct TownInsectKindInfo {
    u16 unk_0;
    u16 size; /* the shadow's size and the radius of its collisions */
    u16 unk_4;
} TownInsectKindInfo;

/* The process the insects belong to, the parts read here. */
typedef struct TownInsectProcess {
    u8 unk_00[0x50];
    ModelPool pools[3]; /* 0x50 */
    void *blocks[2];    /* 0x98: freed (Heap_FreeCurrent) with the event insects */
} TownInsectProcess;

/* A mask of the 4 by 4 inner acres (town_tile_mask.h): 16 rows of 16 tiles each. */
typedef struct TownInsectMask {
    u16 rows[0x100];
} TownInsectMask;

int TownInsect_CountTiles(u16 *mask, int kind, int *acre_x, int *acre_z, AcreMap *map, int place);
void TownInsect_UnmarkSceneActors(TownInsectMask *mask);
void TownInsect_FillMask(TownInsectMask *mask);
int TownInsect_PickTile(TownInsect *insect, TownInsectMask *mask, int kind, int place);
void TownInsect_CopyMask(void *dst, int place);
ModelAnim *TownInsectAnim_DestructDelete(ModelAnim *anim);
ModelAnim *TownInsectAnim_Destruct(ModelAnim *anim);
ModelAnim *TownInsectAnim_Construct(ModelAnim *anim);
int TownInsect_Weather(int kind, int falling);
void TownInsect_ClearFailed(void);
int TownInsect_DrawKind(int month, int time_slot, u8 *kind);
int TownInsect_KindAllowed(int kind);
int TownInsect_SpecialKind(u8 *kind, u8 *place, int town);
void TownInsect_SetAnimSpeed(TownInsect *insect, unsigned long speed);
TownInsect *TownInsect_Destruct(TownInsect *insect);
TownInsect *TownInsect_Construct(TownInsect *insect);
void TownInsect_StepCounter(TownInsect *insect);
int TownInsect_TimeSlot(void);
int TownInsect_DrawKindNow(s8 *kind);
int TownInsect_OnPlayersAheadTile(const Vec3 *point);
int TownInsect_EventShown(void);
int TownInsect_Hide(int id);
int TownInsect_HeldFromMatrix(int player, short *scale, Mtx43 *matrix, int end);
void TownInsect_SetEventPoint(int *point);
int TownInsect_PlaceNew(TownInsectProcess *process, int mode, s8 kind, int place);
int TownInsect_Place(TownInsectProcess *process, int kind, int place, int mode);
void TownInsect_SetFlag54c(void);
void TownInsect_UpdateView(TownInsectProcess *process, int mode);
void TownInsect_UpdatePlayerView(TownInsectProcess *process, int mode, int player, int x, int z);
int TownInsect_RemoveAll(TownInsectProcess *process);
int TownInsect_DrawAll(TownInsectProcess *process);
void TownInsect_SetMatrix(int unused, TownInsect *insect, int held);
int TownInsect_HasShadow(int unused, TownInsect *insect);
void TownInsect_Draw(void *unused, TownInsect *insect);
void TownInsect_SetScale(TownInsect *insect, int percent);
int TownInsect_Catch(u8 id);
void TownInsect_Show(int id);
u8 TownInsect_Release(int id, u8 unused);
int TownInsect_Caught(u8 id);
void TownInsect_EndHeld(u8 player, int send);
void TownInsect_HideById(int id);
int TownInsect_KindFlees(int kind);
void TownInsect_Startle(int id);
void TownInsect_TakeHeld(int kind, int player);
Vec3 *TownInsect_HeldPosition(int player);
int TownInsect_KindHighUp(int unused, int kind);
int TownInsect_DrawTable(void *unused, TownInsect *insects, int count);
u8 TownInsect_HeldState(int player);
void TownInsect_LetGo(int player, int angle);
int TownInsect_CanBeCaught(int unused, TownInsect *insect);
void TownInsect_UpdateHeld(TownInsectProcess *process);
void TownInsect_UpdateEvent(TownInsectProcess *process);
int TownInsect_OnItsTile(int unused, TownInsect *insect);
int TownInsect_CheckTarget(int unused, TownInsect *insect, int kind, int x, int z);
void TownInsect_UpdateLinked(TownInsectProcess *process);
void TownInsect_UpdateTown(TownInsectProcess *process);
int TownInsect_GetPosition(Vec3 *position, int id);
int TownInsect_KindHighPlace(int id);
int TownInsect_Byte254Reached(u8 *reached, int id);
void TownInsect_CheckNear(int unused, TownInsect *insect);

#endif
