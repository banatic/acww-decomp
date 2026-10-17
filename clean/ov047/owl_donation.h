/* The owl's talk scene (owl_talk.h), the rest of its class: what follows the end of a line (its
 * vtable slot 0x14, OwlTalk_OnLineEnded, a table keyed by the line shown), the work done after
 * the screens of the pockets and of the museum (OWL_TALK_AFTER_*), and the tests of the items
 * the pockets offer.
 *
 * The museum's record (main's museum_record.h) has four groups; by their item codes (main's
 * item_group.h and item_form.h) and the owl's lines they are the fossils (group A, 0x450c-0x45db,
 * four codes an item; FurnitureInfo_MuseumKind gives the kind of a fossil, several to a kind), the
 * fish (group B, 0x12e8-0x131f), the insects (group C, 0x12b0-0x12e7) and the paintings (group
 * D, 0x3894-0x38e3, four codes an item). The item 0x1549 is a fossil not assessed yet: the owl
 * replaces it with a fossil drawn at random (OwlTalk_EndAssess). Offered one of the room items
 * 0x38e4-0x3933 it changes it in the pockets for the one of the twenty after them (as
 * item_form.h's replacement), and it has a line for those (0x3934-0x3983).
 *
 * Its lines (of "sp_npc_owl") name an item given: 0x6e plus its index for an insect, 0xaa plus
 * its index for a fish, 0x50 plus its kind for the last fossil of a kind. */
#ifndef CLEAN_OV047_OWL_DONATION_H
#define CLEAN_OV047_OWL_DONATION_H

#include "owl.h"
#include "types.h"

/* The end of a line (slot 0x14) and its handlers. */
void OwlTalk_OnLineEnded(OwlTalk *talk);
void OwlTalk_TakeItem(OwlTalk *talk);
void OwlTalk_EndProgressAsk(OwlTalk *talk);
void OwlTalk_EndThanks(OwlTalk *talk);
void OwlTalk_EndHaveIt(OwlTalk *talk);
void OwlTalk_EndFish(OwlTalk *talk);
void OwlTalk_EndInsect(OwlTalk *talk);
void OwlTalk_EndPainting(OwlTalk *talk);
void OwlTalk_EndCompleteGroup(OwlTalk *talk);
void OwlTalk_EndTaken(OwlTalk *talk);
void OwlTalk_EndDeclined(OwlTalk *talk);
void OwlTalk_EndAssessed(OwlTalk *talk);
void OwlTalk_EndAssessedFossil(OwlTalk *talk);
void OwlTalk_EndAssess(OwlTalk *talk);
void OwlTalk_EndNotGiven(OwlTalk *talk);
void OwlTalk_EndMenuLine(OwlTalk *talk);
void OwlTalk_EndOffer6a(OwlTalk *talk);
void OwlTalk_EndOther(OwlTalk *talk);
void OwlTalk_EndAskFossil(OwlTalk *talk);
void OwlTalk_EndAskGift(OwlTalk *talk);

/* The work after a screen (OWL_TALK_AFTER_*). */
void OwlTalk_TakeErrand(OwlTalk *talk);
void OwlTalk_SayProgress(OwlTalk *talk);
void OwlTalk_TakeFossil(OwlTalk *talk);
void OwlTalk_NextLine(OwlTalk *talk);
void OwlTalk_TakeOffered(OwlTalk *talk);

/* The tests of the items the pockets offer (PocketPredicate). */
u16 OwlTalk_IsErrandItem(u16 *item, int state);
int OwlTalk_IsFossilToAssess(u16 *item, int state);
int OwlTalk_IsMuseumItem(u16 *item, int state);

#endif
