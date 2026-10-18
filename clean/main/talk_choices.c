/* The choices a villager's talk scene offers (talk_choices.h). */
#include "talk_choices.h"

#include "clean.h"
#include "scene_base.h"
#include "main_random.h"
#include "talk_answers.h"

static_assert(offsetof(TalkChoiceList, functions) == 0x0c, "TalkChoiceList layout");
static_assert(offsetof(TalkChoiceList, count) == 0x20, "TalkChoiceList layout");
static_assert(offsetof(TalkChoiceList, cancel) == 0x21, "TalkChoiceList layout");
static_assert(offsetof(TalkChoicesScene, reply) == 0xd0, "TalkChoicesScene layout");
static_assert(offsetof(TalkChoicesScene, functions) == 0x140, "TalkChoicesScene layout");

/* What the menu is told when no choice was made. */
#define TALK_CHOICES_NONE (-1)

extern const MemberPointer __ptmf_null;
/* The message data each choice is set with. */
extern u8 data_021f43f8[];

static void *talk_choices_menu(TalkChoicesScene *scene)
{
    return (void *) (uintptr_t) SceneBase_TalkChoices((SceneBase *) (void *) scene);
}

/* func_0201ce68 (the scene's slot 0x18): when a reply is set, it is run with `arg` and the
 * choice made (-1 without a menu), then cleared. */
void TalkChoices_Reply(TalkChoicesScene *scene, void *arg)
{
    if (scene->reply.function == 0) {
        return;
    }
    void *menu = talk_choices_menu(scene);
    int choice = menu != NULL ? (int) TalkAnswers_Picked(menu) : TALK_CHOICES_NONE;
    void *target = MemberPointer_Object(&scene->reply, scene);
    ((void (*)(void *, void *, int))(uintptr_t) MemberPointer_Code(&scene->reply, target))(target, arg, choice);
    scene->reply = __ptmf_null;
}
CLEAN_AS(func_0201ce68, TalkChoices_Reply)

/* func_0201cec8: with the talk's menu, the list's choices offered: the scene's functions
 * cleared, the menu given the count and the cancel choice, then each choice a message drawn
 * at random from its range (one byte, on the stack) with the message data at 0x021f43f8, and
 * its function kept by the scene; the menu then made ready. */
void TalkChoices_Offer(TalkChoicesScene *scene, TalkChoiceList *list)
{
    void *menu = talk_choices_menu(scene);
    if (menu == NULL) {
        return;
    }
    TalkChoices_ClearFunctions(scene);
    TalkAnswers_Reset(menu, list->count, list->cancel);
    for (int i = 0; i < list->count; i++) {
        int first = list->range[i][0];
        int drawn = MainRandom_Below(list->range[i][1] - first + 1);
        u8 message = (u8) (list->range[i][0] + drawn);
        TalkAnswers_Set(menu, i, &message, 0, data_021f43f8, 0, 0);
        scene->functions[i] = list->functions[i];
    }
    TalkAnswers_LoadTexts(menu);
}
CLEAN_AS(func_0201cec8, TalkChoices_Offer)

/* func_0201cf54 */
void TalkChoices_ClearFunctions(TalkChoicesScene *scene)
{
    for (int i = 0; i < TALK_CHOICES_MAX; i++) {
        scene->functions[i] = 0;
    }
}
CLEAN_AS(func_0201cf54, TalkChoices_ClearFunctions)

/* func_0201cf74: choice `index` set from a range of two bytes (TalkChoices_Set). */
void TalkChoices_SetFrom(int unused, TalkChoiceList *list, int index, const u8 *range, u32 function)
{
    TalkChoices_Set(unused, list, index, range[0], range[1], (int) function);
}
CLEAN_AS(func_0201cf74, TalkChoices_SetFrom)

/* func_0201cf90: choice `index` gets the messages `first` to `last` and the function. The
 * index is not checked. */
void TalkChoices_Set(int unused, TalkChoiceList *list, int index, u8 first, u8 last, int function)
{
    (void) unused;
    u8 *bytes = (u8 *) list;
    bytes[index * 2] = first;
    bytes[index * 2 + 1] = last;
    *(s32 *) (void *) (bytes + offsetof(TalkChoiceList, functions) + index * 4) = function;
}
CLEAN_AS(func_0201cf90, TalkChoices_Set)

/* func_0201cfb4: the list emptied: no ranges, no functions, no choices, cancel -1. */
void TalkChoices_Clear(void *unused, TalkChoiceList *list)
{
    (void) unused;
    for (int i = 0; i < TALK_CHOICES_MAX; i++) {
        list->range[i][0] = 0;
        list->range[i][1] = 0;
        list->functions[i] = 0;
    }
    list->count = 0;
    list->cancel = TALK_CHOICES_NONE;
}
CLEAN_AS(func_0201cfb4, TalkChoices_Clear)
