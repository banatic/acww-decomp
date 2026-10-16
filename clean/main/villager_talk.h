/* A town villager's talk scene (the scene class with vtable 0x020d9df8, held by the villager
 * scene object at 0x680, villager_scene_object.h): a scene of class 0x020d8bd4 (its commands,
 * scene_command.h) with the choices of talk_choices.h and the member functions the talk runs.
 *
 * Its own members are C++ pointers to member functions the talk's states set and run:
 * - 0xb0, 0xb8, 0xc0 are set together from a table of three (func_0202da88). 0xb0 writes the
 *   line to say into a VillagerTalkLine (most of them draw a message for the villager's
 *   personality into the text at 0x104 and its number at 0x122); 0xb8 runs once when the talk
 *   sends the scene event 0x10; 0xc0 runs at each event 0x14 while the talk is on the message
 *   data_021f43f8;
 * - 0xc8 runs once at event 0x14 while the talk is on the message data_021f43e8;
 * - 0xd0 is the reply to a choice (talk_choices.h);
 * - 0xd8 runs when the scene's command ends (func_0202dbf0 sets it);
 * - 0xf0 is a step of the villager's walk, 0xf8 a step that changes the music.
 *
 * Event 0x14 first goes through a table of 17 handlers by event number (VillagerTalk_RunEvent):
 * 1 gives the player an item, 7 opens the screen that asks for the birthday, 12 to 16 run the
 * five member functions at 0x16c. */
#ifndef CLEAN_MAIN_VILLAGER_TALK_H
#define CLEAN_MAIN_VILLAGER_TALK_H

#include "ov004/member_pointer.h"
#include "scene_command.h"
#include "types.h"

#define VILLAGER_TALK_EVENTS 17
#define VILLAGER_TALK_MEMBER_EVENTS 5 /* events 12 to 16 */
#define VILLAGER_TALK_TEXT_SIZE 0x1e

/* What a line function (0xb0) gives: the text (an address, 0 for none) and the message. */
typedef struct VillagerTalkLine {
    u32 text;
    u8 message;
    u8 unk_05[3];
} VillagerTalkLine;

typedef struct VillagerTalk {
    SceneCommandScene scene;                           /* 0x000 */
    MemberPointer line;                                /* 0x0b0: fills a VillagerTalkLine */
    MemberPointer on_event_10;                         /* 0x0b8 */
    MemberPointer on_each_message;                     /* 0x0c0: at the message data_021f43f8 */
    MemberPointer on_last_message;                     /* 0x0c8: once, at the message data_021f43e8 */
    MemberPointer reply;                               /* 0x0d0 */
    MemberPointer on_command_end;                      /* 0x0d8 */
    u8 unk_e0[0x10];                                   /* 0x0e0 */
    MemberPointer walk;                                /* 0x0f0 */
    MemberPointer music;                               /* 0x0f8 */
    u8 *villager;                                      /* 0x100: the villager scene object */
    char text[VILLAGER_TALK_TEXT_SIZE];                /* 0x104 */
    u8 message;                                        /* 0x122 */
    u8 unk_123;                                        /* 0x123 */
    u16 item;                                          /* 0x124: an item the player gives, 0xfff1 for none */
    u8 unk_126[2];                                     /* 0x126 */
    s32 memory_index;                                  /* 0x128: the place of the player's memory */
    u8 *memory;                                        /* 0x12c: the villager's memory of the player */
    u8 unk_130[4];                                     /* 0x130 */
    u8 *partner_memory;                                /* 0x134: the partner villager's memory of the player */
    u32 record_138;                                    /* 0x138: an address whose 0x74 holds sound values */
    u8 no_memory;                                      /* 0x13c: func_0202d8f8 leaves the memory alone */
    u8 unk_13d[3];                                     /* 0x13d */
    u32 functions[5];                                  /* 0x140: talk_choices.h */
    u8 unk_154[6];                                     /* 0x154 */
    u16 sound;                                         /* 0x15a: a sound effect to play, 0 for none */
    u8 unk_15c[0x10];                                  /* 0x15c */
    MemberPointer events[VILLAGER_TALK_MEMBER_EVENTS]; /* 0x16c */
    u8 villager_bits;                                  /* 0x194: town villagers still to be named */
    u8 unk_195[3];                                     /* 0x195 */
    s32 villager_count;                                /* 0x198: how many bits are set */
    u16 gift;                                          /* 0x19c: an item the player gets, 0xfff1 for none */
    u8 gift_from_items;                                /* 0x19e: 1 when the gift comes from the villager's items */
    u8 unk_19f;                                        /* 0x19f */
    s32 bells;                                         /* 0x1a0 */
} VillagerTalk;

void VillagerTalk_OnEvent14(VillagerTalk *talk, int event);
void VillagerTalk_OnEvent10(VillagerTalk *talk, void *arg);
int VillagerTalk_RunEvent(VillagerTalk *talk, unsigned int event);
int VillagerTalk_Event16(VillagerTalk *talk);
int VillagerTalk_Event15(VillagerTalk *talk);
int VillagerTalk_Event14(VillagerTalk *talk);
int VillagerTalk_Event13(VillagerTalk *talk);
int VillagerTalk_Event12(VillagerTalk *talk);
void VillagerTalk_PutBirthday(VillagerTalk *talk);
int VillagerTalk_AskBirthday(VillagerTalk *talk);
int VillagerTalk_ClearOption(void);
int VillagerTalk_SetOption(void);
int VillagerTalk_GiveGift(VillagerTalk *talk);
void VillagerTalk_HandBells(VillagerTalk *talk);
int VillagerTalk_SellGift(VillagerTalk *talk);
void VillagerTalk_TakeItem(VillagerTalk *talk);
int VillagerTalk_TradeItem(VillagerTalk *talk);
void VillagerTalk_TakeSoldItem(VillagerTalk *talk);
int VillagerTalk_BuyItem(VillagerTalk *talk);
int VillagerTalk_PlaySound138(VillagerTalk *talk);
int VillagerTalk_ShowLetter(VillagerTalk *talk);
int VillagerTalk_GiveItem(VillagerTalk *talk);
void VillagerTalk_Line8be0(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_NoteMemory(VillagerTalk *talk, void *unused);
void VillagerTalk_Line8d68(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_NoteMemoryAgain(VillagerTalk *talk, void *unused);
void VillagerTalk_Line89f8(VillagerTalk *talk, VillagerTalkLine *out);
u8 VillagerTalk_Line8d18Group4(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Line8d18Group3(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_OfferChoices32(VillagerTalk *talk);
void VillagerTalk_Line8d18Group2(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_ShowItem3818(VillagerTalk *talk);
void VillagerTalk_Line8d18Group7(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Say2274(VillagerTalk *talk);
void VillagerTalk_Line8d18Group6(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Line8d18Group5(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_GiveItem3818(VillagerTalk *talk);
void VillagerTalk_SayByVillagerCount(VillagerTalk *talk);
void VillagerTalk_Line8d18Group1(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_DropMusic(void);
void VillagerTalk_PlayMusic(void);
void VillagerTalk_WalkSay(VillagerTalk *talk);
void VillagerTalk_WalkStand(VillagerTalk *talk);
void VillagerTalk_WalkStart(VillagerTalk *talk);
void VillagerTalk_StartWalk(VillagerTalk *talk);
void VillagerTalk_Line8d18Group0(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Line213c(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Line2034(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Line2454(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_OfferChoices20360(VillagerTalk *talk);
void VillagerTalk_Line2a5e8(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Say243c(VillagerTalk *talk);
void VillagerTalk_Line8b50Group18(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Line8b50Group16(VillagerTalk *talk, VillagerTalkLine *out);
u8 VillagerTalk_Line8b50Group14(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_LineNewYearsEve(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_LineTimeOfDay(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_OfferChoicesRandom(VillagerTalk *talk);
void VillagerTalk_Line2a5e8Again(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Say23ac(VillagerTalk *talk);

#endif
