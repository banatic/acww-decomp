/* The exchange blocks of a visit (exchange_blocks.h). */
#include "exchange_blocks.h"

#include "clean.h"
#include "session.h"
#include "system_packet.h"
#include "activity.h"
#include "exchange_block.h"
#include "link_global.h"
#include "main_random.h"

extern NetSession *data_020ccf94;

#define GUESTS 3 /* slots 1-3 */

/* What SystemPacket_SendSlotBlocks sends a guest. */
enum {
    SEND_KEEP = 0,  /* the guest keeps its block */
    SEND_CLEAR = 1, /* the guest clears its block */
    SEND_COPY = 2,  /* the block of another slot */
    SEND_NONE = 3,  /* no packet */
};

/* func_020a0af8: each guest slot sent what Activity.block_source says: nothing when the slot
 * is not taken, the source slot's block (or, were it not to be sent, a clear), or a keep when
 * there is no source; the result is SystemPacket_SendSlotBlocks's. */
int ExchangeBlocks_SendToGuests(Activity *activity)
{
    int content[GUESTS] = {SEND_NONE, SEND_NONE, SEND_NONE};
    int block[GUESTS] = {EXCHANGE_BLOCK_NONE, EXCHANGE_BLOCK_NONE, EXCHANGE_BLOCK_NONE};
    NetSession *session = data_020ccf94;
    for (int i = GUESTS - 1; i >= 0; i--) {
        int slot = i + 1;
        if (Session_IsSlotTaken(session, slot) == 0) {
            continue;
        }
        int source = Activity_BlockSource(activity, slot);
        if (source >= EXCHANGE_BLOCK_NONE) {
            content[i] = SEND_KEEP;
        } else if (ExchangeBlock_IsSendable((ExchangeBlock *) (uintptr_t) ExchangeBlock_OfSlot(source)) != 0) {
            content[i] = SEND_COPY;
            block[i] = source;
        } else {
            content[i] = SEND_CLEAR;
        }
    }
    return SystemPacket_SendSlotBlocks(content[0], block[0], content[1], block[1], content[2], block[2]);
}
CLEAN_AS(func_020a0af8, ExchangeBlocks_SendToGuests)

/* func_020a0f3c: the blocks passed round: with the taken slots listed from slot 3 down, each is
 * given the block of the next in the list, the last the first's; the other slots none. */
void ExchangeBlocks_Rotate(Activity *activity)
{
    int taken[SESSION_SLOTS + 1];
    int count = 0;
    NetSession *session = data_020ccf94;
    for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
        if (Session_IsSlotTaken(session, slot) != 0) {
            taken[count++] = slot;
        }
    }
    for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
        Activity_SetBlockSource(activity, slot, EXCHANGE_BLOCK_NONE);
    }
    for (int i = 0; i < count; i++) {
        int next = i + 1 < count ? i + 1 : 0;
        Activity_SetBlockSource(activity, taken[i], (u8) taken[next]);
    }
}
CLEAN_AS(func_020a0f3c, ExchangeBlocks_Rotate)

/* func_020a0fac: every taken slot keeps its own block (the others get none), except that the
 * link state's slot (func_020a6ed0) and one other taken slot drawn at random swap theirs.
 * REQUIRES: another slot than the link state's is taken; with none the slot swapped with is a
 * leftover of the stack in the original, 0 here. */
void ExchangeBlocks_SwapWithRandom(Activity *activity)
{
    int own = (int) LinkGlobal_ServedSlot();
    int others[SESSION_SLOTS] = {0};
    int count = 0;
    NetSession *session = data_020ccf94;
    for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
        if (slot != own && Session_IsSlotTaken(session, slot) != 0) {
            others[count++] = slot;
        }
    }
    for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
        if (Session_IsSlotTaken(session, slot) != 0) {
            Activity_SetBlockSource(activity, slot, (u8) slot);
        } else {
            Activity_SetBlockSource(activity, slot, EXCHANGE_BLOCK_NONE);
        }
    }
    int other = others[MainRandom_Below(count)];
    Activity_SetBlockSource(activity, other, (u8) own);
    Activity_SetBlockSource(activity, own, (u8) other);
}
CLEAN_AS(func_020a0fac, ExchangeBlocks_SwapWithRandom)
