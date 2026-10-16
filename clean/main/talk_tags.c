/* The tags of a talk's messages: the handlers of groups 4 to 11 (talk_tags.h).
 *
 * REQUIRES: the walker and the talk at word-aligned addresses, as every object of the game is. */
#include "talk_tags.h"

#include "clean.h"
#include "house_record.h"
#include "item_record.h"
#include "mail_particles.h"
#include "message_tag.h"
#include "message_walker.h"
#include "player_record.h"
#include "player_records.h"
#include "sky.h"
#include "state_block.h"
#include "talk_answers.h"
#include "talk_windows.h"
#include "villager_data.h"
#include "villager_memory_entry.h"
#include "villager_roster.h"

static_assert(offsetof(TalkTagsWalker, talk) == 0x24, "walker talk");
static_assert(offsetof(TalkTagsWalker, state) == 0x30, "walker state");
static_assert(offsetof(TalkTagsWalker, tag) == 0x38, "walker tag");
static_assert(offsetof(TalkTagsWalker, name_colour) == 0x5c, "walker colour");
static_assert(offsetof(TalkTagsWalker, choices_shown) == 0xd8, "walker choices");
static_assert(offsetof(TalkTagsWalker, convert_next) == 0xd9, "walker convert");
static_assert(offsetof(TalkTagsWalker, unk_e0) == 0xe0, "walker e0");
static_assert(sizeof(TalkTagsWalker) == 0xe4, "walker");

/* The parts of a talk used here. */
#define TALK_TAGS_WINDOWS 0x00b4  /* TalkWindows */
#define TALK_TAGS_RECEIVER 0x14a8 /* the receiver (Base_02066994) */
#define TALK_TAGS_PARTS 0x14b8    /* eleven message parts (MessagePart, 0x5c bytes) */
#define TALK_TAGS_PART_SIZE 0x5c
#define TALK_TAGS_PARTICLES 0x1a58      /* MailTextParticles */
#define TALK_TAGS_RO_AFTER_RIEUL 0x1a60 /* the particles' ro_after_rieul */
#define TALK_TAGS_WEEKDAY 0x1a6c        /* Calendar_TodayWeekday when the talk began (func_02067c20) */
#define TALK_TAGS_PART_OF_DAY 0x1a74    /* Calendar_PartOfDay then (enum PartOfDay) */
#define TALK_TAGS_OTHER_COLOUR 0x1e76   /* set: the other resident's name ends with colour 6 */

/* The texts func_020679b0 to func_02067728 load from the villager (see their handlers). */
#define TALK_TAGS_LIKED_NPC 0x1ccc
#define TALK_TAGS_DISLIKED_NPC 0x1cec
#define TALK_TAGS_RANDOM_NPC 0x1d0c
#define TALK_TAGS_OTHER_PLAYER 0x1d2c
#define TALK_TAGS_BOOM 0x1d4c
#define TALK_TAGS_IMPRESSION 0x1da8
#define TALK_TAGS_NICKNAME 0x1e04
#define TALK_TAGS_PRAISE 0x1e24

/* The receiver's vtable slots (Base_02066994; the scene base's are in scene_base.h). */
#define TALK_TAGS_SLOT_BRANCH 0x34       /* a branch: its kind and its number of choices */
#define TALK_TAGS_SLOT_FOCUS_PLAYER 0x3c /* SceneBase_FocusPlayer */
#define TALK_TAGS_SLOT_FOCUS_FIRST 0x40  /* SceneBase_FocusFirst */
#define TALK_TAGS_SLOT_FOCUS_SECOND 0x44 /* SceneBase_FocusSecond */
#define TALK_TAGS_SLOT_LOOK_PLAYER 0x48  /* SceneBase_LookAtPlayer */
#define TALK_TAGS_SLOT_FACE_PLAYER 0x4c  /* SceneBase_FacePlayer */
#define TALK_TAGS_SLOT_LOOK_FIRST 0x50   /* SceneBase_LookAtFirst */
#define TALK_TAGS_SLOT_FACE_FIRST 0x54   /* SceneBase_FaceFirst */
#define TALK_TAGS_SLOT_LOOK_SECOND 0x58  /* SceneBase_LookAtSecond */
#define TALK_TAGS_SLOT_FACE_SECOND 0x5c  /* SceneBase_FaceSecond */
#define TALK_TAGS_SLOT_PASS_TURN 0x60    /* SceneTalk_RequestWithCamera */
#define TALK_TAGS_SLOT_VILLAGER 0x68     /* the villager talked to, or NULL (func_02066864) */

/* The branch tags (group 6) by kind. */
enum TalkTagsBranch {
    TALK_TAGS_BRANCH_RANDOM2 = 0,
    TALK_TAGS_BRANCH_RANDOM3 = 1,
    TALK_TAGS_BRANCH_FONDNESS = 2,
    TALK_TAGS_BRANCH_PLAYER_KIND = 3,
    TALK_TAGS_BRANCH_HOUSE = 4,
    TALK_TAGS_BRANCH_INSECTS = 5,
    TALK_TAGS_BRANCH_FISH = 6,
    TALK_TAGS_BRANCH_VILLAGERS = 7,
    TALK_TAGS_BRANCH_PART_OF_DAY = 8,
    TALK_TAGS_BRANCH_FALLING = 9,
    TALK_TAGS_BRANCH_PLAYERS = 10,
    TALK_TAGS_BRANCH_WEEKDAY = 11,
    TALK_TAGS_BRANCH_RESIDENT = 12,
    TALK_TAGS_BRANCH_SPECIES = 13
};

/* The colours of the tags put after a name. */
#define TALK_TAGS_COLOUR_PRAISE 2
#define TALK_TAGS_COLOUR_PLAYER 5
#define TALK_TAGS_COLOUR_NPC 6

/* The kinds of creatures in the catalogues, and the count that earns the middle answer. */
#define TALK_TAGS_CREATURES_ALL 0x38
#define TALK_TAGS_CREATURES_MANY 0x21

/* The line numbers the empty failure note gets (with its Japanese label as data). */
#define TALK_TAGS_NOTE_SPECIES 0x1021
#define TALK_TAGS_NOTE_FONDNESS 0xe9a
#define TALK_TAGS_NOTE_BOOM 0xde6
#define TALK_TAGS_NOTE_PRAISE 0xdd0
#define TALK_TAGS_NOTE_NICKNAME 0xdb2
#define TALK_TAGS_NOTE_IMPRESSION 0xd9f
#define TALK_TAGS_NOTE_OTHER_PLAYER 0xd0b
#define TALK_TAGS_NOTE_RANDOM_NPC 0xcf5
#define TALK_TAGS_NOTE_DISLIKED_NPC 0xce0
#define TALK_TAGS_NOTE_LIKED_NPC 0xccb

/* The labels of the failure notes (Shift-JIS): "J species", "J fondness", "boom", "praise
 * word", "nickname", "impression", "other resident's player name", "random NPC", "NPC on bad
 * terms", "NPC on good terms". */
extern const char data_020df138[];
extern const char data_020df140[];
extern const char data_020df14c[];
extern const char data_020df154[];
extern const char data_020df160[];
extern const char data_020df170[];
extern const char data_020df178[];
extern const char data_020df188[];
extern const char data_020df198[];
extern const char data_020df1a8[];

/* A text of a lone tag 1/1 (and its end), walked before the slider's window opens. */
extern const u8 data_020cce98[];
/* The villager count at or under which tag 6/7 takes its first answer. */
extern const s32 data_020cd40c;
extern StateBlock data_021dc7a8;
extern HouseRecord data_021ebcd4;

/* The talk goes on with message `*message` of its file (func_0206844c, then the request
 * func_02068428 flags). */
extern void func_0206b964(TalkTagsWalker *walker, const u8 *message);
/* A failure note: empty in this build. */
extern void func_0206bb9c(void *walker, int line, const void *label);
/* Empty: handed a part of the talk, or nothing. */
extern void func_0206b97c(TalkTagsWalker *walker, void *part);
extern void func_0206b980(void);
/* The talk's name `index` (0 to 3, at 0x18ac) or part `index` (0 to 10) walked in place of
 * the tag. */
extern void func_0206b984(TalkTagsWalker *walker, int index);
extern void func_0206ba08(TalkTagsWalker *walker, int index);
/* The texts of the villager loaded into the talk: 0 when they could not be. */
extern int func_0206781c(u8 *talk);
extern int func_02067728(u8 *talk);
extern int func_0206777c(u8 *talk);
extern int func_020677d0(u8 *talk);
extern int func_0206786c(u8 *talk);
extern int func_020678f8(u8 *talk);
extern int func_02067964(u8 *talk);
extern int func_020679b0(u8 *talk);
/* The talk's answers (at 0x31c). */
extern TalkAnswers *func_0206837c(u8 *talk);
/* An answer; all of them cleared (the pick too); an answer's weight and its byte 0x70; the
 * first answer's text. */
extern TalkAnswer *func_020ab550(TalkAnswers *answers, int index);
extern void func_020ab5e4(TalkAnswers *answers);
extern u8 *func_020ab788(TalkAnswer *answer);
extern u8 *func_020ab794(TalkAnswer *answer);
extern MessageTagText *func_020ab53c(TalkAnswers *answers);
/* The signed byte 0x1c of a player's id: its kind. */
extern int func_020950c0(const DesignCreator *player);
/* A random number below `bound`. */
extern u32 func_020644cc(int bound);

typedef void TalkTagsSlot(void *receiver);
typedef void *TalkTagsPointerSlot(void *receiver);
typedef void TalkTagsBranchSlot(void *receiver, int kind, int choices);
typedef int TalkTagsCharactersFunction(const void *object);

static u8 *talk_tags_at(TalkTagsWalker *walker, u32 offset)
{
    return walker->talk + offset;
}

static void *talk_tags_receiver(TalkTagsWalker *walker)
{
    return *(void **) (void *) talk_tags_at(walker, TALK_TAGS_RECEIVER);
}

static u32 talk_tags_slot(const void *object, u32 slot)
{
    const u8 *vtable = *(const u8 *const *) object;
    return *(const u32 *) (const void *) (vtable + slot);
}

/* The receiver's slot `slot`, after the tag's empty func_020a8750 (the ROM calls it first). */
static void talk_tags_scene_move(TalkTagsWalker *walker, u32 slot)
{
    void *receiver = talk_tags_receiver(walker);
    MessageTag_Destruct(&walker->tag);
    ((TalkTagsSlot *) (uintptr_t) talk_tags_slot(receiver, slot))(receiver);
}

/* The receiver is told the branch and its number of choices; answers the receiver. */
static void *talk_tags_branch(TalkTagsWalker *walker, int kind, int choices)
{
    void *receiver = talk_tags_receiver(walker);
    ((TalkTagsBranchSlot *) (uintptr_t) talk_tags_slot(receiver, TALK_TAGS_SLOT_BRANCH))(receiver, kind, choices);
    return receiver;
}

static u8 *talk_tags_villager(void *receiver)
{
    return (u8 *) ((TalkTagsPointerSlot *) (uintptr_t) talk_tags_slot(receiver, TALK_TAGS_SLOT_VILLAGER))(receiver);
}

/* The characters of a text object (its vtable's slot 3), as an address. */
static int talk_tags_characters(const void *object)
{
    return ((TalkTagsCharactersFunction *) (uintptr_t) talk_tags_slot(object, 0x0c))(object);
}

/* The talk goes on with `message`. */
static void talk_tags_go_to(TalkTagsWalker *walker, u8 message)
{
    func_0206b964(walker, &message);
}

/* A text the talk loaded (`loaded`: whether the load worked) walked in place of the tag between
 * the walker's name colour and `colour_after` (no colour tags with -1), its last syllable kept
 * for the particles, and the particles' ro_after_rieul set to `ro_after_rieul`. A failed load
 * leaves a note only: the text is walked as it is. */
static void talk_tags_put_loaded(TalkTagsWalker *walker, int loaded, int line, const char *label, u32 text, int colour_after,
                                 s32 ro_after_rieul)
{
    if (loaded == 0) {
        func_0206bb9c(walker, line, label);
    }
    if (colour_after >= 0) {
        MessageWalker_Enter(&walker->base, MessageTag_ColourTag(walker->name_colour));
    }
    MessageWalker_Enter(&walker->base, talk_tags_characters(talk_tags_at(walker, text)));
    if (colour_after >= 0) {
        MessageWalker_Enter(&walker->base, MessageTag_ColourTag(colour_after));
    }
    MailParticles_TakeLastSyllable((MailTextParticles *) (void *) talk_tags_at(walker, TALK_TAGS_PARTICLES),
                                   (const char *) (uintptr_t) talk_tags_characters(talk_tags_at(walker, text)));
    *(s32 *) (void *) talk_tags_at(walker, TALK_TAGS_RO_AFTER_RIEUL) = ro_after_rieul;
}

/* func_020694b4 (tag 11/7): part 2 of the talk handed to the empty func_0206b97c. */
void TalkTags_NotePart2(TalkTagsWalker *walker)
{
    func_0206b97c(walker, talk_tags_at(walker, TALK_TAGS_PARTS + 2 * TALK_TAGS_PART_SIZE));
}
CLEAN_AS(func_020694b4, TalkTags_NotePart2)

/* func_020694c8 (tag 11/6): part 1, likewise. */
void TalkTags_NotePart1(TalkTagsWalker *walker)
{
    func_0206b97c(walker, talk_tags_at(walker, TALK_TAGS_PARTS + 1 * TALK_TAGS_PART_SIZE));
}
CLEAN_AS(func_020694c8, TalkTags_NotePart1)

/* func_020694dc (tag 11/5): part 0, likewise. */
void TalkTags_NotePart0(TalkTagsWalker *walker)
{
    func_0206b97c(walker, talk_tags_at(walker, TALK_TAGS_PARTS));
}
CLEAN_AS(func_020694dc, TalkTags_NotePart0)

/* func_020694f0 (tag 11/4): the empty func_0206b980. */
void TalkTags_Nothing11_4(void)
{
    func_0206b980();
}
CLEAN_AS(func_020694f0, TalkTags_Nothing11_4)

/* func_020694f8 (tag 11/3): the next character shown is first turned into its other form. */
void TalkTags_ConvertNext(TalkTagsWalker *walker)
{
    walker->convert_next = 1;
}
CLEAN_AS(func_020694f8, TalkTags_ConvertNext)

/* func_02069500 (tag 11/2) */
void TalkTags_SetE0Two(TalkTagsWalker *walker)
{
    walker->unk_e0 = 2;
}
CLEAN_AS(func_02069500, TalkTags_SetE0Two)

/* func_02069508 (tag 11/1) */
void TalkTags_SetE0One(TalkTagsWalker *walker)
{
    walker->unk_e0 = 1;
}
CLEAN_AS(func_02069508, TalkTags_SetE0One)

/* func_02069510 (tag 10/0): nothing. */
void TalkTags_Nothing10_0(void *walker)
{
    (void) walker;
}
CLEAN_AS(func_02069510, TalkTags_Nothing10_0)

/* func_02069514 (tag 9/9): the scene passes the turn to the next speaker. */
void TalkTags_PassTurn(TalkTagsWalker *walker)
{
    talk_tags_scene_move(walker, TALK_TAGS_SLOT_PASS_TURN);
}
CLEAN_AS(func_02069514, TalkTags_PassTurn)

/* func_02069534 (tag 9/8): the focus turns to face the second speaker. */
void TalkTags_FaceSecond(TalkTagsWalker *walker)
{
    talk_tags_scene_move(walker, TALK_TAGS_SLOT_FACE_SECOND);
}
CLEAN_AS(func_02069534, TalkTags_FaceSecond)

/* func_02069554 (tag 9/7): the focus looks at the second speaker; answers what the slot
 * answers. */
void *TalkTags_LookAtSecond(TalkTagsWalker *walker)
{
    void *receiver = talk_tags_receiver(walker);
    MessageTag_Destruct(&walker->tag);
    return ((TalkTagsPointerSlot *) (uintptr_t) talk_tags_slot(receiver, TALK_TAGS_SLOT_LOOK_SECOND))(receiver);
}
CLEAN_AS(func_02069554, TalkTags_LookAtSecond)

/* func_02069574 (tag 9/6): the focus turns to face the first speaker. */
void TalkTags_FaceFirst(TalkTagsWalker *walker)
{
    talk_tags_scene_move(walker, TALK_TAGS_SLOT_FACE_FIRST);
}
CLEAN_AS(func_02069574, TalkTags_FaceFirst)

/* func_02069594 (tag 9/5): the focus looks at the first speaker. */
void TalkTags_LookAtFirst(TalkTagsWalker *walker)
{
    talk_tags_scene_move(walker, TALK_TAGS_SLOT_LOOK_FIRST);
}
CLEAN_AS(func_02069594, TalkTags_LookAtFirst)

/* func_020695b4 (tag 9/4): the focus turns to face the player. */
void TalkTags_FacePlayer(TalkTagsWalker *walker)
{
    talk_tags_scene_move(walker, TALK_TAGS_SLOT_FACE_PLAYER);
}
CLEAN_AS(func_020695b4, TalkTags_FacePlayer)

/* func_020695d4 (tag 9/3): the focus looks at the player. */
void TalkTags_LookAtPlayer(TalkTagsWalker *walker)
{
    talk_tags_scene_move(walker, TALK_TAGS_SLOT_LOOK_PLAYER);
}
CLEAN_AS(func_020695d4, TalkTags_LookAtPlayer)

/* func_020695f4 (tag 9/2): the focus is the second speaker. */
void TalkTags_FocusSecond(TalkTagsWalker *walker)
{
    talk_tags_scene_move(walker, TALK_TAGS_SLOT_FOCUS_SECOND);
}
CLEAN_AS(func_020695f4, TalkTags_FocusSecond)

/* func_02069614 (tag 9/1): the focus is the first speaker. */
void TalkTags_FocusFirst(TalkTagsWalker *walker)
{
    talk_tags_scene_move(walker, TALK_TAGS_SLOT_FOCUS_FIRST);
}
CLEAN_AS(func_02069614, TalkTags_FocusFirst)

/* func_02069634 (tag 9/0): the focus is the player. */
void TalkTags_FocusPlayer(TalkTagsWalker *walker)
{
    talk_tags_scene_move(walker, TALK_TAGS_SLOT_FOCUS_PLAYER);
}
CLEAN_AS(func_02069634, TalkTags_FocusPlayer)

/* func_02069654 (tag 8/2): nothing. */
void TalkTags_Nothing8_2(void *walker)
{
    (void) walker;
}
CLEAN_AS(func_02069654, TalkTags_Nothing8_2)

/* func_02069658 (tag 8/1): nothing. */
void TalkTags_Nothing8_1(void *walker)
{
    (void) walker;
}
CLEAN_AS(func_02069658, TalkTags_Nothing8_1)

/* func_0206965c (tag 8/0): nothing. */
void TalkTags_Nothing8_0(void *walker)
{
    (void) walker;
}
CLEAN_AS(func_0206965c, TalkTags_Nothing8_0)

/* func_02069660 (tag 6/13): the tag's bytes are a species plus 1 and two messages: the second
 * when the villager talked to is not of that species, else the first. Without a villager, a
 * failure note and the first.
 *
 * QUIRK: the species byte 0 becomes 0xff, which no villager has. */
void TalkTags_BranchBySpecies(TalkTagsWalker *walker)
{
    u8 species;
    u8 messages[2];

    void *receiver = talk_tags_branch(walker, TALK_TAGS_BRANCH_SPECIES, 2);
    MessageTag_ReadThreeBytes(&walker->tag, &species, &messages[0], &messages[1]);
    species = (u8) (species - 1);

    u8 *villager = talk_tags_villager(receiver);
    int other = 0;
    if (villager != NULL) {
        if (VillagerData_Species(villager) != species) {
            other = 1;
        }
    } else {
        func_0206bb9c(walker, TALK_TAGS_NOTE_SPECIES, data_020df138);
    }
    talk_tags_go_to(walker, messages[other]);
}
CLEAN_AS(func_02069660, TalkTags_BranchBySpecies)

/* func_020696e4 (tag 6/12): the first message when this system's player lives in the town,
 * else the second. */
void TalkTags_BranchByResident(TalkTagsWalker *walker)
{
    u8 messages[2];

    talk_tags_branch(walker, TALK_TAGS_BRANCH_RESIDENT, 2);
    MessageTag_ReadTwoBytes(&walker->tag, &messages[0], &messages[1]);
    int visitor = PlayerRecords_IsTownNumber((u32) PlayerRecords_CurrentNumber()) != 1;
    talk_tags_go_to(walker, messages[visitor]);
}
CLEAN_AS(func_020696e4, TalkTags_BranchByResident)

/* func_0206973c (tag 6/11): seven messages, Monday to Sunday, by the weekday the talk began
 * on (0 is Sunday).
 *
 * REQUIRES: the weekday is 0 to 7 (Calendar_TodayWeekday gives 0 to 6); the ROM reads past
 * the messages for a larger one, where this takes the first. */
void TalkTags_BranchByWeekday(TalkTagsWalker *walker)
{
    u8 messages[7];

    talk_tags_branch(walker, TALK_TAGS_BRANCH_WEEKDAY, 7);
    MessageTag_ReadBytes(&walker->tag, messages, 7);
    u32 weekday = *(const u32 *) (const void *) talk_tags_at(walker, TALK_TAGS_WEEKDAY);
    int index = weekday == 0 ? 6 : (int) (weekday - 1);
    talk_tags_go_to(walker, index >= 0 && index < 7 ? messages[index] : messages[0]);
}
CLEAN_AS(func_0206973c, TalkTags_BranchByWeekday)

/* func_02069794 (tag 6/10): four messages by the number of the town's players (1 to 4 and
 * more). */
void TalkTags_BranchByPlayers(TalkTagsWalker *walker)
{
    u8 messages[4];

    talk_tags_branch(walker, TALK_TAGS_BRANCH_PLAYERS, 4);
    MessageTag_ReadFourBytes(&walker->tag, &messages[0], &messages[1], &messages[2], &messages[3]);
    int index = PlayerRecords_CountTown(data_021dc7a8.players) - 1;
    if (index < 0) {
        index = 0;
    } else if (index > 3) {
        index = 3;
    }
    talk_tags_go_to(walker, messages[index]);
}
CLEAN_AS(func_02069794, TalkTags_BranchByPlayers)

/* func_02069804 (tag 6/9): three messages: nothing falls, rain, snow (Sky_Falling). */
void TalkTags_BranchByFalling(TalkTagsWalker *walker)
{
    u8 messages[3];

    talk_tags_branch(walker, TALK_TAGS_BRANCH_FALLING, 3);
    MessageTag_ReadThreeBytes(&walker->tag, &messages[0], &messages[1], &messages[2]);
    int falling = Sky_Falling();
    int index = 0;
    if (falling == SKY_FALLING_RAIN) {
        index = 1;
    } else if (falling == SKY_FALLING_SNOW) {
        index = 2;
    }
    talk_tags_go_to(walker, messages[index]);
}
CLEAN_AS(func_02069804, TalkTags_BranchByFalling)

/* func_02069860 (tag 6/8): four messages by the part of the day the talk began in: morning,
 * afternoon, evening, night (any other value: the first). */
void TalkTags_BranchByPartOfDay(TalkTagsWalker *walker)
{
    u8 messages[4];

    talk_tags_branch(walker, TALK_TAGS_BRANCH_PART_OF_DAY, 4);
    MessageTag_ReadFourBytes(&walker->tag, &messages[0], &messages[1], &messages[2], &messages[3]);
    s32 part = *(const s32 *) (const void *) talk_tags_at(walker, TALK_TAGS_PART_OF_DAY);
    int index = 0;
    if (part == PART_OF_DAY_AFTERNOON) {
        index = 1;
    } else if (part == PART_OF_DAY_EVENING) {
        index = 2;
    } else if (part == PART_OF_DAY_NIGHT) {
        index = 3;
    }
    talk_tags_go_to(walker, messages[index]);
}
CLEAN_AS(func_02069860, TalkTags_BranchByPartOfDay)

/* func_020698d4 (tag 6/7): four messages by the town's villagers: at most data_020cd40c, one
 * more, from 8 on, and the counts between. */
void TalkTags_BranchByVillagers(TalkTagsWalker *walker)
{
    u8 messages[4];

    talk_tags_branch(walker, TALK_TAGS_BRANCH_VILLAGERS, 4);
    MessageTag_ReadFourBytes(&walker->tag, &messages[0], &messages[1], &messages[2], &messages[3]);
    int count = VillagerRoster_Count((VillagerTown *) (void *) data_021dc7a8.villagers);
    int few = data_020cd40c;
    int index;
    if (count <= few) {
        index = 0;
    } else if (count == few + 1) {
        index = 1;
    } else if (count >= 8) {
        index = 3;
    } else {
        index = 2;
    }
    talk_tags_go_to(walker, messages[index]);
}
CLEAN_AS(func_020698d4, TalkTags_BranchByVillagers)

/* Of three messages: all the kinds caught, at least 0x21, fewer. */
static int talk_tags_creatures_index(unsigned int count)
{
    if (count == TALK_TAGS_CREATURES_ALL) {
        return 2;
    }
    return count >= TALK_TAGS_CREATURES_MANY ? 1 : 0;
}

/* func_02069960 (tag 6/6): three messages by the kinds of fish caught. */
void TalkTags_BranchByFish(TalkTagsWalker *walker)
{
    u8 messages[3];

    talk_tags_branch(walker, TALK_TAGS_BRANCH_FISH, 3);
    MessageTag_ReadThreeBytes(&walker->tag, &messages[0], &messages[1], &messages[2]);
    talk_tags_go_to(walker, messages[talk_tags_creatures_index((unsigned int) ItemRecord_CountFish())]);
}
CLEAN_AS(func_02069960, TalkTags_BranchByFish)

/* func_020699c0 (tag 6/5): three messages by the kinds of insects caught. */
void TalkTags_BranchByInsects(TalkTagsWalker *walker)
{
    u8 messages[3];

    talk_tags_branch(walker, TALK_TAGS_BRANCH_INSECTS, 3);
    MessageTag_ReadThreeBytes(&walker->tag, &messages[0], &messages[1], &messages[2]);
    talk_tags_go_to(walker, messages[talk_tags_creatures_index((unsigned int) ItemRecord_CountInsects())]);
}
CLEAN_AS(func_020699c0, TalkTags_BranchByInsects)

/* func_02069a20 (tag 6/4): four messages by the size of the house: 0, 1 or 2, 3, larger. */
void TalkTags_BranchByHouse(TalkTagsWalker *walker)
{
    u8 messages[4];

    talk_tags_branch(walker, TALK_TAGS_BRANCH_HOUSE, 4);
    MessageTag_ReadFourBytes(&walker->tag, &messages[0], &messages[1], &messages[2], &messages[3]);
    unsigned int size = HouseRecord_Size(&data_021ebcd4);
    int index;
    if (size == 0) {
        index = 0;
    } else if (size <= 2) {
        index = 1;
    } else if (size == 3) {
        index = 2;
    } else {
        index = 3;
    }
    talk_tags_go_to(walker, messages[index]);
}
CLEAN_AS(func_02069a20, TalkTags_BranchByHouse)

/* func_02069a94 (tag 6/3): the first message when this system's player's kind (the byte 0x1c
 * of its id) is 0, else the second. */
void TalkTags_BranchByPlayerKind(TalkTagsWalker *walker)
{
    u8 messages[2];

    talk_tags_branch(walker, TALK_TAGS_BRANCH_PLAYER_KIND, 2);
    MessageTag_ReadTwoBytes(&walker->tag, &messages[0], &messages[1]);
    int other = func_020950c0(PlayerRecord_Player(PlayerRecords_Current())) != 0;
    talk_tags_go_to(walker, messages[other]);
}
CLEAN_AS(func_02069a94, TalkTags_BranchByPlayerKind)

/* func_02069af0 (tag 6/2): the tag's bytes are a fondness and two messages: the second when
 * the villager talked to remembers this system's player with less fondness, else the first
 * (also when it does not know the player). Without a villager, a failure note and the
 * first. */
void TalkTags_BranchByFondness(TalkTagsWalker *walker)
{
    u8 fondness;
    u8 messages[2];

    void *receiver = talk_tags_branch(walker, TALK_TAGS_BRANCH_FONDNESS, 2);
    MessageTag_ReadThreeBytes(&walker->tag, &fondness, &messages[0], &messages[1]);
    int index = 0;
    u8 *villager = talk_tags_villager(receiver);
    u8 *record = PlayerRecords_Current();
    if (villager != NULL) {
        VillagerMemory *memory = VillagerMemory_Of(villager, PlayerRecord_Player(record));
        if (memory != NULL && VillagerMemoryEntry_Fondness(memory) < fondness) {
            index = 1;
        }
    } else {
        func_0206bb9c(walker, TALK_TAGS_NOTE_FONDNESS, data_020df140);
    }
    talk_tags_go_to(walker, messages[index]);
}
CLEAN_AS(func_02069af0, TalkTags_BranchByFondness)

/* func_02069b80 (tag 6/1): one of three messages at random. */
void TalkTags_BranchRandom3(TalkTagsWalker *walker)
{
    u8 messages[3];

    talk_tags_branch(walker, TALK_TAGS_BRANCH_RANDOM3, 3);
    MessageTag_ReadThreeBytes(&walker->tag, &messages[0], &messages[1], &messages[2]);
    talk_tags_go_to(walker, messages[func_020644cc(3)]);
}
CLEAN_AS(func_02069b80, TalkTags_BranchRandom3)

/* func_02069bd0 (tag 6/0): one of two messages at random. */
void TalkTags_BranchRandom2(TalkTagsWalker *walker)
{
    u8 messages[2];

    talk_tags_branch(walker, TALK_TAGS_BRANCH_RANDOM2, 2);
    MessageTag_ReadTwoBytes(&walker->tag, &messages[0], &messages[1]);
    talk_tags_go_to(walker, messages[func_020644cc(2)]);
}
CLEAN_AS(func_02069bd0, TalkTags_BranchRandom2)

/* func_02069c1c (tag 5/5): the slider's four choices. Met first, the walk is taken back to
 * the tag and goes through a lone tag 1/1 (data_020cce98) before meeting it again. Met again,
 * the talk's answers are cleared and filled from the tag: a weight and the byte 0x70 of each
 * of the first four answers, then the texts of the first and the fifth; the walk goes past
 * those texts, four answers are counted, the slider window shows them and opens, and the
 * walker waits for the choice. */
void TalkTags_SliderChoices(TalkTagsWalker *walker)
{
    if (walker->choices_shown == 0) {
        MessageWalker_BackOverTag(&walker->base, (const u8 *) walker->tag.start);
        walker->choices_shown = 1;
        MessageWalker_Enter(&walker->base, (int) (uintptr_t) data_020cce98);
        return;
    }

    walker->choices_shown = 0;
    TalkAnswers *answers = func_0206837c(walker->talk);
    TalkAnswer *first = func_020ab550(answers, 0);
    TalkAnswer *second = func_020ab550(answers, 1);
    TalkAnswer *third = func_020ab550(answers, 2);
    TalkAnswer *fourth = func_020ab550(answers, 3);
    func_020ab5e4(answers);
    u8 *weight0 = func_020ab788(first);
    u8 *byte0 = func_020ab794(first);
    u8 *weight1 = func_020ab788(second);
    u8 *byte1 = func_020ab794(second);
    u8 *weight2 = func_020ab788(third);
    u8 *byte2 = func_020ab794(third);
    u8 *weight3 = func_020ab788(fourth);
    u8 *byte3 = func_020ab794(fourth);
    MessageTagText *text0 = func_020ab53c(answers);
    MessageTagText *text4 = (MessageTagText *) (void *) TalkAnswers_FifthText(answers);
    int texts = MessageTag_ReadEightBytesTwoTexts(&walker->tag, weight0, byte0, weight1, byte1, weight2, byte2, weight3, byte3,
                                                  text0, text4);
    MessageWalker_Skip(&walker->base, texts);
    TalkAnswers_SetCount(answers, 4);
    TalkWindows *windows = (TalkWindows *) (void *) talk_tags_at(walker, TALK_TAGS_WINDOWS);
    TalkWindows_ShowSlider(windows, answers);
    TalkWindows_Open(windows);
    walker->state = TALK_TAGS_STATE_CHOOSING;
}
CLEAN_AS(func_02069c1c, TalkTags_SliderChoices)

/* func_02069d24 (tag 4/34): the villager's boom (func_0206781c), without colours. */
void TalkTags_PutBoom(TalkTagsWalker *walker)
{
    talk_tags_put_loaded(walker, func_0206781c(walker->talk), TALK_TAGS_NOTE_BOOM, data_020df14c, TALK_TAGS_BOOM, -1, 1);
}
CLEAN_AS(func_02069d24, TalkTags_PutBoom)

/* func_02069d8c (tag 4/33): the villager's praise word (func_02067728), ending with colour 2. */
void TalkTags_PutPraise(TalkTagsWalker *walker)
{
    talk_tags_put_loaded(walker, func_02067728(walker->talk), TALK_TAGS_NOTE_PRAISE, data_020df154, TALK_TAGS_PRAISE,
                         TALK_TAGS_COLOUR_PRAISE, 1);
}
CLEAN_AS(func_02069d8c, TalkTags_PutPraise)

/* func_02069e10 (tag 4/32): nothing. */
void TalkTags_Nothing4_32(void) {}
CLEAN_AS(func_02069e10, TalkTags_Nothing4_32)

/* func_02069e14 (tag 4/31): the nickname the villager gives the player (func_0206777c). */
void TalkTags_PutNickname(TalkTagsWalker *walker)
{
    talk_tags_put_loaded(walker, func_0206777c(walker->talk), TALK_TAGS_NOTE_NICKNAME, data_020df160, TALK_TAGS_NICKNAME,
                         TALK_TAGS_COLOUR_PLAYER, 1);
}
CLEAN_AS(func_02069e14, TalkTags_PutNickname)

/* func_02069e98 (tag 4/30): the villager's impression (func_020677d0), without colours. */
void TalkTags_PutImpression(TalkTagsWalker *walker)
{
    talk_tags_put_loaded(walker, func_020677d0(walker->talk), TALK_TAGS_NOTE_IMPRESSION, data_020df170, TALK_TAGS_IMPRESSION,
                         -1, 1);
}
CLEAN_AS(func_02069e98, TalkTags_PutImpression)

/* func_02069f00 (tag 4/29): the talk's name 3. */
void TalkTags_PutName3(TalkTagsWalker *walker)
{
    func_0206b984(walker, 3);
}
CLEAN_AS(func_02069f00, TalkTags_PutName3)

/* func_02069f0c (tag 4/28): the talk's name 2. */
void TalkTags_PutName2(TalkTagsWalker *walker)
{
    func_0206b984(walker, 2);
}
CLEAN_AS(func_02069f0c, TalkTags_PutName2)

/* func_02069f18 (tag 4/27): the talk's name 1. */
void TalkTags_PutName1(TalkTagsWalker *walker)
{
    func_0206b984(walker, 1);
}
CLEAN_AS(func_02069f18, TalkTags_PutName1)

/* func_02069f24 (tag 4/26): the talk's name 0. */
void TalkTags_PutName0(TalkTagsWalker *walker)
{
    func_0206b984(walker, 0);
}
CLEAN_AS(func_02069f24, TalkTags_PutName0)

/* func_02069f30 (tag 4/25): the talk's part 10. */
void TalkTags_PutPart10(TalkTagsWalker *walker)
{
    func_0206ba08(walker, 10);
}
CLEAN_AS(func_02069f30, TalkTags_PutPart10)

/* func_02069f3c (tag 4/24): the talk's part 9. */
void TalkTags_PutPart9(TalkTagsWalker *walker)
{
    func_0206ba08(walker, 9);
}
CLEAN_AS(func_02069f3c, TalkTags_PutPart9)

/* func_02069f48 (tag 4/23): the talk's part 8. */
void TalkTags_PutPart8(TalkTagsWalker *walker)
{
    func_0206ba08(walker, 8);
}
CLEAN_AS(func_02069f48, TalkTags_PutPart8)

/* func_02069f54 (tag 4/22): the talk's part 7. */
void TalkTags_PutPart7(TalkTagsWalker *walker)
{
    func_0206ba08(walker, 7);
}
CLEAN_AS(func_02069f54, TalkTags_PutPart7)

/* func_02069f60 (tag 4/21): the talk's part 6. */
void TalkTags_PutPart6(TalkTagsWalker *walker)
{
    func_0206ba08(walker, 6);
}
CLEAN_AS(func_02069f60, TalkTags_PutPart6)

/* func_02069f6c (tag 4/20): the talk's part 5. */
void TalkTags_PutPart5(TalkTagsWalker *walker)
{
    func_0206ba08(walker, 5);
}
CLEAN_AS(func_02069f6c, TalkTags_PutPart5)

/* func_02069f78 (tag 4/19): the talk's part 4. */
void TalkTags_PutPart4(TalkTagsWalker *walker)
{
    func_0206ba08(walker, 4);
}
CLEAN_AS(func_02069f78, TalkTags_PutPart4)

/* func_02069f84 (tag 4/18): the talk's part 3. */
void TalkTags_PutPart3(TalkTagsWalker *walker)
{
    func_0206ba08(walker, 3);
}
CLEAN_AS(func_02069f84, TalkTags_PutPart3)

/* func_02069f90 (tag 4/17): the talk's part 2. */
void TalkTags_PutPart2(TalkTagsWalker *walker)
{
    func_0206ba08(walker, 2);
}
CLEAN_AS(func_02069f90, TalkTags_PutPart2)

/* func_02069f9c (tag 4/16): the talk's part 1. */
void TalkTags_PutPart1(TalkTagsWalker *walker)
{
    func_0206ba08(walker, 1);
}
CLEAN_AS(func_02069f9c, TalkTags_PutPart1)

/* func_02069fa8 (tag 4/15): the talk's part 0. */
void TalkTags_PutPart0(TalkTagsWalker *walker)
{
    func_0206ba08(walker, 0);
}
CLEAN_AS(func_02069fa8, TalkTags_PutPart0)

/* func_02069fb4 (tag 4/14): another resident's player name (func_0206786c), ending with colour
 * 5, or 6 when the talk's byte 0x1e76 is set. */
void TalkTags_PutOtherPlayer(TalkTagsWalker *walker)
{
    if (func_0206786c(walker->talk) == 0) {
        func_0206bb9c(walker, TALK_TAGS_NOTE_OTHER_PLAYER, data_020df178);
    }
    MessageWalker_Enter(&walker->base, MessageTag_ColourTag(walker->name_colour));
    MessageWalker_Enter(&walker->base, talk_tags_characters(talk_tags_at(walker, TALK_TAGS_OTHER_PLAYER)));
    int colour = *talk_tags_at(walker, TALK_TAGS_OTHER_COLOUR) != 0 ? TALK_TAGS_COLOUR_NPC : TALK_TAGS_COLOUR_PLAYER;
    MessageWalker_Enter(&walker->base, MessageTag_ColourTag(colour));
    MailParticles_TakeLastSyllable(
        (MailTextParticles *) (void *) talk_tags_at(walker, TALK_TAGS_PARTICLES),
        (const char *) (uintptr_t) talk_tags_characters(talk_tags_at(walker, TALK_TAGS_OTHER_PLAYER)));
    *(s32 *) (void *) talk_tags_at(walker, TALK_TAGS_RO_AFTER_RIEUL) = 0;
}
CLEAN_AS(func_02069fb4, TalkTags_PutOtherPlayer)

/* func_0206a048 (tag 4/13): a villager picked at random (func_020678f8). */
void TalkTags_PutRandomNpc(TalkTagsWalker *walker)
{
    talk_tags_put_loaded(walker, func_020678f8(walker->talk), TALK_TAGS_NOTE_RANDOM_NPC, data_020df188, TALK_TAGS_RANDOM_NPC,
                         TALK_TAGS_COLOUR_NPC, 0);
}
CLEAN_AS(func_0206a048, TalkTags_PutRandomNpc)

/* func_0206a0cc (tag 4/12): a villager the one talked to is on bad terms with (func_02067964). */
void TalkTags_PutDislikedNpc(TalkTagsWalker *walker)
{
    talk_tags_put_loaded(walker, func_02067964(walker->talk), TALK_TAGS_NOTE_DISLIKED_NPC, data_020df198,
                         TALK_TAGS_DISLIKED_NPC, TALK_TAGS_COLOUR_NPC, 0);
}
CLEAN_AS(func_0206a0cc, TalkTags_PutDislikedNpc)

/* func_0206a150 (tag 4/11): a villager the one talked to is on good terms with (func_020679b0). */
void TalkTags_PutLikedNpc(TalkTagsWalker *walker)
{
    talk_tags_put_loaded(walker, func_020679b0(walker->talk), TALK_TAGS_NOTE_LIKED_NPC, data_020df1a8, TALK_TAGS_LIKED_NPC,
                         TALK_TAGS_COLOUR_NPC, 0);
}
CLEAN_AS(func_0206a150, TalkTags_PutLikedNpc)

/* ---- Group 4 kinds 0 to 10, groups 0 to 3, 7 and 0xff, and the tables by group */

#include "message_query.h"
#include "ov004/member_pointer.h"
#include "sound.h"
#include "text_codes.h"

/* The parts of a talk used below. */
#define TALK_TAGS_INSTANT_COPY 0x1a49 /* a copy of the walker's TALK_TAGS_FLAG_INSTANT */
#define TALK_TAGS_PAUSED 0x1a4a       /* set by a pause; the walker clears it with each character */
#define TALK_TAGS_CATCHPHRASE 0x1c70  /* the villager's catchphrase (func_02067a74) */
#define TALK_TAGS_TOWN_NAME 0x1c8c    /* the town's name (func_02067a3c) */
#define TALK_TAGS_PLAYER_NAME 0x1cac  /* this system's player's name (func_020679fc) */
#define TALK_TAGS_REMEMBERED 0x1e4c   /* the text the villager remembers of the player (func_020676d0) */

/* The colour tag put after the town's name. */
#define TALK_TAGS_COLOUR_TOWN 8

/* The receiver's slots used below (empty in Base_02066994). */
#define TALK_TAGS_SLOT_1C 0x1c
#define TALK_TAGS_SLOT_20 0x20
#define TALK_TAGS_SLOT_24 0x24
#define TALK_TAGS_SLOT_28 0x28
#define TALK_TAGS_SLOT_2C 0x2c
#define TALK_TAGS_SLOT_30 0x30
#define TALK_TAGS_SLOT_TALK_STYLE 0x38 /* SceneBase_SetSpeakerTalkStyle */

/* The line number of the failure note of the catchphrase, and its label. */
#define TALK_TAGS_NOTE_CATCHPHRASE 0xc39
extern const char data_020df1b8[];

/* The talk's texts of the date and time it began (func_02067c20 kept them at 0x1a64 to
 * 0x1a70), each set and answered by these: the second, the minute (with its unit word), the
 * hour on a 12-hour clock, the weekday's name, the day, the month, and the year after "20". */
extern void *func_02067f74(u8 *talk);
extern void *func_02067fa4(u8 *talk);
extern void *func_02067fd4(u8 *talk);
extern void *func_02068010(u8 *talk);
extern void *func_02068034(u8 *talk);
extern void *func_02068058(u8 *talk);
extern void *func_0206807c(u8 *talk);
/* The town's name and this system's player's name (both answer 1), the villager's
 * catchphrase, and the text the villager remembers of the player: loaded into the talk; 0
 * when not. */
extern int func_02067a3c(u8 *talk);
extern int func_020679fc(u8 *talk);
extern int func_02067a74(u8 *talk);
extern int func_020676d0(u8 *talk);
/* The text of the receiver's name (the receiver plus 0x20). */
extern void *func_020668d4(void *receiver);
/* The talk's word 0x10 set. */
extern void func_020676c4(u8 *talk, int value);
/* The talk's window shaken: amplitude, its fall per frame (times 1.5), x and y scales. */
extern void func_02067f28(u8 *talk, s32 amplitude, s32 fall, s32 scale_x, s32 scale_y);

/* The tables of the handlers (function-local statics of the game, filled on the first call),
 * by group: the guard, the table, and the constants it is filled from. */
extern const MemberPointer __ptmf_null;
extern u32 data_021cda78;
extern MemberPointer data_021cdc84[11];
extern const MemberPointer data_020ded1c, data_020ded14, data_020de98c, data_020de85c, data_020decfc, data_020de984,
    data_020decec, data_020de97c, data_020decdc, data_020decd4, data_020deccc;
extern u32 data_021cda64;
extern MemberPointer data_021cde64[17];
extern const MemberPointer data_020decb4, data_020decac, data_020de95c, data_020dec9c, data_020dec94, data_020de89c,
    data_020de8a4, data_020dec7c, data_020dec74, data_020dec6c, data_020de93c, data_020dec5c, data_020dec54, data_020de92c,
    data_020de8bc, data_020dec3c, data_020de924;
extern u32 data_021cda80;
extern MemberPointer data_021cdbb4[8];
extern const MemberPointer data_020dec1c, data_020dec14, data_020de914, data_020de8d4, data_020debfc, data_020debf4,
    data_020debec, data_020de904;
extern u32 data_021cda90;
extern MemberPointer data_021cdaec[5];
extern const MemberPointer data_020de94c, data_020dea0c, data_020debbc, data_020debb4, data_020debac;
extern u32 data_021cda50;
extern MemberPointer data_021ce0c4[35];
extern const MemberPointer data_020deb94, data_020dea3c, data_020dea44, data_020deb7c, data_020deb74, data_020deb6c,
    data_020dea64, data_020deb5c, data_020deb54, data_020dea7c, data_020dea84, data_020deb3c, data_020deb34, data_020deb2c,
    data_020dea9c, data_020deb1c, data_020deb14, data_020deab4, data_020deacc, data_020deadc, data_020deae4, data_020deaf4,
    data_020deafc, data_020deb0c, data_020deb24, data_020deb4c, data_020deb84, data_020deba4, data_020debc4, data_020debd4,
    data_020debe4, data_020dec0c, data_020dec2c, data_020dec34, data_020dec4c;
extern u32 data_021cda68;
extern MemberPointer data_021cdbf4[8];
extern const MemberPointer data_020dece4, data_020ded04, data_020ded24, data_020ded34, data_020ded44, data_020ded9c,
    data_020deda4, data_020dedc4;
extern u32 data_021cda70;
extern MemberPointer data_021cddf4[14];
extern const MemberPointer data_020dee34, data_020dee4c, data_020dee64, data_020dee8c, data_020dea04, data_020de9fc,
    data_020de9f4, data_020de80c, data_020dedbc, data_020de9dc, data_020de9d4, data_020de824, data_020de9c4, data_020de9bc;
extern u32 data_021cda8c;
extern MemberPointer data_021cdabc[3];
extern const MemberPointer data_020de9a4, data_020de854, data_020de994;
extern u32 data_021cda6c;
extern MemberPointer data_021cdc34[10];
extern const MemberPointer data_020de87c, data_020de974, data_020de96c, data_020de964, data_020de894, data_020de954,
    data_020de8ac, data_020de944, data_020de8b4, data_020de934;
extern u32 data_021cda60;
extern MemberPointer data_021cda9c[1];
extern const MemberPointer data_020de8cc;
extern u32 data_021cda7c;
extern MemberPointer data_021ce01c[21];
extern const MemberPointer data_020de8fc, data_020de90c, data_020de91c, data_020dea14, data_020dea1c, data_020dea24,
    data_020dea34, data_020dea4c, data_020dea5c, data_020dea6c, data_020dea74, data_020dea8c, data_020dea94, data_020deaa4,
    data_020deaac, data_020dead4, data_020deaec, data_020deb04, data_020deb44, data_020deb8c, data_020debcc;
extern u32 data_021cda74;
extern MemberPointer data_021cdad4[3];
extern const MemberPointer data_020dec64, data_020deca4;

typedef void *TalkTagsTextFunction(u8 *talk);
typedef void TalkTagsIntSlot(void *receiver, int value);

/* The receiver's slot `slot` handed `value`. */
static void talk_tags_tell(void *receiver, u32 slot, int value)
{
    ((TalkTagsIntSlot *) (uintptr_t) talk_tags_slot(receiver, slot))(receiver, value);
}

/* The receiver's slot `slot` handed the tag's first byte. */
static void talk_tags_tell_byte(TalkTagsWalker *walker, u32 slot)
{
    u8 value;
    void *receiver = talk_tags_receiver(walker);
    MessageTag_GetFirstByte(&walker->tag, &value);
    talk_tags_tell(receiver, slot, value);
}

/* The receiver's slot 0x1c handed `value`, after the tag's empty func_020a8750. */
static void talk_tags_tell_1c(TalkTagsWalker *walker, int value)
{
    void *receiver = talk_tags_receiver(walker);
    MessageTag_Destruct(&walker->tag);
    talk_tags_tell(receiver, TALK_TAGS_SLOT_1C, value);
}

/* The text `text` sets in the talk walked in place of the tag, without colours; it is set
 * again for its last syllable, and the particles' ro_after_rieul set. */
static void talk_tags_put_set_text(TalkTagsWalker *walker, TalkTagsTextFunction *text)
{
    MessageWalker_Enter(&walker->base, talk_tags_characters(text(walker->talk)));
    MailParticles_TakeLastSyllable((MailTextParticles *) (void *) talk_tags_at(walker, TALK_TAGS_PARTICLES),
                                   (const char *) (uintptr_t) talk_tags_characters(text(walker->talk)));
    *(s32 *) (void *) talk_tags_at(walker, TALK_TAGS_RO_AFTER_RIEUL) = 1;
}

/* The choices read from the tag (`bytes` of texts after it) shown: the walk goes past those
 * texts, `count` answers are counted, the choice window shows them and opens, and the walker
 * waits for the choice. */
static void talk_tags_show_choices(TalkTagsWalker *walker, TalkAnswers *answers, int bytes, int count)
{
    MessageWalker_Skip(&walker->base, bytes);
    TalkAnswers_SetCount(answers, count);
    TalkWindows *windows = (TalkWindows *) (void *) talk_tags_at(walker, TALK_TAGS_WINDOWS);
    TalkWindows_ShowChoices(windows, answers);
    TalkWindows_Open(windows);
    walker->state = TALK_TAGS_STATE_CHOOSING;
}

/* The talk's answers: the first `count` (at most 5) taken, all cleared, and the byte 0x70 and
 * the text of each of those. */
static TalkAnswers *talk_tags_clear_answers(TalkTagsWalker *walker, int count, u8 **bytes, MessageTagText **texts)
{
    TalkAnswer *answer[5];
    TalkAnswers *answers = func_0206837c(walker->talk);
    for (int i = 0; i < count; i++) {
        answer[i] = TalkAnswers_Answer(answers, i);
    }
    TalkAnswers_Clear(answers);
    for (int i = 0; i < count; i++) {
        bytes[i] = TalkAnswers_Answer70(answer[i]);
        texts[i] = (MessageTagText *) (void *) TalkAnswers_Text(answer[i]);
    }
    return answers;
}

/* The handler of the tag's kind in a group's table (filled on the first call).
 * REQUIRES: the kind is within the table (the ROM indexes it unchecked). */
static void talk_tags_dispatch(TalkTagsWalker *walker, u32 *guard, MemberPointer *table, const MemberPointer *const *constants,
                               int count)
{
    MemberTable_InitOnce(guard, table, constants, count);
    MemberPointer_CallVoid(&table[walker->tag.kind], walker);
}

/* func_0206a1d4 (tag 4/10): the second the talk began at. */
void TalkTags_PutSecond(TalkTagsWalker *walker)
{
    talk_tags_put_set_text(walker, func_02067f74);
}
CLEAN_AS(func_0206a1d4, TalkTags_PutSecond)

/* func_0206a21c (tag 4/9): the minute, with its unit word. */
void TalkTags_PutMinute(TalkTagsWalker *walker)
{
    talk_tags_put_set_text(walker, func_02067fa4);
}
CLEAN_AS(func_0206a21c, TalkTags_PutMinute)

/* func_0206a264 (tag 4/8): the hour on a 12-hour clock (12 for 0 and 12). */
void TalkTags_PutHour12(TalkTagsWalker *walker)
{
    talk_tags_put_set_text(walker, func_02067fd4);
}
CLEAN_AS(func_0206a264, TalkTags_PutHour12)

/* func_0206a2ac (tag 4/7): the weekday's name. */
void TalkTags_PutWeekday(TalkTagsWalker *walker)
{
    talk_tags_put_set_text(walker, func_02068010);
}
CLEAN_AS(func_0206a2ac, TalkTags_PutWeekday)

/* func_0206a2f4 (tag 4/6): the day of the month. */
void TalkTags_PutDay(TalkTagsWalker *walker)
{
    talk_tags_put_set_text(walker, func_02068034);
}
CLEAN_AS(func_0206a2f4, TalkTags_PutDay)

/* func_0206a33c (tag 4/5): the month. */
void TalkTags_PutMonth(TalkTagsWalker *walker)
{
    talk_tags_put_set_text(walker, func_02068058);
}
CLEAN_AS(func_0206a33c, TalkTags_PutMonth)

/* func_0206a384 (tag 4/4): the year, in four digits. */
void TalkTags_PutYear(TalkTagsWalker *walker)
{
    talk_tags_put_set_text(walker, func_0206807c);
}
CLEAN_AS(func_0206a384, TalkTags_PutYear)

/* func_0206a3cc (tag 4/3): the town's name, ending with colour 8. */
void TalkTags_PutTownName(TalkTagsWalker *walker)
{
    func_02067a3c(walker->talk);
    talk_tags_put_loaded(walker, 1, 0, NULL, TALK_TAGS_TOWN_NAME, TALK_TAGS_COLOUR_TOWN, 0);
}
CLEAN_AS(func_0206a3cc, TalkTags_PutTownName)

/* func_0206a438 (tag 4/2): the catchphrase of the villager talked to, without colours. */
void TalkTags_PutCatchphrase(TalkTagsWalker *walker)
{
    talk_tags_put_loaded(walker, func_02067a74(walker->talk), TALK_TAGS_NOTE_CATCHPHRASE, data_020df1b8, TALK_TAGS_CATCHPHRASE,
                         -1, 0);
}
CLEAN_AS(func_0206a438, TalkTags_PutCatchphrase)

/* func_0206a4a0 (tag 4/1): the name of the receiver (the one talked to), ending with colour
 * 6. */
void TalkTags_PutReceiverName(TalkTagsWalker *walker)
{
    MessageWalker_Enter(&walker->base, MessageTag_ColourTag(walker->name_colour));
    void *receiver = talk_tags_receiver(walker);
    MessageWalker_Enter(&walker->base, talk_tags_characters(func_020668d4(receiver)));
    MessageWalker_Enter(&walker->base, MessageTag_ColourTag(TALK_TAGS_COLOUR_NPC));
    MailParticles_TakeLastSyllable((MailTextParticles *) (void *) talk_tags_at(walker, TALK_TAGS_PARTICLES),
                                   (const char *) (uintptr_t) talk_tags_characters(func_020668d4(receiver)));
    *(s32 *) (void *) talk_tags_at(walker, TALK_TAGS_RO_AFTER_RIEUL) = 0;
}
CLEAN_AS(func_0206a4a0, TalkTags_PutReceiverName)

/* func_0206a510 (tag 4/0): this system's player's name, ending with colour 5. */
void TalkTags_PutPlayerName(TalkTagsWalker *walker)
{
    func_020679fc(walker->talk);
    talk_tags_put_loaded(walker, 1, 0, NULL, TALK_TAGS_PLAYER_NAME, TALK_TAGS_COLOUR_PLAYER, 0);
}
CLEAN_AS(func_0206a510, TalkTags_PutPlayerName)

/* func_0206a57c (tag 3/4): the receiver's slot 0x30 handed the tag's first byte. */
void TalkTags_TellReceiver30(TalkTagsWalker *walker)
{
    talk_tags_tell_byte(walker, TALK_TAGS_SLOT_30);
}
CLEAN_AS(func_0206a57c, TalkTags_TellReceiver30)

/* func_0206a5a8 (tag 3/3): the receiver's slot 0x2c handed the tag's first byte. */
void TalkTags_TellReceiver2c(TalkTagsWalker *walker)
{
    talk_tags_tell_byte(walker, TALK_TAGS_SLOT_2C);
}
CLEAN_AS(func_0206a5a8, TalkTags_TellReceiver2c)

/* func_0206a5d4 (tag 3/2): the receiver's slot 0x28 handed the tag's first byte. */
void TalkTags_TellReceiver28(TalkTagsWalker *walker)
{
    talk_tags_tell_byte(walker, TALK_TAGS_SLOT_28);
}
CLEAN_AS(func_0206a5d4, TalkTags_TellReceiver28)

/* func_0206a600 (tag 3/1): the receiver's slot 0x24 handed the tag's first byte. */
void TalkTags_TellReceiver24(TalkTagsWalker *walker)
{
    talk_tags_tell_byte(walker, TALK_TAGS_SLOT_24);
}
CLEAN_AS(func_0206a600, TalkTags_TellReceiver24)

/* func_0206a62c (tag 3/0): the receiver's slot 0x20, after the tag's empty func_020a8750. */
void TalkTags_TellReceiver20(TalkTagsWalker *walker)
{
    talk_tags_scene_move(walker, TALK_TAGS_SLOT_20);
}
CLEAN_AS(func_0206a62c, TalkTags_TellReceiver20)

/* func_0206a64c (tag 2/7): five choices, the last also the one B picks. */
void TalkTags_FiveChoicesCancelLast(TalkTagsWalker *walker)
{
    TalkTags_FiveChoices(walker);
    TalkAnswers_SetCancelToLast(func_0206837c(walker->talk));
}
CLEAN_AS(func_0206a64c, TalkTags_FiveChoicesCancelLast)

/* func_0206a664 (tag 2/6): four choices, the last also the one B picks. */
void TalkTags_FourChoicesCancelLast(TalkTagsWalker *walker)
{
    TalkTags_FourChoices(walker);
    TalkAnswers_SetCancelToLast(func_0206837c(walker->talk));
}
CLEAN_AS(func_0206a664, TalkTags_FourChoicesCancelLast)

/* func_0206a67c (tag 2/5): three choices, the last also the one B picks. */
void TalkTags_ThreeChoicesCancelLast(TalkTagsWalker *walker)
{
    TalkTags_ThreeChoices(walker);
    TalkAnswers_SetCancelToLast(func_0206837c(walker->talk));
}
CLEAN_AS(func_0206a67c, TalkTags_ThreeChoicesCancelLast)

/* func_0206a694 (tag 2/4): two choices, the last also the one B picks. */
void TalkTags_TwoChoicesCancelLast(TalkTagsWalker *walker)
{
    TalkTags_TwoChoices(walker);
    TalkAnswers_SetCancelToLast(func_0206837c(walker->talk));
}
CLEAN_AS(func_0206a694, TalkTags_TwoChoicesCancelLast)

/* func_0206a6ac (tag 2/3): five choices: the talk's answers cleared and set from the tag's
 * five texts (with a byte 0x70 each), then shown. */
void TalkTags_FiveChoices(TalkTagsWalker *walker)
{
    u8 *bytes[5];
    MessageTagText *texts[5];
    TalkAnswers *answers = talk_tags_clear_answers(walker, 5, bytes, texts);
    int read = MessageTag_ReadFiveTexts(&walker->tag, bytes[0], texts[0], bytes[1], texts[1], bytes[2], texts[2], bytes[3],
                                        texts[3], bytes[4], texts[4]);
    talk_tags_show_choices(walker, answers, read, 5);
}
CLEAN_AS(func_0206a6ac, TalkTags_FiveChoices)

/* func_0206a790 (tag 2/2): four choices, likewise. */
void TalkTags_FourChoices(TalkTagsWalker *walker)
{
    u8 *bytes[4];
    MessageTagText *texts[4];
    TalkAnswers *answers = talk_tags_clear_answers(walker, 4, bytes, texts);
    int read =
        MessageTag_ReadFourTexts(&walker->tag, bytes[0], texts[0], bytes[1], texts[1], bytes[2], texts[2], bytes[3], texts[3]);
    talk_tags_show_choices(walker, answers, read, 4);
}
CLEAN_AS(func_0206a790, TalkTags_FourChoices)

/* func_0206a854 (tag 2/1): three choices, likewise. */
void TalkTags_ThreeChoices(TalkTagsWalker *walker)
{
    u8 *bytes[3];
    MessageTagText *texts[3];
    TalkAnswers *answers = talk_tags_clear_answers(walker, 3, bytes, texts);
    int read = MessageTag_ReadThreeTexts(&walker->tag, bytes[0], texts[0], bytes[1], texts[1], bytes[2], texts[2]);
    talk_tags_show_choices(walker, answers, read, 3);
}
CLEAN_AS(func_0206a854, TalkTags_ThreeChoices)

/* func_0206a8f4 (tag 2/0): two choices, likewise. */
void TalkTags_TwoChoices(TalkTagsWalker *walker)
{
    u8 *bytes[2];
    MessageTagText *texts[2];
    TalkAnswers *answers = talk_tags_clear_answers(walker, 2, bytes, texts);
    int read = (int) MessageTag_ReadTwoTexts(&walker->tag, bytes[0], texts[0], bytes[1], texts[1]);
    talk_tags_show_choices(walker, answers, read, 2);
}
CLEAN_AS(func_0206a8f4, TalkTags_TwoChoices)

/* func_0206a978 (tag 1/16): the talk's word 0x10 set to the tag's first byte. */
void TalkTags_SetTalkWord10(TalkTagsWalker *walker)
{
    u8 value;
    MessageTag_GetFirstByte(&walker->tag, &value);
    func_020676c4(walker->talk, value);
}
CLEAN_AS(func_0206a978, TalkTags_SetTalkWord10)

/* func_0206a998 (tag 1/15): the receiver's slot 0x1c handed 4. */
void TalkTags_Receiver1cWith4(TalkTagsWalker *walker)
{
    talk_tags_tell_1c(walker, 4);
}
CLEAN_AS(func_0206a998, TalkTags_Receiver1cWith4)

/* func_0206a9bc (tag 1/14): the receiver's slot 0x1c handed 3. */
void TalkTags_Receiver1cWith3(TalkTagsWalker *walker)
{
    talk_tags_tell_1c(walker, 3);
}
CLEAN_AS(func_0206a9bc, TalkTags_Receiver1cWith3)

/* func_0206a9e0 (tag 1/13): the receiver's slot 0x1c handed 2. */
void TalkTags_Receiver1cWith2(TalkTagsWalker *walker)
{
    talk_tags_tell_1c(walker, 2);
}
CLEAN_AS(func_0206a9e0, TalkTags_Receiver1cWith2)

/* func_0206aa04 (tag 1/12): the receiver's slot 0x1c handed 1. */
void TalkTags_Receiver1cWith1(TalkTagsWalker *walker)
{
    talk_tags_tell_1c(walker, 1);
}
CLEAN_AS(func_0206aa04, TalkTags_Receiver1cWith1)

/* func_0206aa28 (tag 1/11): the receiver's slot 0x1c handed 0. */
void TalkTags_Receiver1cWith0(TalkTagsWalker *walker)
{
    talk_tags_tell_1c(walker, 0);
}
CLEAN_AS(func_0206aa28, TalkTags_Receiver1cWith0)

/* func_0206aa4c (tag 1/10): sound effect 8, and the window shaken hard. */
void TalkTags_ShakeStrong(TalkTagsWalker *walker)
{
    SoundSys_PlaySe(8);
    func_02067f28(walker->talk, 0x11000, 0xa66, 0xccc, 0x1000);
}
CLEAN_AS(func_0206aa4c, TalkTags_ShakeStrong)

/* func_0206aa80 (tag 1/9): sound effect 7, and the window shaken. */
void TalkTags_ShakeMedium(TalkTagsWalker *walker)
{
    SoundSys_PlaySe(7);
    func_02067f28(walker->talk, 0xa000, 0x800, 0x800, 0x1333);
}
CLEAN_AS(func_0206aa80, TalkTags_ShakeMedium)

/* func_0206aab0 (tag 1/8): sound effect 6, and the window shaken lightly. */
void TalkTags_ShakeLight(TalkTagsWalker *walker)
{
    SoundSys_PlaySe(6);
    func_02067f28(walker->talk, 0x6000, 0x666, 0x4cc, 0x1199);
}
CLEAN_AS(func_0206aab0, TalkTags_ShakeLight)

/* func_0206aae4 (tag 1/7): nothing; it ends the text tag 1/6 may replace. */
void TalkTags_RememberedEnd(void) {}
CLEAN_AS(func_0206aae4, TalkTags_RememberedEnd)

/* func_0206aae8 (tag 1/6): when a tag 1/7 follows and the villager talked to remembers a text
 * of the player, the walk goes on at that tag 1/7 and that text is walked in place of what
 * was between them. */
void TalkTags_RememberedText(TalkTagsWalker *walker)
{
    int position = (int) walker->base.position;
    int end = MessageQuery_FindTag(position, 1, 7);
    if (end == 0) {
        return;
    }
    if (func_020676d0(walker->talk) == 0) {
        return;
    }
    MessageWalker_Skip(&walker->base, end - position);
    MessageWalker_Enter(&walker->base, talk_tags_characters(talk_tags_at(walker, TALK_TAGS_REMEMBERED)));
}
CLEAN_AS(func_0206aae8, TalkTags_RememberedText)

/* func_0206ab30 (tag 1/5): the walk can be hurried again. */
void TalkTags_HurryAllowed(TalkTagsWalker *walker)
{
    MessageTag_Destruct(&walker->tag);
    walker->unk_4c[TALK_TAGS_FLAG_NO_HURRY] = 0;
}
CLEAN_AS(func_0206ab30, TalkTags_HurryAllowed)

/* func_0206ab48 (tag 1/4): the walk cannot be hurried. */
void TalkTags_HurryForbidden(TalkTagsWalker *walker)
{
    MessageTag_Destruct(&walker->tag);
    walker->unk_4c[TALK_TAGS_FLAG_NO_HURRY] = 1;
}
CLEAN_AS(func_0206ab48, TalkTags_HurryForbidden)

/* func_0206ab60 (tag 1/3): the text is shown a character at a time again. */
void TalkTags_InstantOff(TalkTagsWalker *walker)
{
    MessageTag_Destruct(&walker->tag);
    walker->unk_4c[TALK_TAGS_FLAG_INSTANT] = 0;
    *talk_tags_at(walker, TALK_TAGS_INSTANT_COPY) = 0;
}
CLEAN_AS(func_0206ab60, TalkTags_InstantOff)

/* func_0206ab84 (tag 1/2): the text is shown whole at once. */
void TalkTags_InstantOn(TalkTagsWalker *walker)
{
    MessageTag_Destruct(&walker->tag);
    walker->unk_4c[TALK_TAGS_FLAG_INSTANT] = 1;
    *talk_tags_at(walker, TALK_TAGS_INSTANT_COPY) = 1;
}
CLEAN_AS(func_0206ab84, TalkTags_InstantOn)

/* func_0206aba8 (tag 1/1): the walk stops, the window kept. */
void TalkTags_StopKeepWindow(TalkTagsWalker *walker)
{
    MessageTag_Destruct(&walker->tag);
    walker->state = TALK_TAGS_STATE_STOP_KEEP;
}
CLEAN_AS(func_0206aba8, TalkTags_StopKeepWindow)

/* func_0206abbc (tag 1/0): a pause of the tag's first halfword in frames (as 20.12 fixed
 * point; the walker takes 1.5 off at each step), and the talk's byte 0x1a4a set. */
void TalkTags_Pause(TalkTagsWalker *walker)
{
    u16 frames;
    MessageTag_GetFirstHalf(&walker->tag, &frames);
    walker->unk_58 = (s32) ((u32) frames << 12);
    *talk_tags_at(walker, TALK_TAGS_PAUSED) = 1;
}
CLEAN_AS(func_0206abbc, TalkTags_Pause)

/* func_0206abe8 (tag 0/8): a "{" walked in place of the tag. */
void TalkTags_PutLeftBrace(TalkTagsWalker *walker)
{
    MessageWalker_Enter(&walker->base, TextCodes_LeftBrace());
}
CLEAN_AS(func_0206abe8, TalkTags_PutLeftBrace)

/* func_0206ac00 (tag 0/7): a "%". */
void TalkTags_PutPercent(TalkTagsWalker *walker)
{
    MessageWalker_Enter(&walker->base, TextCodes_Percent());
}
CLEAN_AS(func_0206ac00, TalkTags_PutPercent)

/* func_0206ac18 (tag 0/6): a "&". */
void TalkTags_PutAmpersand(TalkTagsWalker *walker)
{
    MessageWalker_Enter(&walker->base, TextCodes_Ampersand());
}
CLEAN_AS(func_0206ac18, TalkTags_PutAmpersand)

/* func_0206ac30 (tag 0/1): a "/". */
void TalkTags_PutSlash(TalkTagsWalker *walker)
{
    MessageWalker_Enter(&walker->base, TextCodes_Slash());
}
CLEAN_AS(func_0206ac30, TalkTags_PutSlash)

/* func_0206ac48 (tag 0/0): a "*". */
void TalkTags_PutAsterisk(TalkTagsWalker *walker)
{
    MessageWalker_Enter(&walker->base, TextCodes_Asterisk());
}
CLEAN_AS(func_0206ac48, TalkTags_PutAsterisk)

/* func_0206ac60: nothing (the handler of many kinds of groups 0, 5 and 11). */
void TalkTags_Nothing(void) {}
CLEAN_AS(func_0206ac60, TalkTags_Nothing)

/* func_0206ac64 (group 0xff): kind 0 func_020692c8, kind 2 func_02069270.
 * REQUIRES: the kind is 0 or 2: kind 1 is the null member pointer, which the ROM calls (at
 * address 0). */
void TalkTags_DispatchGroupFF(TalkTagsWalker *walker)
{
    static const MemberPointer *const constants[3] = {&data_020dec64, &__ptmf_null, &data_020deca4};
    talk_tags_dispatch(walker, &data_021cda74, data_021cdad4, constants, 3);
}
CLEAN_AS(func_0206ac64, TalkTags_DispatchGroupFF)

/* func_0206ace4 (group 11): kinds 0 to 20 (kind 0 TalkTags_Nothing, 1 to 7 the walker's
 * settings, then func_02069498 down to func_020692f8). */
void TalkTags_DispatchGroup11(TalkTagsWalker *walker)
{
    static const MemberPointer *const constants[21] = {
        &data_020de8fc, &data_020de90c, &data_020de91c, &data_020dea14, &data_020dea1c, &data_020dea24, &data_020dea34,
        &data_020dea4c, &data_020dea5c, &data_020dea6c, &data_020dea74, &data_020dea8c, &data_020dea94, &data_020deaa4,
        &data_020deaac, &data_020dead4, &data_020deaec, &data_020deb04, &data_020deb44, &data_020deb8c, &data_020debcc,
    };
    talk_tags_dispatch(walker, &data_021cda7c, data_021ce01c, constants, 21);
}
CLEAN_AS(func_0206ace4, TalkTags_DispatchGroup11)

/* func_0206ae64 (group 10): kind 0 only (TalkTags_Nothing10_0). */
void TalkTags_DispatchGroup10(TalkTagsWalker *walker)
{
    static const MemberPointer *const constants[1] = {&data_020de8cc};
    talk_tags_dispatch(walker, &data_021cda60, data_021cda9c, constants, 1);
}
CLEAN_AS(func_0206ae64, TalkTags_DispatchGroup10)

/* func_0206aec4 (group 9): kinds 0 to 9, the scene's moves (TalkTags_FocusPlayer to
 * TalkTags_PassTurn). */
void TalkTags_DispatchGroup9(TalkTagsWalker *walker)
{
    static const MemberPointer *const constants[10] = {
        &data_020de87c, &data_020de974, &data_020de96c, &data_020de964, &data_020de894,
        &data_020de954, &data_020de8ac, &data_020de944, &data_020de8b4, &data_020de934,
    };
    talk_tags_dispatch(walker, &data_021cda6c, data_021cdc34, constants, 10);
}
CLEAN_AS(func_0206aec4, TalkTags_DispatchGroup9)

/* func_0206afa4 (group 8): kinds 0 to 2, which do nothing. */
void TalkTags_DispatchGroup8(TalkTagsWalker *walker)
{
    static const MemberPointer *const constants[3] = {&data_020de9a4, &data_020de854, &data_020de994};
    talk_tags_dispatch(walker, &data_021cda8c, data_021cdabc, constants, 3);
}
CLEAN_AS(func_0206afa4, TalkTags_DispatchGroup8)

/* func_0206b024 (group 7): the speaker takes the talking motion in the style the tag's kind
 * gives (the receiver's slot 0x38, after the tag's empty func_020a8750). */
void TalkTags_SpeakerTalkStyle(TalkTagsWalker *walker)
{
    int style = (int) walker->tag.kind;
    void *receiver = talk_tags_receiver(walker);
    MessageTag_Destruct(&walker->tag);
    talk_tags_tell(receiver, TALK_TAGS_SLOT_TALK_STYLE, style);
}
CLEAN_AS(func_0206b024, TalkTags_SpeakerTalkStyle)

/* func_0206b04c (group 6): kinds 0 to 13, the branches (TalkTags_BranchRandom2 to
 * TalkTags_BranchBySpecies). */
void TalkTags_DispatchGroup6(TalkTagsWalker *walker)
{
    static const MemberPointer *const constants[14] = {
        &data_020dee34, &data_020dee4c, &data_020dee64, &data_020dee8c, &data_020dea04, &data_020de9fc, &data_020de9f4,
        &data_020de80c, &data_020dedbc, &data_020de9dc, &data_020de9d4, &data_020de824, &data_020de9c4, &data_020de9bc,
    };
    talk_tags_dispatch(walker, &data_021cda70, data_021cddf4, constants, 14);
}
CLEAN_AS(func_0206b04c, TalkTags_DispatchGroup6)

/* func_0206b164 (group 5): kinds 0 to 7: kind 5 TalkTags_SliderChoices, the others nothing. */
void TalkTags_DispatchGroup5(TalkTagsWalker *walker)
{
    static const MemberPointer *const constants[8] = {
        &data_020dece4, &data_020ded04, &data_020ded24, &data_020ded34,
        &data_020ded44, &data_020ded9c, &data_020deda4, &data_020dedc4,
    };
    talk_tags_dispatch(walker, &data_021cda68, data_021cdbf4, constants, 8);
}
CLEAN_AS(func_0206b164, TalkTags_DispatchGroup5)

/* func_0206b228 (group 4): kinds 0 to 34, the texts walked in place of the tag
 * (TalkTags_PutPlayerName to TalkTags_PutBoom). */
void TalkTags_DispatchGroup4(TalkTagsWalker *walker)
{
    static const MemberPointer *const constants[35] = {
        &data_020deb94, &data_020dea3c, &data_020dea44, &data_020deb7c, &data_020deb74, &data_020deb6c, &data_020dea64,
        &data_020deb5c, &data_020deb54, &data_020dea7c, &data_020dea84, &data_020deb3c, &data_020deb34, &data_020deb2c,
        &data_020dea9c, &data_020deb1c, &data_020deb14, &data_020deab4, &data_020deacc, &data_020deadc, &data_020deae4,
        &data_020deaf4, &data_020deafc, &data_020deb0c, &data_020deb24, &data_020deb4c, &data_020deb84, &data_020deba4,
        &data_020debc4, &data_020debd4, &data_020debe4, &data_020dec0c, &data_020dec2c, &data_020dec34, &data_020dec4c,
    };
    talk_tags_dispatch(walker, &data_021cda50, data_021ce0c4, constants, 35);
}
CLEAN_AS(func_0206b228, TalkTags_DispatchGroup4)

/* func_0206b474 (group 3): kinds 0 to 4 (TalkTags_TellReceiver20 to TalkTags_TellReceiver30). */
void TalkTags_DispatchGroup3(TalkTagsWalker *walker)
{
    static const MemberPointer *const constants[5] = {
        &data_020de94c, &data_020dea0c, &data_020debbc, &data_020debb4, &data_020debac,
    };
    talk_tags_dispatch(walker, &data_021cda90, data_021cdaec, constants, 5);
}
CLEAN_AS(func_0206b474, TalkTags_DispatchGroup3)

/* func_0206b510 (group 2): kinds 0 to 7, the choices (TalkTags_TwoChoices to
 * TalkTags_FiveChoicesCancelLast). Met first, the walk is taken back to the tag and goes
 * through a lone tag 1/1 (data_020cce98) before meeting it again; met again, the kind's
 * handler runs.
 * REQUIRES: the kind is 0 to 7 (the ROM indexes its table unchecked). */
void TalkTags_DispatchGroup2(TalkTagsWalker *walker)
{
    static const MemberPointer *const constants[8] = {
        &data_020dec1c, &data_020dec14, &data_020de914, &data_020de8d4,
        &data_020debfc, &data_020debf4, &data_020debec, &data_020de904,
    };
    MemberTable_InitOnce(&data_021cda80, data_021cdbb4, constants, 8);
    const MemberPointer *handler = &data_021cdbb4[walker->tag.kind];
    if (walker->choices_shown != 0) {
        walker->choices_shown = 0;
        MemberPointer_CallVoid(handler, walker);
    } else {
        MessageWalker_BackOverTag(&walker->base, (const u8 *) walker->tag.start);
        walker->choices_shown = 1;
        MessageWalker_Enter(&walker->base, (int) (uintptr_t) data_020cce98);
    }
}
CLEAN_AS(func_0206b510, TalkTags_DispatchGroup2)

/* func_0206b608 (group 1): kinds 0 to 16, the walk's own tags (TalkTags_Pause to
 * TalkTags_SetTalkWord10). */
void TalkTags_DispatchGroup1(TalkTagsWalker *walker)
{
    static const MemberPointer *const constants[17] = {
        &data_020decb4, &data_020decac, &data_020de95c, &data_020dec9c, &data_020dec94, &data_020de89c,
        &data_020de8a4, &data_020dec7c, &data_020dec74, &data_020dec6c, &data_020de93c, &data_020dec5c,
        &data_020dec54, &data_020de92c, &data_020de8bc, &data_020dec3c, &data_020de924,
    };
    talk_tags_dispatch(walker, &data_021cda64, data_021cde64, constants, 17);
}
CLEAN_AS(func_0206b608, TalkTags_DispatchGroup1)

/* func_0206b750 (group 0): kinds 0 to 10, the characters put as themselves (kinds 0, 1 and 6
 * to 8), the others nothing. */
void TalkTags_DispatchGroup0(TalkTagsWalker *walker)
{
    static const MemberPointer *const constants[11] = {
        &data_020ded1c, &data_020ded14, &data_020de98c, &data_020de85c, &data_020decfc, &data_020de984,
        &data_020decec, &data_020de97c, &data_020decdc, &data_020decd4, &data_020deccc,
    };
    talk_tags_dispatch(walker, &data_021cda78, data_021cdc84, constants, 11);
}
CLEAN_AS(func_0206b750, TalkTags_DispatchGroup0)
