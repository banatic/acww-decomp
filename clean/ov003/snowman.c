/* The snowballs and snowmen: how a snowman talks, then how a ball rolls, grows, is pushed and
 * is built into a snowman (snowman.h). */
#include "snowman.h"

#include <stdint.h>
#include <string.h>

#include "autoload_2/approach.h"            /* Approach_DivideS16, Math_AbsDiff16, Approach_EaseS32 */
#include "autoload_2/fx_math.h"             /* Math_Atan2 */
#include "autoload_2/heap.h"                /* Heap_Alloc, Heap_Free */
#include "autoload_2/matrix.h"              /* Mtx43_Translation, Mtx43_RotateX */
#include "autoload_2/sound_emitter_class.h" /* SoundEmitterClass_ConstructBaseB */
#include "autoload_2/vector.h"              /* Vec_DistanceXZ */
#include "clean.h"
#include "main/sound_emitter.h" /* SoundEmitter_PlayB */
#include "main/text_label.h"    /* TextVtable */
#include "ov004/member_pointer.h"
#include "itcm/vector.h"
#include "main/acre_tile.h"
#include "main/actor_table.h"
#include "main/collision_query.h"
#include "main/event_queue.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/globe.h"
#include "main/item_code.h"
#include "main/main_random.h"
#include "main/map_code.h"
#include "main/message_reader.h"
#include "main/message_receiver.h"
#include "main/message_texts.h"
#include "main/model_object.h"
#include "main/quaternion.h"
#include "main/scene_object_base.h"
#include "main/scene_query.h"
#include "main/session_players.h"
#include "main/shadow.h"
#include "main/snowmen.h"
#include "main/talk_receiver.h"
#include "main/town_item_lists.h"
#include "main/unit_type_info.h"

static_assert(offsetof(Snowman, position) == 0x5c, "position");
static_assert(offsetof(Snowman, receiver_vtable) == 0xec, "receiver");
static_assert(offsetof(Snowman, message) == 0x10a, "receiver byte 0x1e");
static_assert(offsetof(Snowman, link) == 0x12c, "link");
static_assert(offsetof(Snowman, flags) == 0x378, "flags");
static_assert(offsetof(Snowman, scene_state) == 0x39c, "first state");
static_assert(offsetof(Snowman, talk_state) == 0x3a0, "talk state");
static_assert(offsetof(SnowmanVisitor, position) == 0x5c, "visitor position");
static_assert(offsetof(SnowmanVisitor, yaw) == 0x8e, "visitor yaw");
static_assert(offsetof(Snowman, index) == 0x08, "index");
static_assert(offsetof(Snowman, last_position) == 0x68, "last position");
static_assert(offsetof(Snowman, ball_model) == 0x134, "ball model");
static_assert(offsetof(Snowman, ball_model.matrix) == 0x198, "ball model matrix");
static_assert(offsetof(Snowman, face_model) == 0x1d0, "face model");
static_assert(offsetof(Snowman, face_model.matrix) == 0x234, "face model matrix");
static_assert(offsetof(Snowman, size) == 0x26c, "size");
static_assert(offsetof(Snowman, last_size) == 0x270, "last size");
static_assert(offsetof(Snowman, collider) == 0x274, "collider");
static_assert(offsetof(Snowman, collisions) == 0x284, "collisions");
static_assert(offsetof(Snowman, body) == 0x2a4, "body");
static_assert(offsetof(Snowman, body.body.push_x) == 0x2b4, "push x");
static_assert(offsetof(Snowman, body.body.push_z) == 0x2bc, "push z");
static_assert(offsetof(Snowman, body.body.touched) == 0x2e0, "touched");
static_assert(offsetof(Snowman, body.body.hit) == 0x2e8, "hit");
static_assert(offsetof(Snowman, body.body.weight) == 0x2ec, "weight");
static_assert(offsetof(Snowman, body.rolling.velocity_x) == 0x2f0, "velocity");
static_assert(offsetof(Snowman, body.rolling.rotation) == 0x2f8, "rotation");
static_assert(offsetof(Snowman, body.rolling.model_offset) == 0x308, "model offset");
static_assert(offsetof(Snowman, body.rolling.start_position) == 0x31c, "start position");
static_assert(offsetof(Snowman, sound) == 0x328, "sound");
static_assert(offsetof(Snowman, last_collisions) == 0x369, "last collisions");
static_assert(offsetof(Snowman, rolling_sound) == 0x36a, "rolling sound");
static_assert(offsetof(Snowman, roll_factor) == 0x374, "roll factor");
static_assert(offsetof(Snowman, heading) == 0x394, "heading");
static_assert(offsetof(Snowman, item_under) == 0x39a, "item under");
static_assert(sizeof(Snowman) == 0x3a4, "size of the class");
static_assert(sizeof(SnowmanModel) == 0x9c, "model");
static_assert(sizeof(SnowmanSaved) == 0x10, "saved ball");

#define SNOWMAN_RECEIVER_OFFSET 0xec

/* The scene events of vtable slot 0x4c. */
#define SNOWMAN_EVENT_TALK 0
#define SNOWMAN_EVENT_TALK_AGAIN 1
#define SNOWMAN_EVENT_IDLE 8

/* The speaker's name: message 0x26 of the archive "st_spnpc_name". */
#define SNOWMAN_NAME_MESSAGE 0x26

/* "sp_npc_snowman", the receiver's name, and "st_spnpc_name". */
extern const char data_ov003_0223838c[];
extern const char data_ov003_0223839c[];

/* The talk machine's tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov003_0223c61c;
extern MemberPointer data_ov003_0223c63c[SNOWMAN_TALK_STATES];
extern const MemberPointer data_ov003_022381a8, data_ov003_02238168, data_ov003_022381f0;
extern u32 data_ov003_0223c620;
extern MemberPointer data_ov003_0223c624[SNOWMAN_TALK_STATES];
extern const MemberPointer data_ov003_02238198, data_ov003_022381e8, data_ov003_02238180;

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_MulFunc(fx32 a, fx32 b);

/* A text label of main (vtable data_020e51d0, 0x118 bytes): built by MessageText256_Construct,
 * destroyed by MessageText256_Destruct; MessageReader_LoadMessage loads message `*number` of a
 * named archive into it. */
typedef struct SnowmanNameText {
    const TextVtable *vtable;
    u8 unk_04[0x114];
} SnowmanNameText;

typedef const char *(*SnowmanTextBuffer)(void *text);

/* The receiver part as C++ converts a pointer to the snowman to it: NULL stays NULL. */
static void *snowman_receiver(Snowman *snowman)
{
    return snowman != NULL ? (u8 *) snowman + SNOWMAN_RECEIVER_OFFSET : NULL;
}

/* func_ov003_02219e64 (update of SNOWMAN_TALK_END): once the link has closed, hands the receiver
 * back (SceneObjectBase_ReleaseReceiver) and lets the scene go on (func_0203e020). Its state stays
 * SNOWMAN_TALK_END until the scene sets another. */
void SnowmanTalk_UpdateEnd(Snowman *snowman)
{
    if (snowman->link != NULL && snowman->link->open == 0) {
        SceneObjectBase_ReleaseReceiver((SceneObjectBase *) snowman, snowman_receiver(snowman));
        EventQueue_FinishObjectEvent(snowman);
    }
}
CLEAN_AS(func_ov003_02219e64, SnowmanTalk_UpdateEnd)

/* func_ov003_02219e94 (entry of SNOWMAN_TALK_END) */
int SnowmanTalk_EnterEnd(void)
{
    return 1;
}
CLEAN_AS(func_ov003_02219e94, SnowmanTalk_EnterEnd)

/* func_ov003_02219e98 (update of SNOWMAN_TALK_OPEN): on once the link has opened. */
void SnowmanTalk_UpdateOpen(Snowman *snowman)
{
    if (snowman->link != NULL && snowman->link->open != 0) {
        SnowmanTalk_SetState(snowman, SNOWMAN_TALK_END);
    }
}
CLEAN_AS(func_ov003_02219e98, SnowmanTalk_UpdateOpen)

/* func_ov003_02219ebc (entry of SNOWMAN_TALK_OPEN): takes the receiver
 * (SceneObjectBase_TakeReceiver), names it "sp_npc_snowman" and gives it one of the three messages
 * of the snowman's kind, drawn at random: 0-0xb while SNOWMAN_FLAG_FIRST_TALK is set, else
 * 0xc-0x17. The link's request is raised, the receiver's speaker name is set from "st_spnpc_name",
 * and the flag is cleared.
 * REQUIRES: the receiver has a link once SceneObjectBase_TakeReceiver has taken it. */
int SnowmanTalk_EnterOpen(Snowman *snowman)
{
    SceneObjectBase_TakeReceiver((SceneObjectBase *) snowman, snowman_receiver(snowman));
    int kind = (snowman->flags >> SNOWMAN_KIND_SHIFT) & 3;
    int message;
    if (snowman->flags & SNOWMAN_FLAG_FIRST_TALK) {
        message = MainRandom_Below(3) + kind * 3;
    } else {
        message = MainRandom_Below(3) + kind * 3 + 0xc;
    }
    MessageReceiver_SetName((MessageReceiver *) &snowman->receiver_vtable, data_ov003_0223838c);
    snowman->message = (u8) message;
    snowman->link->requested = 1;

    char number = SNOWMAN_NAME_MESSAGE;
    SnowmanNameText name;
    MessageText256_Construct((MessageText256 *) &name);
    MessageReader_LoadMessage(&name, (unsigned char *) &number, data_ov003_0223839c);
    const char *text = ((SnowmanTextBuffer) (uintptr_t) name.vtable->buffer)(&name);
    TalkReceiver_SetSpeaker((TalkReceiver *) &snowman->receiver_vtable, text, 0);
    snowman->flags &= (u16) ~SNOWMAN_FLAG_FIRST_TALK;
    MessageText256_Destruct((MessageText256 *) &name);
    return 1;
}
CLEAN_AS(func_ov003_02219ebc, SnowmanTalk_EnterOpen)

/* func_ov003_02219f80 (update of SNOWMAN_TALK_IDLE) */
void SnowmanTalk_UpdateIdle(Snowman *snowman)
{
    (void) snowman;
}
CLEAN_AS(func_ov003_02219f80, SnowmanTalk_UpdateIdle)

/* func_ov003_02219f84 (entry of SNOWMAN_TALK_IDLE) */
int SnowmanTalk_EnterIdle(void)
{
    return 1;
}
CLEAN_AS(func_ov003_02219f84, SnowmanTalk_EnterIdle)

/* _ZN18Obj_ov003_022382ac19func_ov003_02219f88Ev: the talk state's update, through its table.
 * REQUIRES: the state is not negative (SnowmanTalk_SetState only sets 0 to 2). */
void SnowmanTalk_Update(Snowman *snowman)
{
    static const MemberPointer *const updates[SNOWMAN_TALK_STATES] = {
        &data_ov003_022381a8, /* SnowmanTalk_UpdateIdle */
        &data_ov003_02238168, /* SnowmanTalk_UpdateOpen */
        &data_ov003_022381f0, /* SnowmanTalk_UpdateEnd */
    };
    MemberTable_InitOnce(&data_ov003_0223c61c, data_ov003_0223c63c, updates, SNOWMAN_TALK_STATES);
    if (snowman->talk_state < SNOWMAN_TALK_STATES) {
        MemberPointer_CallVoid(&data_ov003_0223c63c[snowman->talk_state], snowman);
    }
}
CLEAN_AS(_ZN18Obj_ov003_022382ac19func_ov003_02219f88Ev, SnowmanTalk_Update)

/* func_ov003_0221a004: enters talk state `state` if its entry (through a table) agrees; whether
 * it did. States 3 and above do not exist.
 * REQUIRES: `state` is not negative. */
int SnowmanTalk_SetState(Snowman *snowman, int state)
{
    static const MemberPointer *const entries[SNOWMAN_TALK_STATES] = {
        &data_ov003_02238198, /* SnowmanTalk_EnterIdle */
        &data_ov003_022381e8, /* SnowmanTalk_EnterOpen */
        &data_ov003_02238180, /* SnowmanTalk_EnterEnd */
    };
    MemberTable_InitOnce(&data_ov003_0223c620, data_ov003_0223c624, entries, SNOWMAN_TALK_STATES);
    if (state < SNOWMAN_TALK_STATES && MemberPointer_CallInt(&data_ov003_0223c624[state], snowman) != 0) {
        snowman->talk_state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_0221a004, SnowmanTalk_SetState)

/* func_ov003_0221a090 (vtable slot 0x4c): the scene's events: 0 and 1 start a talk (1 then
 * clears SNOWMAN_FLAG_FIRST_TALK, which the talk has already cleared when it started), 8 makes
 * the snowman idle; others do nothing. */
void SnowmanTalk_OnSceneEvent(Snowman *snowman, int event)
{
    switch (event) {
        case SNOWMAN_EVENT_TALK:
            SnowmanTalk_SetState(snowman, SNOWMAN_TALK_OPEN);
            break;
        case SNOWMAN_EVENT_TALK_AGAIN:
            SnowmanTalk_SetState(snowman, SNOWMAN_TALK_OPEN);
            snowman->flags &= (u16) ~SNOWMAN_FLAG_FIRST_TALK;
            break;
        case SNOWMAN_EVENT_IDLE:
            SnowmanTalk_SetState(snowman, SNOWMAN_TALK_IDLE);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_0221a090, SnowmanTalk_OnSceneEvent)

/* func_ov003_0221a0d4 (vtable slot 0x48): whether `visitor` stands closer than 2.5 (2 times
 * 500/400, computed with FX_Div and FX_MulFunc) to the snowman across the ground while the first
 * machine is in state 0xb. func_0203edd0 runs on the snowman first in any case. */
int SnowmanTalk_CanTalkTo(Snowman *snowman, const SnowmanVisitor *visitor)
{
    SceneObjectBase_ClearApproach((SceneObjectBase *) snowman);
    fx32 reach = FX_MulFunc(0x2000, FX_Div(0x7d000, 0x64000));
    return visitor != NULL && Vec_DistanceXZ(&visitor->position, &snowman->position) < reach &&
           snowman->scene_state == SNOWMAN_STATE_HEAD;
}
CLEAN_AS(func_ov003_0221a0d4, SnowmanTalk_CanTalkTo)

/* ---- The ball */

/* The tables of the first machine (member_pointer.h): their guards, the tables and their
 * constants. */
extern u32 data_ov003_0223c614;
extern MemberPointer data_ov003_0223c6c4[SNOWMAN_STATES];
extern const MemberPointer data_ov003_02238218, data_ov003_02238210, data_ov003_022381a0, data_ov003_02238200,
    data_ov003_022381f8, data_ov003_02238170, data_ov003_02238178, data_ov003_022381e0, data_ov003_022381d8,
    data_ov003_022381d0, data_ov003_022381b8, data_ov003_022381c8, data_ov003_02238220, data_ov003_022381b0;
extern u32 data_ov003_0223c618;
extern MemberPointer data_ov003_0223c654[SNOWMAN_STATES];
extern const MemberPointer data_ov003_022381c0, data_ov003_02238228, data_ov003_02238190, data_ov003_02238188,
    data_ov003_02238238, data_ov003_02238270, data_ov003_02238268, data_ov003_02238260, data_ov003_02238258,
    data_ov003_02238250, data_ov003_02238248, data_ov003_02238240, data_ov003_02238208, data_ov003_02238230;

/* The vtables: the class's, its receiver part's and its body's. */
extern const u8 data_ov003_022382ac[];
extern const u8 data_ov003_02238314[];
extern const u8 data_ov003_02238280[];
/* "/snowman/snowball1.nsbmd" and "/snowman/snow_face.nsbmd" */
extern const char data_ov003_022383ac[];
extern const char data_ov003_022383c8[];

/* The model tags: "SNW0" and "SNW1". */
#define SNOWMAN_TAG_BALL 0x534e5730
#define SNOWMAN_TAG_FACE 0x534e5731

/* The quaternion that does not rotate. */
extern const SnowmanQuat data_020d1a10;
/* The town's map (func_0204f5e0 finds the item on a tile of it). */
extern void *data_021c80bc;
/* The three snowmen main keeps, six bytes each (func_020b0594, func_020b0540). */
extern u8 data_021f3b56[];
/* Counts frames. */
extern int data_021fbdd0;
/* The camera, a point of it, and how far from that point a ball is still drawn. */
extern int data_021c67a4;
extern const Vec3 data_021c67d0;
extern int data_020ca0ec;
/* The heap the balls are allocated from. */
extern Heap *data_021c9b24;
extern const s16 FX_SinCosTable_[];

/* The eight tiles around one, as steps along x and z. */
typedef struct SnowmanTileStep {
    s16 x;
    s16 z;
} SnowmanTileStep;
extern const SnowmanTileStep data_ov003_0223660c[8];

/* What func_02034270 tells of the ground at a point; func_0203423c releases it. */
typedef struct SnowmanGround {
    u8 unk_00[0x34];
    int kind; /* SNOWMAN_GROUND_SNOW where a ball grows */
    u8 unk_38[0x40 - 0x38];
} SnowmanGround;
#define SNOWMAN_GROUND_SNOW 3

/* What func_0208a020 gives for the body: something touching it, with a value at 0x98. */
typedef struct SnowmanContact {
    u8 unk_00[0x98];
    int unk_98; /* above SNOWMAN_KNOCK_LIMIT knocks a snowman's part */
} SnowmanContact;
#define SNOWMAN_KNOCK_LIMIT 0x666

#define SNOWMAN_PLAYER 4 /* the actor func_020961a8 is asked for */
#define SNOWMAN_NO_ITEM 0xfff1
#define SNOWMAN_SIZE_MIN 0x800
#define SNOWMAN_SIZE_PUSHABLE 0xa00 /* smaller balls are not pushed and make sound 0x81c */
#define SNOWMAN_SIZE_MAX 0x1400

extern fx32 VEC_Mag(const Vec3 *v);
extern void MTX_Concat43(const Mtx43 *a, const Mtx43 *b, Mtx43 *ab);

/* An arithmetic shift right, for negative values too. */
static int shift_right(int value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

static fx32 sine(int angle)
{
    return FX_SinCosTable_[2 * ((u16) angle >> 4)];
}

static fx32 cosine(int angle)
{
    return FX_SinCosTable_[2 * ((u16) angle >> 4) + 1];
}

static SoundEmitter *snowman_sound(Snowman *snowman)
{
    return (SoundEmitter *) (void *) snowman->sound;
}

/* The item on a tile of the map, in layer 0. */
static u16 *item_on_tile(void *map, int x, int z)
{
    return AcreTile_ItemInAcre(map, shift_right(x, 4), shift_right(z, 4), x & 0xf, z & 0xf, 0);
}

/* Both machines idle: the ball is loose and nobody talks to it. */
static int is_idle_loose(const Snowman *snowman)
{
    return snowman->talk_state == SNOWMAN_TALK_IDLE && snowman->scene_state == SNOWMAN_STATE_LOOSE;
}

/* func_ov003_0221a128 (update of state 0xb, a head): its size is kept as the last; something
 * touching it with more than SNOWMAN_KNOCK_LIMIT knocks it (Snowman_Knock, which does nothing
 * in this state); otherwise, while SNOWMAN_FLAG_FIRST_TALK is set, it asks the scene for an
 * event (func_0203e0a8), which starts a talk. */
void Snowman_UpdateHead(Snowman *snowman)
{
    snowman->last_size = snowman->size;
    if (snowman->body.body.touched) {
        const SnowmanContact *contact =
            (const SnowmanContact *) (uintptr_t) FieldBody_TouchedActor((FieldBody *) &snowman->body.body);
        if (contact != NULL && contact->unk_98 > SNOWMAN_KNOCK_LIMIT) {
            Snowman_Knock(snowman, 1);
            return;
        }
    }
    if (snowman->flags & SNOWMAN_FLAG_FIRST_TALK) {
        EventQueue_RequestKind6(snowman, 0);
    }
}
CLEAN_AS(func_ov003_0221a128, Snowman_UpdateHead)

/* func_ov003_0221a190 (entry of state 0xb): collisions with layer 0 and contact flag 2, and no
 * rotation. */
int Snowman_EnterHead(Snowman *snowman)
{
    snowman->flags &= (u16) ~SNOWMAN_FLAG_LAYER_B;
    snowman->flags |= SNOWMAN_FLAG_CONTACT_2;
    snowman->body.rolling.rotation = data_020d1a10;
    return 1;
}
CLEAN_AS(func_ov003_0221a190, Snowman_EnterHead)

/* func_ov003_0221a1dc (update of state 9, a body): as a head's, without the talk. */
void Snowman_UpdateBody(Snowman *snowman)
{
    snowman->last_size = snowman->size;
    if (snowman->body.body.touched) {
        const SnowmanContact *contact =
            (const SnowmanContact *) (uintptr_t) FieldBody_TouchedActor((FieldBody *) &snowman->body.body);
        if (contact != NULL && contact->unk_98 > SNOWMAN_KNOCK_LIMIT) {
            Snowman_Knock(snowman, 1);
        }
    }
}
CLEAN_AS(func_ov003_0221a1dc, Snowman_UpdateBody)

/* func_ov003_0221a228 (entry of state 9): collisions with layer 0 and contact flag 2; the
 * rotation stays. */
int Snowman_EnterBody(Snowman *snowman)
{
    snowman->flags &= (u16) ~SNOWMAN_FLAG_LAYER_B;
    snowman->flags |= SNOWMAN_FLAG_CONTACT_2;
    return 1;
}
CLEAN_AS(func_ov003_0221a228, Snowman_EnterBody)

/* _ZN18Obj_ov003_022382ac19func_ov003_0221a244Ev: the first machine's update, through its
 * table. REQUIRES: the state is not negative (Snowman_SetState only sets 0 to 13). */
void Snowman_UpdateState(Snowman *snowman)
{
    static const MemberPointer *const updates[SNOWMAN_STATES] = {
        &data_ov003_02238218, /* func_ov068_0226f854 */
        &data_ov003_02238210, /* func_ov068_0226f648 */
        &data_ov003_022381a0, /* func_ov068_0226f504 */
        &data_ov003_02238200, /* func_ov068_0226f49c */
        &data_ov003_022381f8, /* func_ov068_0226f3b0 */
        &data_ov003_02238170, /* func_ov068_0226f298 */
        &data_ov003_02238178, /* func_ov068_0226f178 */
        &data_ov003_022381e0, /* func_ov068_0226effc */
        &data_ov003_022381d8, /* func_ov068_0226ee54 */
        &data_ov003_022381d0, /* Snowman_UpdateBody */
        &data_ov003_022381b8, /* func_ov068_0226ed9c */
        &data_ov003_022381c8, /* Snowman_UpdateHead */
        &data_ov003_02238220, /* func_ov068_0226eca8 */
        &data_ov003_022381b0, /* func_ov068_0226ebc4 */
    };
    MemberTable_InitOnce(&data_ov003_0223c614, data_ov003_0223c6c4, updates, SNOWMAN_STATES);
    if (snowman->scene_state < SNOWMAN_STATES) {
        MemberPointer_CallVoid(&data_ov003_0223c6c4[snowman->scene_state], snowman);
    }
}
CLEAN_AS(_ZN18Obj_ov003_022382ac19func_ov003_0221a244Ev, Snowman_UpdateState)

/* func_ov003_0221a35c: enters state `state` of the first machine if its entry (through a table)
 * agrees; whether it did. States 14 and above do not exist.
 * REQUIRES: `state` is not negative. */
int Snowman_SetState(Snowman *snowman, int state)
{
    static const MemberPointer *const entries[SNOWMAN_STATES] = {
        &data_ov003_022381c0, /* func_ov068_0226fc2c */
        &data_ov003_02238228, /* func_ov068_0226f730 */
        &data_ov003_02238190, /* func_ov068_0226f5cc */
        &data_ov003_02238188, /* func_ov068_0226f4b4 */
        &data_ov003_02238238, /* func_ov068_0226f444 */
        &data_ov003_02238270, /* func_ov068_0226f348 */
        &data_ov003_02238268, /* func_ov068_0226f230 */
        &data_ov003_02238260, /* func_ov068_0226f0e0 */
        &data_ov003_02238258, /* func_ov068_0226ef04 */
        &data_ov003_02238250, /* Snowman_EnterBody */
        &data_ov003_02238248, /* func_ov068_0226ee0c */
        &data_ov003_02238240, /* Snowman_EnterHead */
        &data_ov003_02238208, /* func_ov068_0226ed38 */
        &data_ov003_02238230, /* func_ov068_0226ec54 */
    };
    MemberTable_InitOnce(&data_ov003_0223c618, data_ov003_0223c654, entries, SNOWMAN_STATES);
    if (state < SNOWMAN_STATES && MemberPointer_CallInt(&data_ov003_0223c654[state], snowman) != 0) {
        snowman->scene_state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_0221a35c, Snowman_SetState)

/* func_ov003_0221a484: an item a snowman's map object replaced goes to main's list of fifteen
 * (func_0203a76c) when it is something (for a code func_0204bcdc accepts, by comparing
 * func_0204bc64 of it and of nothing) of a kind func_0204bd08 or func_0204bcdc accepts; whether
 * it went. */
int Snowman_KeepDisplacedItem(u16 *item)
{
    int nothing;
    if (ItemCode_HasVariant(item)) {
        u16 none = SNOWMAN_NO_ITEM;
        int code = ItemCode_VariantItem(item);
        nothing = code == ItemCode_VariantItem(&none);
    } else {
        nothing = *item == SNOWMAN_NO_ITEM;
    }
    if (!nothing && (ItemCode_IsKind1(item) || ItemCode_HasVariant(item))) {
        TownItemLists_PushListA(*item);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_0221a484, Snowman_KeepDisplacedItem)

/* func_ov003_0221a4f0: puts nothing on the tile of `position` (layer 0); whether it could. Also
 * 0 without a map. */
int Snowman_ClearTile(const Vec3 *position)
{
    void *map = data_021c80bc;
    if (map != NULL) {
        int x, z;
        Position_Tile(&x, &z, (const Position *) position);
        u16 none = SNOWMAN_NO_ITEM;
        if (AcreTile_SetItem(map, &none, x, z, 0)) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov003_0221a4f0, Snowman_ClearTile)

/* func_ov003_0221a538: snowman `number`'s map object on one of the eight tiles around the one
 * of `position` where it can stand (Snowman_CanStandAt), drawn at random among them
 * (func_020644cc); `*replaced` as Snowman_PlaceObject leaves it. Whether it was put; 0 without
 * a map or when no tile around can take it.
 * QUIRK: the object's code is asked for (func_0204bb14) and not used. */
int Snowman_PlaceObjectNearby(int number, Vec3 *position, u16 *replaced)
{
    if (data_021c80bc == NULL) {
        return 0;
    }
    MapCode_Snowman((u32) number);
    int x, z;
    Position_Tile(&x, &z, (const Position *) position);
    u8 usable = 0;
    int count = 0;
    for (int i = 0; i < 8; i++) {
        Vec3 point;
        AcreTile_TileCentre(&point, (u32) (x + data_ov003_0223660c[i].x), (u32) (z + data_ov003_0223660c[i].z));
        if (Snowman_CanStandAt(&point)) {
            usable |= (u8) (1 << i);
            count++;
        }
    }
    if (count == 0) {
        return 0;
    }
    int chosen = MainRandom_Below(count);
    int seen = 0;
    for (int i = 0; i < 8; i++) {
        if ((usable >> i) & 1) {
            if (seen == chosen) {
                Vec3 point;
                AcreTile_TileCentre(&point, (u32) (x + data_ov003_0223660c[i].x), (u32) (z + data_ov003_0223660c[i].z));
                return Snowman_PlaceObject(number, &point, replaced) != 0;
            }
            seen++;
        }
    }
    return 0;
}
CLEAN_AS(func_ov003_0221a538, Snowman_PlaceObjectNearby)

/* func_ov003_0221a608: snowman `number`'s map object put on the tile of `position` (layer 0)
 * when it can stand there (Snowman_CanStandAt); `*replaced` becomes the item that was on the
 * tile (nothing, 0xfff1, when it cannot stand there or there is no map). Whether it was put. */
int Snowman_PlaceObject(int number, Vec3 *position, u16 *replaced)
{
    *replaced = SNOWMAN_NO_ITEM;
    if (!Snowman_CanStandAt(position)) {
        return 0;
    }
    void *map = data_021c80bc;
    if (map == NULL) {
        return 0;
    }
    u16 object = MapCode_Snowman((u32) number);
    int x, z;
    Position_Tile(&x, &z, (const Position *) position);
    u16 *there = item_on_tile(map, x, z);
    if (there != NULL) {
        *replaced = *there;
    }
    return AcreTile_SetItem(map, &object, x, z, 0) != 0;
}
CLEAN_AS(func_ov003_0221a608, Snowman_PlaceObject)

/* Whether main's tables allow a snowman next to a tile: func_02031b38 says yes, and
 * func_02031078 finds nothing there or something of kind 2. */
static int tile_allows(int x, int z)
{
    int a, b, c;
    int found = CollisionQuery_PostAt(x, z, (fx32 *) &a, (fx32 *) &b, &c);
    return UnitTypeInfo_Byte04At(x, z) != 0 && !(found != 0 && c != 2);
}

/* func_ov003_0221a68c: whether a snowman can stand on the tile of `position`: there is a map,
 * the item there is not one func_0204c71c rejects, it is not the player's tile, main's tables
 * allow it (as tile_allows, and func_02031acc 0 or 1) and allow each of the eight tiles around
 * it. */
int Snowman_CanStandAt(Vec3 *position)
{
    void *map = data_021c80bc;
    if (map == NULL) {
        return 0;
    }
    int player_x = -1, player_z = -1;
    SnowmanVisitor *player = SessionPlayers_ActorOf(SNOWMAN_PLAYER);
    if (player != NULL) {
        Position_Tile(&player_x, &player_z, (const Position *) &player->position);
    }
    int x, z;
    Position_Tile(&x, &z, (const Position *) position);
    u16 *item = item_on_tile(map, x, z);
    if (item != NULL && MapCode_IsSpecial(item)) {
        return 0;
    }
    int a, b, c;
    int found = CollisionQuery_PostAt(x, z, (fx32 *) &a, (fx32 *) &b, &c);
    if (x == player_x && z == player_z) {
        return 0;
    }
    if (UnitTypeInfo_Byte04At(x, z) == 0 || (found != 0 && c != 2)) {
        return 0;
    }
    if (UnitTypeInfo_Byte09At(x, z) > 1) {
        return 0;
    }
    for (int dx = -1; dx <= 1; dx++) {
        for (int dz = -1; dz <= 1; dz++) {
            if ((dx != 0 || dz != 0) && !tile_allows(x + dx, z + dz)) {
                return 0;
            }
        }
    }
    return 1;
}
CLEAN_AS(func_ov003_0221a68c, Snowman_CanStandAt)

/* func_ov003_0221a7a0: the starting state. A loose ball starts in state 0. A snowman's part
 * notes its snowman's number ((index - 2) / 2) and, when main keeps that snowman
 * (func_020b0594), its face, then takes its size from it: a body (state 9) the body's size, a
 * head (state 0xb) the head's, lifted to sit on the body. Without the snowman nothing more
 * happens. */
void Snowman_Setup(Snowman *snowman)
{
    if (Snowman_IsLoose(snowman)) {
        Snowman_SetState(snowman, SNOWMAN_STATE_LOOSE);
        return;
    }
    int is_body = Snowman_IsBody(snowman);
    u32 number = ((snowman->index - 2) >> 1) & SNOWMAN_NUMBER_MASK;
    snowman->flags = (u16) ((snowman->flags & ~SNOWMAN_NUMBER_MASK) | number);
    int head_size, body_size, face;
    if (Snowmen_Get((SnowmenRecord *) data_021f3b56, number, &head_size, &body_size, &face, NULL, NULL, NULL) == 0) {
        return;
    }
    snowman->flags = (u16) ((snowman->flags & ~(3 << SNOWMAN_KIND_SHIFT)) | ((face & 3) << SNOWMAN_KIND_SHIFT));
    if (is_body) {
        snowman->size = body_size;
        Snowman_SetState(snowman, SNOWMAN_STATE_BODY);
    } else {
        snowman->size = head_size;
        snowman->position.y = body_size * 2 - shift_right(body_size, 3) - shift_right(head_size, 3) - 0x400;
        Snowman_SetState(snowman, SNOWMAN_STATE_HEAD);
    }
}
CLEAN_AS(func_ov003_0221a7a0, Snowman_Setup)

/* func_ov003_0221a860: whether it is a snowman's body (an odd index from 3). */
int Snowman_IsBody(Snowman *snowman)
{
    return Snowman_IsPart(snowman) && !Snowman_IsHead(snowman);
}
CLEAN_AS(func_ov003_0221a860, Snowman_IsBody)

/* func_ov003_0221a888: whether it is a snowman's head (an even index from 2). */
int Snowman_IsHead(Snowman *snowman)
{
    return Snowman_IsPart(snowman) && ((snowman->index - 2) & 1) == 0;
}
CLEAN_AS(func_ov003_0221a888, Snowman_IsHead)

/* func_ov003_0221a8ac: whether it is part of a snowman (index 2 and up). */
int Snowman_IsPart(Snowman *snowman)
{
    return !Snowman_IsLoose(snowman);
}
CLEAN_AS(func_ov003_0221a8ac, Snowman_IsPart)

/* func_ov003_0221a8c4: whether it is a loose ball (index 0 or 1). */
int Snowman_IsLoose(Snowman *snowman)
{
    return snowman->index < 2;
}
CLEAN_AS(func_ov003_0221a8c4, Snowman_IsLoose)

/* func_ov003_0221a8d4: whether the first machine is in one of the loose ball's states. */
int Snowman_CanRoll(Snowman *snowman)
{
    return snowman->scene_state < SNOWMAN_STATE_LOOSE_END;
}
CLEAN_AS(func_ov003_0221a8d4, Snowman_CanRoll)

/* The push that Snowman_Push has added is taken back. */
static int push_refused(Snowman *snowman, fx32 velocity_x, fx32 velocity_z)
{
    snowman->position.x -= snowman->body.rolling.velocity_x;
    snowman->position.z -= snowman->body.rolling.velocity_z;
    snowman->body.rolling.velocity_x = velocity_x;
    snowman->body.rolling.velocity_z = velocity_z;
    return 0;
}

/* func_ov003_0221a8e8: the player (func_020961a8) pushes a loose ball of at least
 * SNOWMAN_SIZE_PUSHABLE with `force` (at most 0xc32) towards `direction`. Not when
 * func_020b6660 says no, without a player, or while either machine is busy.
 *
 * What touches it pushes it first (SNOWMAN_FLAG_CONTACT_MOVED). Its heading is `direction`, or
 * while it was pushed the frame before its last heading moved a fifth of the way towards
 * `direction` (Approach_DivideS16, at most 0x2000). The velocity (a sixteenth of what it was
 * when it was not pushed the frame before) gets force * 0x1b6 * roll factor along the heading,
 * and the ball moves by it. The player's point behind it is the player's position moved by that
 * same step. The push is refused (its move and velocity taken back) when that point is farther
 * than size + 1.0 from the ball's last position across the ground, when the direction from it
 * to the ball is more than 0x1000 (0x471c while pushed the frame before) off `direction`, or
 * when the player's yaw, moved an eighth of the way towards `direction`, is more than 0x471c
 * off the heading.
 *
 * A push that holds: `*behind` is that point, `*angle` the direction from it to the ball,
 * `*speed` half the velocity's length; it notes SNOWMAN_FLAG_PUSHED and the heading, plays
 * sound 0x820, and eases the roll factor towards 1.0 (faster for a smaller ball).
 * QUIRK: the angle differences are read as 16-bit signed values, so one of exactly half a turn
 * (0x8000) counts as negative and never refuses the push. */
int Snowman_Push(Snowman *snowman, Vec3 *behind, s16 *angle, int *speed, int force, int direction)
{
    SnowmanVisitor *player = SessionPlayers_ActorOf(SNOWMAN_PLAYER);
    if (SceneQuery_CurrentIs0() == 0 || player == NULL) {
        return 0;
    }
    if (snowman->talk_state != SNOWMAN_TALK_IDLE || snowman->scene_state != SNOWMAN_STATE_LOOSE) {
        return 0;
    }
    if (snowman->size < SNOWMAN_SIZE_PUSHABLE) {
        return 0;
    }
    if (force > 0xc32) {
        force = 0xc32;
    }
    if (snowman->body.body.touched) {
        snowman->position.x += snowman->body.body.push_x;
        snowman->position.z += snowman->body.body.push_z;
        snowman->flags |= SNOWMAN_FLAG_CONTACT_MOVED;
    }

    s16 heading = (s16) direction;
    if (snowman->flags & SNOWMAN_FLAG_WAS_PUSHED) {
        heading = snowman->heading;
        Approach_DivideS16(&heading, direction, 5, 0x2000);
    }
    fx32 velocity_x = snowman->body.rolling.velocity_x;
    fx32 velocity_z = snowman->body.rolling.velocity_z;
    if (!(snowman->flags & SNOWMAN_FLAG_WAS_PUSHED)) {
        snowman->body.rolling.velocity_x = shift_right(velocity_x, 4);
        snowman->body.rolling.velocity_z = shift_right(velocity_z, 4);
    }
    fx32 step = FX_MulFunc(FX_MulFunc(force, 0x1b6), snowman->roll_factor);
    fx32 step_x = FX_MulFunc(step, sine(heading));
    fx32 step_z = FX_MulFunc(step, cosine(heading));
    snowman->body.rolling.velocity_x += step_x;
    snowman->body.rolling.velocity_z += step_z;
    snowman->position.x += snowman->body.rolling.velocity_x;
    snowman->position.z += snowman->body.rolling.velocity_z;

    s16 player_yaw = player->yaw;
    Approach_DivideS16(&player_yaw, direction, 8, 0x2000);
    Vec3 point = player->position;
    point.x += step_x;
    point.z += step_z;

    int to_ball = Math_Atan2(snowman->position.x - point.x, snowman->position.z - point.z);
    if ((u32) Vec_DistanceXZ(&snowman->last_position, &point) > (u32) (snowman->size + 0x1000)) {
        return push_refused(snowman, velocity_x, velocity_z);
    }
    s16 limit = (snowman->flags & SNOWMAN_FLAG_WAS_PUSHED) ? 0x471c : 0x1000;
    if ((s16) Math_AbsDiff16(to_ball, direction) > limit) {
        return push_refused(snowman, velocity_x, velocity_z);
    }
    if ((s16) Math_AbsDiff16(player_yaw, heading) > 0x471c) {
        return push_refused(snowman, velocity_x, velocity_z);
    }

    Vec3 offset;
    Vec_Subtract(&offset, &snowman->position, &point);
    *angle = Math_Atan2(offset.x, offset.z);
    *behind = point;
    snowman->flags |= SNOWMAN_FLAG_PUSHED;
    snowman->heading = heading;
    SoundEmitter_PlayEx(snowman_sound(snowman), 0x820, 0x7f, 0);
    fx32 growth = FX_Div(snowman->size - SNOWMAN_SIZE_PUSHABLE, SNOWMAN_SIZE_PUSHABLE);
    fx32 rate = FX_MulFunc(0xc00, 0x1000 - growth) + 0x200;
    Approach_EaseS32(&snowman->roll_factor, 0x1000, rate, 0x1000);
    Vec3 velocity = {snowman->body.rolling.velocity_x, 0, snowman->body.rolling.velocity_z};
    *speed = shift_right(Vec_LengthXZ(&velocity), 1);
    return 1;
}
CLEAN_AS(func_ov003_0221a8e8, Snowman_Push)

/* func_ov003_0221abf8: a loose ball is knocked (state 3); whether it was. Others are not.
 * The second argument is not used. */
int Snowman_Knock(Snowman *snowman, int unused)
{
    (void) unused;
    if (snowman->scene_state < SNOWMAN_STATE_LOOSE_END) {
        return Snowman_SetState(snowman, SNOWMAN_STATE_KNOCKED);
    }
    return 0;
}
CLEAN_AS(func_ov003_0221abf8, Snowman_Knock)

/* func_ov003_0221ac18 */
int Snowman_Size(Snowman *snowman)
{
    return snowman->size;
}
CLEAN_AS(func_ov003_0221ac18, Snowman_Size)

/* func_ov003_0221ac24: moves it to `position` (SNOWMAN_FLAG_PLACED) unless it was already
 * moved so, pushed, or hit this frame; whether it moved. */
int Snowman_Place(Snowman *snowman, const Vec3 *position)
{
    if (!(snowman->flags & SNOWMAN_FLAG_PLACED) && !(snowman->flags & SNOWMAN_FLAG_PUSHED) && !snowman->body.body.hit) {
        snowman->position = *position;
        snowman->flags |= SNOWMAN_FLAG_PLACED;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_0221ac24, Snowman_Place)

/* func_ov003_0221ac70: a frame of rolling. A loose idle ball falls by 0x200; the collider moves
 * it from its last position (func_02031288, layer 0xb or 0), with sound 0x81d for a loose idle
 * ball when it met more than before. The body is registered for contacts (func_02089c20) with
 * its size times a factor (0.65, 1.0 below SNOWMAN_SIZE_PUSHABLE, a step between those below
 * 0xe00), twice its size, flags 0x20 (and 2 with SNOWMAN_FLAG_CONTACT_2), 0x11 for a head or
 * 0x12, the index's low byte and its weight.
 *
 * The distance it moved makes it roll (Snowman_UpdateModels) by an angle that grows with the
 * distance over its size. A loose ball keeps that move as its velocity less a friction (by its
 * state and what its collider touches, from 0x28 to 0x155), at most 0x400; other balls stop.
 * On snow (ground kind 3) it grows by distance / 0x80000 of itself (at most to
 * SNOWMAN_SIZE_MAX) unless it was placed; elsewhere it shrinks by distance / 0x200000 (at least
 * to SNOWMAN_SIZE_MIN), except a loose idle-talking ball in states 2 and 6. */
void Snowman_Roll(Snowman *snowman)
{
    int layer = (snowman->flags & SNOWMAN_FLAG_LAYER_B) ? 0xb : 0;
    if (is_idle_loose(snowman)) {
        snowman->position.y -= 0x200;
    }
    CollisionQuery_Move((CollisionContacts *) snowman->collider, &snowman->position, &snowman->last_position, 0,
                        snowman->last_size, snowman, layer);

    u8 collisions = snowman->collisions;
    if (collisions > snowman->last_collisions && is_idle_loose(snowman)) {
        SoundEmitter_PlayB(snowman_sound(snowman), 0x81d, 0x7f, 0);
    }
    snowman->last_collisions = collisions;

    int contact_flags = 0x20;
    if (snowman->flags & SNOWMAN_FLAG_CONTACT_2) {
        contact_flags |= 2;
    }
    int kind = snowman->scene_state == SNOWMAN_STATE_HEAD ? 0x11 : 0x12;
    fx32 factor = FX_Div(0x41000, 0x64000);
    if (snowman->size < SNOWMAN_SIZE_PUSHABLE) {
        factor = 0x1000;
    } else if (snowman->size < 0xe00) {
        int percent = 100 - shift_right(0x23 * FX_Div(snowman->size - SNOWMAN_SIZE_PUSHABLE, 0x400), 12);
        factor = FX_Div(percent * 0x1000, 0x64000);
    }
    fx32 size = snowman->size;
    FieldOwnedBody_Set((FieldOwnedBody *) &snowman->body.body, (Actor *) snowman, FX_MulFunc(size, factor), size * 2,
                       contact_flags, 0x2fc, kind, (u8) snowman->index, snowman->body.body.weight);
    FieldBody_Enter((FieldBody *) &snowman->body.body);

    Vec3 moved;
    Vec_Subtract(&moved, &snowman->position, &snowman->last_position);
    fx32 distance = VEC_Mag(&moved);
    fx32 turns = FX_Div(distance, FX_MulFunc(0x323d, snowman->size));
    int roll = (s16) (u16) ((u32) shift_right(turns, 1) << 4);
    int direction = Math_Atan2(moved.x, moved.z);

    if (Snowman_CanRoll(snowman)) {
        fx32 length = VEC_Mag(&moved);
        if (length == 0) {
            snowman->body.rolling.velocity_x = 0;
            snowman->body.rolling.velocity_z = 0;
        } else {
            fx32 left;
            if (snowman->talk_state == SNOWMAN_TALK_IDLE && snowman->scene_state == 1) {
                left = length - FX_Div(0x2000, 0xa5000);
            } else if (snowman->talk_state == SNOWMAN_TALK_IDLE && snowman->scene_state == 5) {
                left = length - 0x155;
            } else {
                int touching = *(const int *) (const void *) (snowman->collider + 4);
                if (touching & 1) {
                    left = length - ((snowman->flags & SNOWMAN_FLAG_PUSHED) ? 0x155 : 0x28);
                } else if (touching & 2) {
                    left = length - 0xaa;
                } else {
                    left = length - FX_Div(0x2000, 0xa0000);
                }
            }
            if (left < 0) {
                left = 0;
            }
            if (left > 0x400) {
                left = 0x400;
            }
            fx32 scale = FX_Div(left, length);
            snowman->body.rolling.velocity_x = FX_MulFunc(moved.x, scale);
            snowman->body.rolling.velocity_z = FX_MulFunc(moved.z, scale);
        }
    } else {
        snowman->body.rolling.velocity_x = 0;
        snowman->body.rolling.velocity_z = 0;
    }

    SnowmanGround ground;
    CollisionGround_Init((CollisionGround *) &ground, &snowman->position, 0, 0);
    if (ground.kind == SNOWMAN_GROUND_SNOW) {
        if (!(snowman->flags & SNOWMAN_FLAG_PLACED)) {
            snowman->size = FX_MulFunc(snowman->size, shift_right(distance, 7) + 0x1000);
            if (snowman->size > SNOWMAN_SIZE_MAX) {
                snowman->size = SNOWMAN_SIZE_MAX;
            }
        }
    } else if (!(snowman->talk_state == SNOWMAN_TALK_IDLE && (snowman->scene_state == 2 || snowman->scene_state == 6))) {
        snowman->size = FX_MulFunc(snowman->size, 0x1000 - shift_right(distance, 9));
        if (snowman->size < SNOWMAN_SIZE_MIN) {
            snowman->size = SNOWMAN_SIZE_MIN;
        }
    }
    Snowman_UpdateModels(snowman, roll, direction);
    CollisionGround_Destroy((CollisionGround *) &ground);
}
CLEAN_AS(func_ov003_0221ac70, Snowman_Roll)

/* func_ov003_0221af94: before the machines run. While something touches it, its push moves the
 * ball (unless Snowman_Push already added it), and a ball below SNOWMAN_SIZE_PUSHABLE touched
 * with contact flag 4 plays sound 0x81c once per contact. Its weight follows its size:
 * ((size - 0x800) / 0xc00 * 1.05 + 0.87) * 4. */
void Snowman_PreUpdate(Snowman *snowman)
{
    if (snowman->body.body.touched) {
        if (!(snowman->flags & SNOWMAN_FLAG_CONTACT_MOVED)) {
            snowman->position.x += snowman->body.body.push_x;
            snowman->position.z += snowman->body.body.push_z;
        }
        if (FieldBody_TouchedWith((FieldBody *) &snowman->body.body, 4) && snowman->size < SNOWMAN_SIZE_PUSHABLE) {
            if (!snowman->rolling_sound) {
                SoundEmitter_PlayB(snowman_sound(snowman), 0x81c, 0x7f, 0);
            }
            snowman->rolling_sound = 1;
        } else {
            snowman->rolling_sound = 0;
        }
    } else {
        snowman->rolling_sound = 0;
    }
    fx32 part = FX_MulFunc(FX_Div(snowman->size - SNOWMAN_SIZE_MIN, 0xc00), 0x10cd);
    snowman->body.body.weight = (int) ((u32) (part + 0xdec) << 2);
}
CLEAN_AS(func_ov003_0221af94, Snowman_PreUpdate)

/* func_ov003_0221b064: where its models are drawn. A nonzero `roll` turns its rotation by `roll`
 * about the level axis across `direction` (func_0209a204), and once in eight frames (when the
 * frame count's low three bits are its index) the rotation is normalized (func_0209a3c8). The
 * models sit at the position plus the offset, lifted by its size less 0.25, as the camera shows
 * that point (func_0203f8d0, which also gives an angle to turn about x by), rotated. */
void Snowman_UpdateModels(Snowman *snowman, int roll, int direction)
{
    SnowmanQuat *rotation = &snowman->body.rolling.rotation;
    if (roll != 0) {
        Vec3 axis = {cosine(direction), 0, -sine(direction)};
        int half = shift_right(roll, 1);
        Vec_Scale(&axis, sine(half));
        SnowmanQuat turn = {axis.x, axis.y, axis.z, cosine(half)};
        Quat_Multiply((const Quat *) &turn, (const Quat *) rotation, (Quat *) rotation);
        if ((data_021fbdd0 & 7) == (int) snowman->index) {
            Quat_Normalize((Quat *) rotation);
        }
    }
    Vec3 at;
    Vec_Add(&at, &snowman->position, &snowman->body.rolling.model_offset);
    at.y = at.y + snowman->size - 0x400;
    Vec3 shown;
    int tilt = Globe_BendFar(&shown, &at);
    Mtx43 place;
    Mtx43_Translation(&place, shown.x, shown.y, shown.z);
    Mtx43_RotateX(&place, tilt);
    Mtx43 turned;
    Quat_ToMtx43((const Quat *) rotation, &turned);
    MTX_Concat43(&turned, &place, &place);
    snowman->ball_model.matrix = place;
    snowman->face_model.matrix = place;
}
CLEAN_AS(func_ov003_0221b064, Snowman_UpdateModels)

/* func_ov003_0221b174 (vtable slot 0x0c): leaving the scene. A body takes any snowman's map
 * object off its tile, then stands its own snowman's there or on a tile around it; when neither
 * can take it, main forgets that snowman (func_020b0540). The item the object replaced is kept
 * (Snowman_KeepDisplacedItem). An idle loose ball saves its position and size. Then its sound
 * is told (the emitter's vtable slot 0x10) and it leaves overlay 3's table of balls.
 * REQUIRES: a body has a map. */
void Snowman_Leave(Snowman *snowman)
{
    if (snowman->scene_state == SNOWMAN_STATE_BODY) {
        void *map = data_021c80bc;
        int x, z;
        Position_Tile(&x, &z, (const Position *) &snowman->position);
        u16 *item = item_on_tile(map, x, z);
        if (item != NULL && MapCode_IsSnowman(item)) {
            u16 none = SNOWMAN_NO_ITEM;
            AcreTile_SetItem(map, &none, x, z, 0);
        }
        int number = snowman->flags & SNOWMAN_NUMBER_MASK;
        if (!Snowman_PlaceObject(number, &snowman->position, &snowman->item_under) &&
            !Snowman_PlaceObjectNearby(number, &snowman->position, &snowman->item_under)) {
            Snowmen_TakeOffMap((SnowmenRecord *) data_021f3b56, (u32) number);
        }
        Snowman_KeepDisplacedItem(&snowman->item_under);
    }
    if (is_idle_loose(snowman)) {
        SnowmanSaved *saved = (SnowmanSaved *) Snowmen_LooseBalls();
        saved[snowman->index & 1].position = snowman->position;
        fx32 size = snowman->size;
        saved = (SnowmanSaved *) Snowmen_LooseBalls();
        saved[snowman->index & 1].size = size;
    }
    SoundEmitter_Vfunc10B(snowman_sound(snowman));
    Snowman_Unregister(snowman);
}
CLEAN_AS(func_ov003_0221b174, Snowman_Leave)

/* func_ov003_0221b294 (vtable slot 0x24): draws it while the camera exists and it is within
 * data_020ca0ec of the camera's point across the ground: the face model for a head, else the
 * ball's, scaled by its size (func_02055e7c), and func_020acc0c at its position with its size.
 * Always 1. */
int Snowman_Draw(Snowman *snowman)
{
    if (data_021c67a4 != 0 && Vec_DistanceXZ(&data_021c67d0, &snowman->position) <= data_020ca0ec) {
        fx32 scale = FX_Div(snowman->size, 0x1000);
        Vec3 scales = {scale, scale, scale};
        if (snowman->scene_state == SNOWMAN_STATE_HEAD) {
            ModelObject_Draw((ModelObject *) &snowman->face_model, &scales);
        } else {
            ModelObject_Draw((ModelObject *) &snowman->ball_model, &scales);
        }
        CharaShadow_Draw(&snowman->position, snowman->size, 0x4000, 0x1000);
    }
    return 1;
}
CLEAN_AS(func_ov003_0221b294, Snowman_Draw)

/* _ZN18Obj_ov003_022382ac19func_ov003_0221b320Ev (vtable slot 0x18): a frame. Unless it was
 * pushed this frame its roll factor drops to 0.1; the frame starts from where the last ended;
 * then Snowman_PreUpdate, the first machine, the talk and Snowman_Roll. The frame's flags move
 * on (pushed becomes pushed the frame before; contact moved and placed clear), and so does the
 * hit; its sound follows it (given a copy of its position). Always 1. */
u32 Snowman_Update(Snowman *snowman)
{
    fx32 factor = FX_Div(0xa000, 0x64000);
    if (!(snowman->flags & SNOWMAN_FLAG_PUSHED)) {
        snowman->roll_factor = factor;
    }
    snowman->last_position = snowman->body.rolling.start_position;
    Snowman_PreUpdate(snowman);
    Snowman_UpdateState(snowman);
    SnowmanTalk_Update(snowman);
    Snowman_Roll(snowman);

    u16 flags = snowman->flags &
                (u16) ~(SNOWMAN_FLAG_WAS_PUSHED | SNOWMAN_FLAG_PUSHED | SNOWMAN_FLAG_CONTACT_MOVED | SNOWMAN_FLAG_PLACED);
    if (snowman->flags & SNOWMAN_FLAG_PUSHED) {
        flags |= SNOWMAN_FLAG_WAS_PUSHED;
    }
    snowman->flags = flags;
    snowman->body.body.hit = 0;

    snowman->last_position = snowman->position;
    snowman->body.rolling.start_position = snowman->last_position;
    Vec3 position = snowman->position;
    SoundEmitter_UpdateAtB(snowman_sound(snowman), &position);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov003_022382ac19func_ov003_0221b320Ev, Snowman_Update)

/* func_ov003_0221b414 (vtable slot 0x00): starting. Nothing under it, no rotation, both models
 * loaded; a loose ball takes its size from main's table and writes its position there (and the
 * same size back). Then func_0203efb0 with the index, the talk idle, the starting state
 * (Snowman_Setup), its collider settled from where it is (layer 0xb), the models placed, its
 * sound stopped and func_0203edd0; it enters overlay 3's table of balls. */
void Snowman_Init(Snowman *snowman)
{
    snowman->item_under = SNOWMAN_NO_ITEM;
    snowman->body.rolling.rotation = data_020d1a10;
    ModelObject_LoadShared((ModelObject *) &snowman->ball_model, SNOWMAN_TAG_BALL, data_ov003_022383ac);
    ModelObject_LoadShared((ModelObject *) &snowman->face_model, SNOWMAN_TAG_FACE, data_ov003_022383c8);
    if (Snowman_IsLoose(snowman)) {
        SnowmanSaved *saved = (SnowmanSaved *) Snowmen_LooseBalls();
        snowman->size = saved[snowman->index & 1].size;
        saved = (SnowmanSaved *) Snowmen_LooseBalls();
        saved[snowman->index & 1].position = snowman->position;
        fx32 size = snowman->size;
        saved = (SnowmanSaved *) Snowmen_LooseBalls();
        saved[snowman->index & 1].size = size;
    }
    SceneObjectBase_SetId((SceneObjectBase *) snowman, (u16) snowman->index);
    SnowmanTalk_SetState(snowman, SNOWMAN_TALK_IDLE);
    Snowman_Setup(snowman);

    snowman->last_position = snowman->position;
    snowman->body.rolling.start_position = snowman->last_position;
    CollisionQuery_Move((CollisionContacts *) snowman->collider, &snowman->position, &snowman->last_position, 0,
                        snowman->last_size, snowman, 0xb);
    snowman->last_position = snowman->position;
    snowman->body.rolling.start_position = snowman->last_position;
    snowman->last_collisions = snowman->collisions;

    Snowman_UpdateModels(snowman, 0, 0);
    SoundEmitter_StopB(snowman_sound(snowman));
    SceneObjectBase_ClearApproach((SceneObjectBase *) snowman);
    Snowman_Register(snowman);
}
CLEAN_AS(func_ov003_0221b414, Snowman_Init)

/* func_ov003_0221b5a4 (the class's operator delete): frees a block to the balls' heap, when
 * there is one. */
void Snowman_Delete(void *block)
{
    if (data_021c9b24 != NULL) {
        Heap_Free(data_021c9b24, block);
    }
}
CLEAN_AS(func_ov003_0221b5a4, Snowman_Delete)

/* func_ov003_0221b5c0 (the class's operator new): a zeroed block of `size` bytes from the balls'
 * heap.
 * REQUIRES: the heap has room. Without, the original clears `size` bytes at address 0; Clean
 * does not. */
void *Snowman_Alloc(int size)
{
    void *block = Heap_Alloc(data_021c9b24, size);
    if (block != NULL) {
        memset(block, 0, (size_t) size);
    }
    return block;
}
CLEAN_AS(func_ov003_0221b5c0, Snowman_Alloc)

/* func_ov003_0221b5e8: the largest size a ball grows to. */
int Snowman_MaxSize(void)
{
    return SNOWMAN_SIZE_MAX;
}
CLEAN_AS(func_ov003_0221b5e8, Snowman_MaxSize)

/* func_ov003_0221b5f0: the smallest size a ball shrinks to. */
int Snowman_MinSize(void)
{
    return SNOWMAN_SIZE_MIN;
}
CLEAN_AS(func_ov003_0221b5f0, Snowman_MinSize)

/* The vtables set back, then the sound, the body, the collider, the models, the receiver part
 * and the base destroyed in turn. */
static void destroy_parts(Snowman *snowman)
{
    snowman->vtable = data_ov003_022382ac;
    snowman->receiver_vtable = data_ov003_02238314;
    SoundEmitterClass_DestructBaseB((SoundEmitterObject *) (void *) snowman->sound);
    SnowmanBody_Destroy(&snowman->body.body);
    CollisionContacts_Destroy((CollisionContacts *) snowman->collider);
    ModelObject_DestructComplete((ModelObject *) &snowman->face_model);
    ModelObject_DestructComplete((ModelObject *) &snowman->ball_model);
    TalkReceiver_Destruct((TalkReceiver *) &snowman->receiver_vtable);
    SceneObjectBase_DestructBase((SceneObjectBase *) snowman);
}

/* func_ov003_0221b5f8 (the deleting destructor): the destructor's work, then the memory freed
 * (Snowman_Delete). */
Snowman *Snowman_DestroyAndFree(Snowman *snowman)
{
    destroy_parts(snowman);
    Snowman_Delete(snowman);
    return snowman;
}
CLEAN_AS(func_ov003_0221b5f8, Snowman_DestroyAndFree)

/* func_ov003_0221b668: the destructor, without freeing. */
Snowman *Snowman_Destroy(Snowman *snowman)
{
    destroy_parts(snowman);
    return snowman;
}
CLEAN_AS(func_ov003_0221b668, Snowman_Destroy)

/* func_ov003_0221b6d4: the constructor: the base and the receiver part, the vtables, the
 * models, the collider, the body and the sound; nothing under it. */
Snowman *Snowman_Construct(Snowman *snowman)
{
    SceneObjectBase_Construct((SceneObjectBase *) snowman);
    TalkReceiver_ConstructBase((TalkReceiver *) &snowman->receiver_vtable);
    snowman->vtable = data_ov003_022382ac;
    snowman->receiver_vtable = data_ov003_02238314;
    ModelObject_Construct((ModelObject *) &snowman->ball_model);
    ModelObject_Construct((ModelObject *) &snowman->face_model);
    CollisionContacts_Construct((CollisionContacts *) snowman->collider);
    SnowmanBody_Construct(&snowman->body.body);
    SoundEmitterClass_ConstructBaseB((SoundEmitterObject *) (void *) snowman->sound);
    snowman->item_under = SNOWMAN_NO_ITEM;
    return snowman;
}
CLEAN_AS(func_ov003_0221b6d4, Snowman_Construct)

/* func_ov003_0221b74c (the body's vtable slot 0x08): told of a contact; flag 4 marks it hit. */
void SnowmanBody_OnContact(SnowmanBody *body, int a, int b, int flags)
{
    (void) a;
    (void) b;
    if (flags & 4) {
        body->hit = 1;
    }
}
CLEAN_AS(func_ov003_0221b74c, SnowmanBody_OnContact)

/* func_ov003_0221b75c: the body's destructor: its vtable, not hit, then its base's. */
SnowmanBody *SnowmanBody_Destroy(SnowmanBody *body)
{
    body->vtable = data_ov003_02238280;
    body->hit = 0;
    FieldOwnedBody_Destruct((FieldOwnedBody *) body);
    return body;
}
CLEAN_AS(func_ov003_0221b75c, SnowmanBody_Destroy)

/* func_ov003_0221b77c: the body's constructor: its base's, then its vtable, not hit. */
SnowmanBody *SnowmanBody_Construct(SnowmanBody *body)
{
    FieldOwnedBody_Construct((FieldOwnedBody *) body);
    body->vtable = data_ov003_02238280;
    body->hit = 0;
    return body;
}
CLEAN_AS(func_ov003_0221b77c, SnowmanBody_Construct)

/* func_ov003_0221b79c: allocates and constructs a ball; nothing keeps the pointer here. */
void Snowman_New(void)
{
    Snowman *snowman = Snowman_Alloc(sizeof(Snowman));
    if (snowman != NULL) {
        Snowman_Construct(snowman);
    }
}
CLEAN_AS(func_ov003_0221b79c, Snowman_New)

/* The ball a pointer to its receiver part belongs to. */
static Snowman *snowman_of(void *receiver)
{
    return (Snowman *) (void *) ((u8 *) receiver - SNOWMAN_RECEIVER_OFFSET);
}

/* func_ov003_0221b7b8 (the receiver vtable's deleting destructor): Snowman_DestroyAndFree on the
 * ball around `receiver`. */
Snowman *Snowman_ReceiverDestroyAndFree(void *receiver)
{
    return Snowman_DestroyAndFree(snowman_of(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_022382acD0Ev, Snowman_ReceiverDestroyAndFree)

/* func_ov003_0221b7d4 (the receiver vtable's destructor): Snowman_Destroy on the ball around
 * `receiver`. */
Snowman *Snowman_ReceiverDestroy(void *receiver)
{
    return Snowman_Destroy(snowman_of(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_022382acD1Ev, Snowman_ReceiverDestroy)

/* ---- Overlay 3's table of balls */

/* The balls by the low three bits of their index (snowman.h); a free entry is NULL. */
extern Snowman *data_ov003_02262b38[8];

#define SNOWMAN_TABLE_SIZE 8

/* func_ov003_02236128: the first ball of the table other than `ball` that can roll
 * (Snowman_CanRoll), or NULL. */
Snowman *Snowman_OtherRollable(Snowman *ball)
{
    for (u32 i = 0; i < SNOWMAN_TABLE_SIZE; i++) {
        Snowman *other = data_ov003_02262b38[i];
        if (other == NULL || other == ball) {
            continue;
        }
        if (Snowman_CanRoll(other) != 0) {
            return other;
        }
    }
    return NULL;
}
CLEAN_AS(func_ov003_02236128, Snowman_OtherRollable)

/* func_ov003_02236164: loose ball `index & 1` when it is at rest: in the first machine's state
 * 0, not talking, not pushed this frame and not hit; else NULL. */
Snowman *Snowman_IdleLooseBall(int index)
{
    Snowman *ball = Snowman_Find(index & 1);
    if (ball != NULL && ball->talk_state == SNOWMAN_TALK_IDLE && ball->scene_state == SNOWMAN_STATE_LOOSE &&
        (ball->flags & SNOWMAN_FLAG_PUSHED) == 0 && ball->body.body.hit == 0) {
        return ball;
    }
    return NULL;
}
CLEAN_AS(func_ov003_02236164, Snowman_IdleLooseBall)

/* func_ov003_022361bc: each ball of the table offered the push (Snowman_Push) in turn, until
 * one takes it; whether one did. */
int Snowman_PushAny(Vec3 *behind, s16 *angle, int *speed, int force, int direction)
{
    for (u32 i = 0; i < SNOWMAN_TABLE_SIZE; i++) {
        if (data_ov003_02262b38[i] != NULL &&
            Snowman_Push(data_ov003_02262b38[i], behind, angle, speed, force, direction) != 0) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov003_022361bc, Snowman_PushAny)

/* func_ov003_02236204: the ball of the table whose index is `index`, or NULL. */
Snowman *Snowman_Find(int index)
{
    for (u32 i = 0; i < SNOWMAN_TABLE_SIZE; i++) {
        Snowman *ball = data_ov003_02262b38[i];
        if (ball != NULL && (u32) index == ball->index) {
            return ball;
        }
    }
    return NULL;
}
CLEAN_AS(func_ov003_02236204, Snowman_Find)

/* func_ov003_02236230: the ball taken out of its entry of the table (the low three bits of its
 * index); whether it was there. */
int Snowman_Unregister(Snowman *ball)
{
    u32 slot = ball->index & 7;
    if (data_ov003_02262b38[slot] == ball) {
        data_ov003_02262b38[slot] = NULL;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_02236230, Snowman_Unregister)

/* func_ov003_02236254: the ball put in its entry of the table; 0 when the entry is taken. */
int Snowman_Register(Snowman *ball)
{
    u32 slot = ball->index & 7;
    if (data_ov003_02262b38[slot] != NULL) {
        return 0;
    }
    data_ov003_02262b38[slot] = ball;
    return 1;
}
CLEAN_AS(func_ov003_02236254, Snowman_Register)
