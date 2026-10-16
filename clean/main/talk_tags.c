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
