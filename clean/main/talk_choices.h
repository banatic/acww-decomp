/* The choices a villager's talk scene offers (the scene class with vtable 0x020d9df8, a scene
 * base of scene_base.h, held by the villager scene object at 0x680, villager_scene_object.h).
 *
 * A caller fills a list (TalkChoiceList, on its stack) with up to five choices, each a range
 * of message numbers one of which is drawn at random, and the member function to run when it
 * is picked; the scene then offers them (TalkChoices_Offer) and keeps the choices' functions
 * at 0x140. The scene's reply (a member function pointer at 0xd0, func_0202da74 sets it) is
 * run once, with the choice made, when the talk tells the scene (TalkChoices_Reply). */
#ifndef CLEAN_MAIN_TALK_CHOICES_H
#define CLEAN_MAIN_TALK_CHOICES_H

#include "ov004/member_pointer.h"
#include "types.h"

#define TALK_CHOICES_MAX 5

typedef struct TalkChoiceList {
    u8 range[TALK_CHOICES_MAX][2];   /* 0x00: each choice's first and last message */
    u8 unk_0a[2];                    /* 0x0a */
    u32 functions[TALK_CHOICES_MAX]; /* 0x0c: what each choice runs (the game's, by address) */
    u8 count;                        /* 0x20 */
    s8 cancel;                       /* 0x21: handed to the menu with the count; -1 when set up */
} TalkChoiceList;

/* The scene's parts used here. */
typedef struct TalkChoicesScene {
    u8 unk_00[0xd0];
    MemberPointer reply; /* 0xd0: called with the talk's argument and the choice made */
    u8 unk_d8[0x68];
    u32 functions[TALK_CHOICES_MAX]; /* 0x140 */
} TalkChoicesScene;

void TalkChoices_Reply(TalkChoicesScene *scene, void *arg);
void TalkChoices_Offer(TalkChoicesScene *scene, TalkChoiceList *list);
void TalkChoices_ClearFunctions(TalkChoicesScene *scene);
void TalkChoices_SetFrom(int unused, TalkChoiceList *list, int index, const u8 *range, u32 function);
void TalkChoices_Set(int unused, TalkChoiceList *list, int index, u8 first, u8 last, int function);
void TalkChoices_Clear(void *unused, TalkChoiceList *list);

#endif
