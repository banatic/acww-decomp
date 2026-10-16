/* The bromide (bromide.h). */
#include "bromide.h"

#include "clean.h"

static_assert(offsetof(Bromide, state) == 0x844, "state");
static_assert(sizeof(Bromide) == 0x848, "the size of a bromide");

#define BROMIDE_RECEIVER_OFFSET 0xec

/* The scene object's hooks. */
extern void func_0203ee08(Bromide *bromide, void *receiver);
extern int func_0203e020(Bromide *bromide);
/* Enters a state of the bromide if its entry agrees; whether it did. */
extern int func_ov004_02213590(Bromide *bromide, int state);

/* The receiver part as C++ converts a pointer to the bromide to it: NULL stays NULL. */
static void *Bromide_receiver(Bromide *bromide)
{
    return bromide != NULL ? (u8 *) bromide + BROMIDE_RECEIVER_OFFSET : NULL;
}

/* func_ov004_022133f8 (update of BROMIDE_TALK_END): once the link has closed, hands the
 * receiver back (func_0203ee08) and lets the scene go on (func_0203e020). Its state stays
 * BROMIDE_TALK_END until the scene sets another. */
void Bromide_UpdateTalkEnd(Bromide *bromide)
{
    if (bromide->base.link != NULL && bromide->base.link->open == 0) {
        func_0203ee08(bromide, Bromide_receiver(bromide));
        func_0203e020(bromide);
    }
}
CLEAN_AS(func_ov004_022133f8, Bromide_UpdateTalkEnd)

/* func_ov004_02213428 (entry of BROMIDE_TALK_END) */
int Bromide_EnterTalkEnd(Bromide *bromide)
{
    (void) bromide;
    return 1;
}
CLEAN_AS(func_ov004_02213428, Bromide_EnterTalkEnd)

/* func_ov004_0221342c (update of BROMIDE_TALK): on once the link has opened. */
void Bromide_UpdateTalk(Bromide *bromide)
{
    if (bromide->base.link != NULL && bromide->base.link->open != 0) {
        func_ov004_02213590(bromide, BROMIDE_TALK_END);
    }
}
CLEAN_AS(func_ov004_0221342c, Bromide_UpdateTalk)
