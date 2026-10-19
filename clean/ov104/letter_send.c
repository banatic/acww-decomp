/* The post office's letter posting scene of overlay 104 (letter_send.h): its destructors, its
 * flags, the posting of the letters (here or through the linked host), the cursor's moves, the
 * choices it opens, the held letter and its places. */
#include "letter_send.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/current_pockets.h"
#include "main/display_layers.h"
#include "main/group_params.h"
#include "main/label_sprite.h"
#include "main/layer_load_task.h"
#include "main/mail.h"
#include "main/player_id.h"
#include "main/player_messages.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/session.h"
#include "main/sliding_window.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "main/talk_object.h"
#include "main/villager_part.h"
#include "ov002/key_repeat.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"
#include "ov094/pockets_common.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(LetterSendScene, flags) == 0x94, "flags");
static_assert(offsetof(LetterSendScene, grab_dx) == 0xa0 && offsetof(LetterSendScene, held_x) == 0xa8, "places");
static_assert(offsetof(LetterSendScene, result) == 0xb0 && offsetof(LetterSendScene, posted) == 0xb2, "result");
static_assert(offsetof(LetterSendScene, held_kind) == 0xb4 && offsetof(LetterSendScene, cursor) == 0xb8, "bytes");
static_assert(offsetof(LetterSendScene, choice_row) == 0xbd && offsetof(LetterSendScene, next_to_send) == 0xbe, "bytes");
static_assert(offsetof(LetterSendScene, held) == 0xc0 && offsetof(LetterSendScene, swapped) == 0x1c0, "letters");
static_assert(offsetof(LetterSendScene, unk_2c0) == 0x2c0 && offsetof(LetterSendScene, grid) == 0x2f8, "grid");
static_assert(offsetof(LetterSendScene, letters) == 0xd58 && offsetof(LetterSendScene, wallet) == 0xd80, "ov094 objects");
static_assert(offsetof(LetterSendScene, popup) == 0x23b8 && offsetof(LetterSendScene, glide) == 0x2488, "popup");
static_assert(offsetof(LetterSendScene, cursor_sprite) == 0x24a0 && offsetof(LetterSendScene, choice) == 0x2504, "sprite");
static_assert(offsetof(LetterSendScene, entries) == 0x28ec && offsetof(LetterSendScene, error) == 0x28f8, "choice");
static_assert(offsetof(LetterSendScene, view) == 0x2a14 && offsetof(LetterSendScene, button) == 0x2d3c, "view");
static_assert(offsetof(LetterSendScene, outbox) == 0x2db4 && offsetof(LetterSendScene, carried_copy) == 0x37b4, "outbox");
static_assert(offsetof(LetterSendScene, panel) == 0x41b4 && sizeof(LetterSendScene) == 0x4380, "size (func_ov104_0229f460)");

/* The touch (main's bytes, as ov106's mailbox_scene.c reads them). */
extern u8 data_021f6c58, data_021f6c54, data_021f6c60, data_021f6c5c;

/* The heap the menu scenes are allocated from, the link's session and the four players' records. */
extern Heap *data_021c9b28;
extern NetSession *data_020ccf94;
extern u8 data_021dc7bc[];

/* The scene's vtable. */
extern const u8 data_ov104_0229f6d0[];

/* The members' destructors (a letter's is handed to __cxa_vec_cleanup, so it is the game's
 * symbol). */
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void func_02066688(void *letter);

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The talk object's parts the full mailboxes' owners are named in (TalkObject_SetPart). */
#define LETTER_SEND_FIRST_NAME_PART 7
#define LETTER_SEND_NAME_PARTS 3

/* The sound effects of the panel's buttons and the label button. */
#define LETTER_SEND_SE_POST 0x27
#define LETTER_SEND_SE_CANCEL 0x28
#define LETTER_SEND_SE_LABEL 0x29

/* The panel's buttons. */
#define LETTER_SEND_BUTTON_CANCEL 7
#define LETTER_SEND_BUTTON_POST 9

/* The state both buttons set the scene to, directly (not by MenuScene_SetState). */
#define LETTER_SEND_STATE_END 4

/* The size of a message sent to the host: its type and the letter. */
#define LETTER_SEND_MESSAGE_SIZE (1 + (int) sizeof(Letter))

/* Bit `n` as the ARM's shift by a register makes it: the shift's bottom byte, 0 from 32 on. */
static u32 lsend_bit(u32 n)
{
    n &= 0xff;
    return n < 32 ? 1u << n : 0;
}

static MenuScene *lsend_scene(LetterSendScene *self)
{
    return &self->base;
}

static PagedChoice *lsend_choice(LetterSendScene *self)
{
    return (PagedChoice *) (void *) self->choice;
}

static Letter *lsend_mail(Letter *letter)
{
    return letter;
}

/* The place is a letter of the letters object: carried or to post. */
static int lsend_is_letter_place(LetterSendScene *self, int place)
{
    return LetterSend_IsCarriedPlace(self, (unsigned int) place) != 0 ||
           LetterSend_IsOutboxPlace(self, (unsigned int) place) != 0;
}

static int lsend_letter_index(LetterSendScene *self, int place)
{
    return LetterSend_LetterIndex(self, (unsigned int) place);
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void lsend_update_cursor_sprite(Glider *sprite)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}

/* The members' destructors, last member first, then the base's. The object at 0x2c0 has none. */
static void lsend_destroy_members(LetterSendScene *self)
{
    self->base.vtable = data_ov104_0229f6d0;
    ButtonPanel_Destroy(&self->panel);
    __cxa_vec_cleanup(self->carried_copy, LETTER_SEND_LETTERS, sizeof(Letter), func_02066688);
    __cxa_vec_cleanup(self->outbox, LETTER_SEND_LETTERS, sizeof(Letter), func_02066688);
    LabelButton0_Destroy(&self->button);
    LetterView_Destruct(&self->view);
    ErrorMessage_Destruct(&self->error);
    PagedChoice_Destroy(lsend_choice(self));
    Glider0_Destroy(&self->cursor_sprite);
    Glide_Destroy(&self->glide);
    Popup_Destroy(&self->popup);
    PocketsWallet_Destruct(&self->wallet);
    PocketsLetters_Destruct(&self->letters);
    PocketsGrid_Destruct(&self->grid);
    Letter_Destruct(&self->swapped);
    Letter_Destruct(&self->held);
    MenuScene_DestroyBase(lsend_scene(self));
}

/* func_ov104_0229c180 */
LetterSendScene *LetterSend_Destroy(LetterSendScene *self)
{
    lsend_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov104_0229c180, LetterSend_Destroy)

/* func_ov104_0229c260 */
LetterSendScene *LetterSend_Delete(LetterSendScene *self)
{
    lsend_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov104_0229c260, LetterSend_Delete)

/* func_ov104_0229c344 */
void LetterSend_ClearFlags(LetterSendScene *self, unsigned int flags)
{
    self->flags &= ~flags;
}
CLEAN_AS(func_ov104_0229c344, LetterSend_ClearFlags)

/* func_ov104_0229c354 */
void LetterSend_SetFlags(LetterSendScene *self, unsigned int flags)
{
    self->flags |= flags;
}
CLEAN_AS(func_ov104_0229c354, LetterSend_SetFlags)

/* func_ov104_0229c364: 1 when any of `flags` is set. */
int LetterSend_TestFlags(LetterSendScene *self, int flags)
{
    return (self->flags & (u32) flags) != 0;
}
CLEAN_AS(func_ov104_0229c364, LetterSend_TestFlags)

/* func_ov104_0229c378: `letter` sent to the host as message 8 (PLAYER_MESSAGE_STORE_RECORD,
 * the type byte and then the letter, built in a block of the menu scenes' heap), and the reply
 * set to 8 until the host answers. Always 1. REQUIRES: the heap has the block's 0x101 bytes;
 * the original writes through a null block too. */
int LetterSend_SendToHost(LetterSendScene *self, const Letter *letter)
{
    (void) self;
    Heap *heap = data_021c9b28;
    u8 *message = Heap_AllocBack(heap, LETTER_SEND_MESSAGE_SIZE);
    message[0] = PLAYER_MESSAGE_STORE_RECORD;
    MI_CpuCopy8(letter, message + 1, sizeof(Letter));
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, message, LETTER_SEND_MESSAGE_SIZE);
    Session_EndMessage(session, PLAYER_MESSAGE_CATEGORY, 0);
    Heap_Free(heap, message);
    PlayerMessages_SetReply(PLAYER_MESSAGE_STORE_RECORD);
    return 1;
}
CLEAN_AS(func_ov104_0229c378, LetterSend_SendToHost)

/* func_ov104_0229c3dc (each frame, from LetterSend_Update): while sending to the
 * host, the host's reply to the last letter taken in, then the next written letter to someone
 * else sent. Reply 8 (none yet) waits; 11 (no room) stops with LETTER_SEND_RESULT_NOT_ALL_SENT;
 * 9 and 10 (stored) mark the letter posted. After reply 10 (stored, and now no room) the next
 * letter with an addressee is not sent: posting stops with LETTER_SEND_RESULT_NOT_ALL_SENT. A
 * written letter without an addressee is passed over with LETTER_SEND_RESULT_NO_ADDRESSEE.
 * Sending ends after the last letter. Outside a linked post, sending is ended at once. */
void LetterSend_ContinueLinkedPost(LetterSendScene *self)
{
    if (LetterSend_TestFlags(self, LETTER_SEND_FLAG_LINKED) == 0) {
        LetterSend_ClearFlags(self, LETTER_SEND_FLAG_SENDING);
        return;
    }
    if (LetterSend_TestFlags(self, LETTER_SEND_FLAG_SENDING) == 0) {
        return;
    }

    int reply = PLAYER_MESSAGE_NONE;
    if (LetterSend_TestFlags(self, LETTER_SEND_FLAG_AWAITING_REPLY) != 0) {
        reply = PlayerMessages_Reply();
        switch (reply) {
            case PLAYER_MESSAGE_STORE_RECORD:
                return;
            case PLAYER_MESSAGE_NOT_STORED:
                self->result |= LETTER_SEND_RESULT_NOT_ALL_SENT;
                LetterSend_ClearFlags(self, LETTER_SEND_FLAG_SENDING);
                LetterSend_ClearFlags(self, LETTER_SEND_FLAG_AWAITING_REPLY);
                return;
            case PLAYER_MESSAGE_STORED:
            case PLAYER_MESSAGE_STORED_FULL:
                self->result |= LETTER_SEND_RESULT_POSTED;
                self->posted = (u16) (self->posted | lsend_bit(self->next_to_send));
                self->next_to_send++;
                LetterSend_ClearFlags(self, LETTER_SEND_FLAG_AWAITING_REPLY);
                break;
            default:
                break;
        }
    }

    while (self->next_to_send < LETTER_SEND_LETTERS) {
        Letter *letter = &self->outbox[self->next_to_send];
        if (Letter_IsToSelf(letter) == 0 && Letter_State(letter) == LETTER_STATE_WRITTEN) {
            self->result |= LETTER_SEND_RESULT_WRITTEN;
            if (Mail_HasAddressee(lsend_mail(letter)) != 0) {
                if (reply == PLAYER_MESSAGE_STORED_FULL) {
                    self->result |= LETTER_SEND_RESULT_NOT_ALL_SENT;
                    LetterSend_ClearFlags(self, LETTER_SEND_FLAG_SENDING);
                    return;
                }
                if (LetterSend_SendToHost(self, letter) != 0) {
                    LetterSend_SetFlags(self, LETTER_SEND_FLAG_AWAITING_REPLY);
                    return;
                }
            } else {
                self->result |= LETTER_SEND_RESULT_NO_ADDRESSEE;
            }
        }
        self->next_to_send++;
    }
    LetterSend_ClearFlags(self, LETTER_SEND_FLAG_SENDING);
}
CLEAN_AS(func_ov104_0229c3dc, LetterSend_ContinueLinkedPost)

/* func_ov104_0229c558: when consoles are linked, the post starts: nothing marked posted, the
 * result cleared (LETTER_SEND_RESULT_NOTHING without letters to post), and
 * LETTER_SEND_RESULT_TO_SELF_LINKED when a written letter is to the player themself. A console
 * that is not the host (its session slot is not 0) starts sending the letters to the host; the
 * host posts them here, only marking them posted (LetterSend_PostAll), with
 * LETTER_SEND_RESULT_NOT_ALL_SENT when the post office had no room. */
void LetterSend_BeginLinkedPost(LetterSendScene *self)
{
    NetSession *session = data_020ccf94;
    if (Session_IsLinked(session) == 0) {
        return;
    }

    LetterSend_SetFlags(self, LETTER_SEND_FLAG_LINKED);
    self->posted = 0;
    int count = Mail_CountLetters(lsend_mail(self->outbox), LETTER_SEND_LETTERS);
    self->result = 0;
    if (count <= 0) {
        self->result = LETTER_SEND_RESULT_NOTHING;
        LetterSend_ClearFlags(self, LETTER_SEND_FLAG_SENDING);
        return;
    }

    if (LetterSend_HasLetterToSelf(self, self->outbox) != 0) {
        self->result |= LETTER_SEND_RESULT_TO_SELF_LINKED;
    }
    if (session->local_slot != 0) {
        LetterSend_SetFlags(self, LETTER_SEND_FLAG_SENDING);
        self->next_to_send = 0;
        LetterSend_ClearFlags(self, LETTER_SEND_FLAG_AWAITING_REPLY);
        LetterSend_ContinueLinkedPost(self);
        return;
    }

    LetterSend_SetFlags(self, LETTER_SEND_FLAG_HOST);
    self->result |= LetterSend_PostAll(self, self->outbox, 1);
    if (self->result & LETTER_SEND_RESULT_POST_OFFICE_FULL) {
        self->result |= LETTER_SEND_RESULT_NOT_ALL_SENT;
    }
}
CLEAN_AS(func_ov104_0229c558, LetterSend_BeginLinkedPost)

/* func_ov104_0229c648: the ten `letters` compacted (Mail_Compact); each of them addressed to a
 * villager of this town given to that villager and cleared (LETTER_SEND_RESULT_POSTED). */
int LetterSend_GiveToVillagers(LetterSendScene *self, Letter *letters)
{
    (void) self;
    u16 result = 0;
    int count = Mail_Compact(lsend_mail(letters), LETTER_SEND_LETTERS);
    for (int i = 0; i < count; i++) {
        Letter *letter = &letters[i];
        if (Mail_FindVillagerAddressee(lsend_mail(letter)) >= 0) {
            Mail_GiveToVillager(lsend_mail(letter));
            Letter_Clear(letter);
            result |= LETTER_SEND_RESULT_POSTED;
        }
    }
    return result;
}
CLEAN_AS(func_ov104_0229c648, LetterSend_GiveToVillagers)

/* func_ov104_0229c6a0: the ten `letters` compacted; each one not to the player themself handed
 * on directly: to a player of this town into their mailbox, to a villager of this town to the
 * villager (cleared, LETTER_SEND_RESULT_POSTED). A letter to someone of no town here stays. The
 * players whose mailbox was full are counted into bits 6 and up of the result and named, in
 * player order, in parts 7, 8 and 9 of talk object 0. QUIRK: four full mailboxes count 4, which
 * reaches LETTER_SEND_RESULT_WRITTEN (bit 8) and leaves bits 6-7 at 0. */
u16 LetterSend_DeliverDirectly(LetterSendScene *self, Letter *letters)
{
    (void) self;
    u16 result = 0;
    int count = Mail_Compact(lsend_mail(letters), LETTER_SEND_LETTERS);
    if (count == 0) {
        return result;
    }

    u32 full_mask = 0;
    int full_count = 0;
    for (int i = 0; i < count; i++) {
        Letter *letter = &letters[i];
        if (Letter_IsToSelf(letter) != 0) {
            continue;
        }
        int player = Mail_FindPlayerAddressee(lsend_mail(letter));
        if (player == MAIL_NOT_HERE) {
            continue;
        }
        if (player != MAIL_NOT_THAT_KIND) {
            if (Mail_PutInMailbox(lsend_mail(letter), player, 1) != 0) {
                Letter_Clear(letter);
                result |= LETTER_SEND_RESULT_POSTED;
            } else if ((full_mask & lsend_bit((u32) player)) == 0) {
                full_mask |= lsend_bit((u32) player);
                full_count++;
            }
        } else if (Mail_FindVillagerAddressee(lsend_mail(letter)) >= 0) {
            Mail_GiveToVillager(lsend_mail(letter));
            Letter_Clear(letter);
            result |= LETTER_SEND_RESULT_POSTED;
        }
    }

    if (full_count != 0) {
        int named = 0;
        TalkObject *talk = TalkObject_Get(0);
        PlayerIdText name;
        PlayerIdText_Construct(&name);
        for (int player = 0; player < MAIL_PLAYERS; player++) {
            if ((full_mask & (1u << player)) == 0) {
                continue;
            }
            DesignCreator *id = PlayerRecord_Player(PlayerRecords_TownRecord(data_021dc7bc, player));
            PlayerId_NameToText(id, (TextBase *) (void *) &name);
            if (named < LETTER_SEND_NAME_PARTS) {
                TalkObject_SetPart(talk, LETTER_SEND_FIRST_NAME_PART + named, (TextBase *) (void *) &name);
            }
            named++;
        }
        result = (u16) (result | (full_count << LETTER_SEND_FULL_MAILBOXES_SHIFT));
        PlayerIdText_Destruct(&name);
    }
    return result;
}
CLEAN_AS(func_ov104_0229c6a0, LetterSend_DeliverDirectly)

/* func_ov104_0229c7dc: `letter` left at the post office, its state advanced; nonzero when the
 * post office had room. */
int LetterSend_HoldAtPostOffice(LetterSendScene *self, Letter *letter)
{
    (void) self;
    return Mail_HoldAtPostOffice(lsend_mail(letter), 1);
}
CLEAN_AS(func_ov104_0229c7dc, LetterSend_HoldAtPostOffice)

/* func_ov104_0229c7e8: the ten `letters` compacted; of those, a letter not in the written state
 * is cleared, and a written one to someone else with an addressee left at the post office again
 * (cleared, LETTER_SEND_RESULT_POSTED) or, without room, LETTER_SEND_RESULT_STILL_FULL. */
u16 LetterSend_RetryHold(LetterSendScene *self, Letter *letters)
{
    u16 result = 0;
    int count = Mail_Compact(lsend_mail(letters), LETTER_SEND_LETTERS);
    if (count == 0) {
        return result;
    }
    for (int i = 0; i < count; i++) {
        Letter *letter = &letters[i];
        if (Letter_State(letter) != LETTER_STATE_WRITTEN) {
            Letter_Clear(letter);
        } else if (Letter_IsToSelf(letter) == 0 && Mail_HasAddressee(lsend_mail(letter)) != 0) {
            if (LetterSend_HoldAtPostOffice(self, letter) != 0) {
                Letter_Clear(letter);
                result |= LETTER_SEND_RESULT_POSTED;
            } else {
                result |= LETTER_SEND_RESULT_STILL_FULL;
            }
        }
    }
    return result;
}
CLEAN_AS(func_ov104_0229c7e8, LetterSend_RetryHold)

/* A letter of LetterSend_PostAll taken: only marked posted with `mark_only` (the host's, whose
 * letters are dropped later by LetterSend_ReturnUnsent), else cleared. */
static void lsend_take(LetterSendScene *self, Letter *letter, int index, int mark_only)
{
    if (mark_only != 0) {
        self->posted = (u16) (self->posted | (1u << index));
    } else {
        Letter_Clear(letter);
    }
}

/* func_ov104_0229c870: the ten `letters` posted (0 at once when there are none). A letter that
 * is not in the written state is taken (lsend_take) as it is; a written one to someone else is
 * left at the post office and taken (LETTER_SEND_RESULT_POSTED), or gives
 * LETTER_SEND_RESULT_NO_ADDRESSEE without an addressee and LETTER_SEND_RESULT_POST_OFFICE_FULL
 * without room; LETTER_SEND_RESULT_WRITTEN with each. Letters to the player themself stay.
 * QUIRK: the state of a letter that is not empty is asked for twice. */
u16 LetterSend_PostAll(LetterSendScene *self, Letter *letters, int mark_only)
{
    if (Mail_CountLetters(lsend_mail(letters), LETTER_SEND_LETTERS) == 0) {
        return 0;
    }

    u16 result = 0;
    for (int i = 0; i < LETTER_SEND_LETTERS; i++) {
        Letter *letter = &letters[i];
        if (Letter_State(letter) == LETTER_STATE_NONE) {
            continue;
        }
        if (Letter_State(letter) != LETTER_STATE_WRITTEN) {
            lsend_take(self, letter, i, mark_only);
            continue;
        }
        if (Letter_IsToSelf(letter) != 0) {
            continue;
        }
        if (Mail_HasAddressee(lsend_mail(letter)) == 0) {
            result |= LETTER_SEND_RESULT_WRITTEN | LETTER_SEND_RESULT_NO_ADDRESSEE;
            continue;
        }
        if (LetterSend_HoldAtPostOffice(self, letter) == 0) {
            result |= LETTER_SEND_RESULT_WRITTEN | LETTER_SEND_RESULT_POST_OFFICE_FULL;
            continue;
        }
        lsend_take(self, letter, i, mark_only);
        result |= LETTER_SEND_RESULT_WRITTEN | LETTER_SEND_RESULT_POSTED;
    }
    return result;
}
CLEAN_AS(func_ov104_0229c870, LetterSend_PostAll)

/* func_ov104_0229c944: the written letters to the player themself among the ten `letters`: one
 * is made the letter screen's letter (GroupParams_SetLetter) and cleared
 * (LETTER_SEND_RESULT_ONE_TO_SELF); more than one are left (LETTER_SEND_RESULT_SEVERAL_TO_SELF). */
u16 LetterSend_TakeLetterToSelf(LetterSendScene *self, Letter *letters)
{
    (void) self;
    u16 result = 0;
    int found = -1; /* -1 none, -2 several, else the index */
    for (int i = 0; i < LETTER_SEND_LETTERS; i++) {
        Letter *letter = &letters[i];
        if (Letter_State(letter) == LETTER_STATE_WRITTEN && Letter_IsToSelf(letter) != 0) {
            found = found == -1 ? i : -2;
        }
    }
    if (found == -2) {
        result |= LETTER_SEND_RESULT_SEVERAL_TO_SELF;
    } else if (found != -1) {
        result |= LETTER_SEND_RESULT_ONE_TO_SELF;
        GroupParams_SetLetter(&letters[found]);
        Letter_Clear(&letters[found]);
    }
    return result;
}
CLEAN_AS(func_ov104_0229c944, LetterSend_TakeLetterToSelf)

/* func_ov104_0229c9c4: whether one of the ten `letters` is a written letter to the player
 * themself. */
int LetterSend_HasLetterToSelf(LetterSendScene *self, const Letter *letters)
{
    (void) self;
    for (int i = 0; i < LETTER_SEND_LETTERS; i++) {
        if (Letter_State(&letters[i]) == LETTER_STATE_WRITTEN && Letter_IsToSelf(&letters[i]) != 0) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov104_0229c9c4, LetterSend_HasLetterToSelf)

/* func_ov104_0229c9fc (panel button 7): sound 0x28, LETTER_SEND_FLAG_CANCELLED, the button
 * selected, sub state 0x1b and state 4. */
void LetterSend_Cancel(LetterSendScene *self)
{
    SoundSys_PlaySe(LETTER_SEND_SE_CANCEL);
    LetterSend_SetFlags(self, LETTER_SEND_FLAG_CANCELLED);
    ButtonPanel_Select(&self->panel, LETTER_SEND_BUTTON_CANCEL);
    MenuScene_SetSubState(lsend_scene(self), 0x1b);
    self->base.state = LETTER_SEND_STATE_END;
    LetterSend_ClearFlags(self, LETTER_SEND_FLAG_ACTION_1);
}
CLEAN_AS(func_ov104_0229c9fc, LetterSend_Cancel)

/* func_ov104_0229ca44 (panel button 9): sound 0x27, the button selected, sub state 0x1b and
 * state 4; with consoles linked the post starts here (LetterSend_BeginLinkedPost), else the
 * scene's end posts the letters. */
void LetterSend_Post(LetterSendScene *self)
{
    SoundSys_PlaySe(LETTER_SEND_SE_POST);
    LetterSend_ClearFlags(self, LETTER_SEND_FLAG_CANCELLED);
    ButtonPanel_Select(&self->panel, LETTER_SEND_BUTTON_POST);
    MenuScene_SetSubState(lsend_scene(self), 0x1b);
    self->base.state = LETTER_SEND_STATE_END;
    LetterSend_ClearFlags(self, LETTER_SEND_FLAG_ACTION_1);
    if (Session_IsLinked(data_020ccf94) != 0) {
        LetterSend_BeginLinkedPost(self);
    }
}
CLEAN_AS(func_ov104_0229ca44, LetterSend_Post)

/* func_ov104_0229caa0: each letter left to post put back among the carried letters, in a free
 * place (it stays where there is none); with `drop_posted`, the letters marked posted are
 * cleared instead. */
void LetterSend_ReturnUnsent(LetterSendScene *self, int drop_posted)
{
    for (int i = 0; i < LETTER_SEND_LETTERS; i++) {
        Letter *letter = &self->outbox[i];
        if (drop_posted != 0 && (self->posted & (1u << i)) != 0) {
            Letter_Clear(letter);
        } else if (Letter_State(letter) != LETTER_STATE_NONE) {
            int place = LetterSend_FreeCarriedPlace(self);
            if (place != LETTER_SEND_NO_PLACE) {
                LetterSend_PutLetterAt(self, place, letter);
            }
        }
    }
}
CLEAN_AS(func_ov104_0229caa0, LetterSend_ReturnUnsent)

/* func_ov104_0229cb04: the carried letters put back as the scene began. */
void LetterSend_RestoreCarried(LetterSendScene *self)
{
    for (int i = 0; i < LETTER_SEND_LETTERS; i++) {
        LetterSend_PutLetterAt(self, LETTER_SEND_CARRIED_FIRST + i, &self->carried_copy[i]);
    }
}
CLEAN_AS(func_ov104_0229cb04, LetterSend_RestoreCarried)

/* func_ov104_0229cb38: the carried letters copied aside. */
void LetterSend_SaveCarried(LetterSendScene *self)
{
    for (int i = 0; i < LETTER_SEND_LETTERS; i++) {
        Letter *letter = LetterSend_PlaceLetter(self, LETTER_SEND_CARRIED_FIRST + i);
        Letter_Assign(&self->carried_copy[i], letter);
    }
}
CLEAN_AS(func_ov104_0229cb38, LetterSend_SaveCarried)

/* func_ov104_0229cb70 (action 3) */
void LetterSend_RunActionMenu(LetterSendScene *self)
{
    LetterSend_OpenFixedMenu(self);
}
CLEAN_AS(func_ov104_0229cb70, LetterSend_RunActionMenu)

/* func_ov104_0229cb78 (action 2): the letter of the place whose choice is open picked up and
 * held where that place is (2 pixels up and left when state flag 2 is set), sub state 0x1c. */
void LetterSend_PickUpSlotLetter(LetterSendScene *self)
{
    u8 place = self->slot;
    LetterSend_PickUpLetter(self, place);
    self->held_x = LetterSend_PlaceX(self, place);
    self->held_y = LetterSend_PlaceY(self, place);
    if (StateFlags_Test2() != 0) {
        self->held_x -= 2;
        self->held_y -= 2;
    }
    MenuScene_SetSubState(lsend_scene(self), 0x1c);
    PocketsLetters_StartPickUp(&self->letters);
}
CLEAN_AS(func_ov104_0229cb78, LetterSend_PickUpSlotLetter)

/* func_ov104_0229cbe8: sub state 0x1a, the label button's state 2, sound 0x29. */
void LetterSend_PressLabelButton(LetterSendScene *self)
{
    MenuScene_SetSubState(lsend_scene(self), 0x1a);
    /* The button's base is main's labelled sprite (label_button.h). */
    LabelSprite_SetState((LabelSprite *) (void *) &self->button, 2);
    SoundSys_PlaySe(LETTER_SEND_SE_LABEL);
}
CLEAN_AS(func_ov104_0229cbe8, LetterSend_PressLabelButton)

/* func_ov104_0229cc0c (action 1): state 4, phase 1, LETTER_SEND_FLAG_ACTION_1. */
void LetterSend_RunAction1(LetterSendScene *self)
{
    MenuScene_SetState(lsend_scene(self), 4);
    MenuScene_SetPhase(lsend_scene(self), 1);
    LetterSend_SetFlags(self, LETTER_SEND_FLAG_ACTION_1);
}
CLEAN_AS(func_ov104_0229cc0c, LetterSend_RunAction1)

/* func_ov104_0229cc30: the cursor moved by `keys` (KeyRepeat_Has*) in the part of the scene it
 * is in; `mode` 0 lets it go down to the places below the letters. The wrap flags are cleared
 * first. 1 when the cursor changed place; 0 at once when `keys` is 0. */
int LetterSend_MoveCursor(LetterSendScene *self, int keys, int mode)
{
    u8 before = self->cursor;

    LetterSend_ClearFlags(self, LETTER_SEND_FLAGS_WRAPPED);
    if (keys == 0) {
        return 0;
    }
    if (LetterSend_IsCarriedPlace(self, self->cursor) != 0) {
        LetterSend_MoveCursorInCarried(self, keys, mode);
    } else if (LetterSend_IsOutboxPlace(self, self->cursor) != 0) {
        LetterSend_MoveCursorInOutbox(self, keys, mode);
    } else if (LetterSend_IsBelowPlace(self, self->cursor) != 0) {
        LetterSend_MoveCursorBelow(self, keys);
    }
    return before != self->cursor;
}
CLEAN_AS(func_ov104_0229cc30, LetterSend_MoveCursor)

/* func_ov104_0229ccb4: left goes to the place below the letters to post, right to the one below
 * the carried letters; up goes to the bottom left letter above (0x1d or 0x13), the cursor sprite
 * turning to set A. */
void LetterSend_MoveCursorBelow(LetterSendScene *self, int keys)
{
    if (KeyRepeat_HasLeft(keys) != 0) {
        self->cursor = LETTER_SEND_BELOW_OUTBOX;
    } else if (KeyRepeat_HasRight(keys) != 0) {
        self->cursor = LETTER_SEND_BELOW_CARRIED;
    }
    if (KeyRepeat_HasUp(keys) != 0) {
        Glider_TurnToSetA(&self->cursor_sprite);
        self->cursor = self->cursor == LETTER_SEND_BELOW_OUTBOX ? 0x1d : 0x13;
    }
}
CLEAN_AS(func_ov104_0229ccb4, LetterSend_MoveCursorBelow)

/* Up and down within a column of five rows of two (shared by both sets of letters): up stops at
 * the top row, down from the bottom row goes to the place `below` when `mode` is 0, the cursor
 * sprite turning to set B. */
static void lsend_move_in_column(LetterSendScene *self, int keys, int mode, int row, u8 below)
{
    if (KeyRepeat_HasUp(keys) != 0) {
        if (row > 0) {
            self->cursor -= LETTER_SEND_COLUMNS;
        }
        return;
    }
    if (KeyRepeat_HasDown(keys) != 0) {
        if (row < LETTER_SEND_ROWS - 1) {
            self->cursor += LETTER_SEND_COLUMNS;
        } else if (mode == 0) {
            self->cursor = below;
            Glider_TurnToSetB(&self->cursor_sprite);
        }
    }
}

/* func_ov104_0229cd18: the cursor on the letters to post (5 rows of 2, at the left). Left stops
 * at the left column; right of the right column goes to the carried letters' left column of the
 * same row (no wrap flag). Up and down are taken only when the cursor is still on the letters to
 * post and no wrap flag is set. */
void LetterSend_MoveCursorInOutbox(LetterSendScene *self, int keys, int mode)
{
    int column = (int) self->cursor - LETTER_SEND_OUTBOX_FIRST;
    int row = 0;
    while (column >= LETTER_SEND_COLUMNS) {
        row++;
        column -= LETTER_SEND_COLUMNS;
    }

    if (KeyRepeat_HasLeft(keys) != 0) {
        if (column > 0) {
            self->cursor--;
        }
    } else if (KeyRepeat_HasRight(keys) != 0) {
        if (column >= 1) {
            self->cursor = (u8) (row * 2 + LETTER_SEND_CARRIED_FIRST);
            return;
        }
        self->cursor++;
    }

    if (LetterSend_IsOutboxPlace(self, self->cursor) == 0 || LetterSend_TestFlags(self, LETTER_SEND_FLAGS_WRAPPED) != 0) {
        return;
    }
    lsend_move_in_column(self, keys, mode, row, LETTER_SEND_BELOW_OUTBOX);
}
CLEAN_AS(func_ov104_0229cd18, LetterSend_MoveCursorInOutbox)

/* func_ov104_0229cdf0: the cursor on the carried letters (5 rows of 2, at the right). Left of the
 * left column goes to the letters to post's right column of the same row (no wrap flag); right
 * stops at the right column. Up and down as LetterSend_MoveCursorInOutbox. */
void LetterSend_MoveCursorInCarried(LetterSendScene *self, int keys, int mode)
{
    int index = (int) self->cursor - LETTER_SEND_CARRIED_FIRST;
    int column = index & 1;
    /* The ROM shifts arithmetically; `index` is 0-9 for the places this is called on. */
    int row = index >> 1;

    if (KeyRepeat_HasLeft(keys) != 0) {
        if (column <= 0) {
            self->cursor = (u8) (row * 2 + LETTER_SEND_OUTBOX_FIRST + 1);
            return;
        }
        self->cursor--;
    } else if (KeyRepeat_HasRight(keys) != 0) {
        if (column < 1) {
            self->cursor++;
        }
    }

    if (LetterSend_IsCarriedPlace(self, self->cursor) == 0 || LetterSend_TestFlags(self, LETTER_SEND_FLAGS_WRAPPED) != 0) {
        return;
    }
    lsend_move_in_column(self, keys, mode, row, LETTER_SEND_BELOW_CARRIED);
}
CLEAN_AS(func_ov104_0229cdf0, LetterSend_MoveCursorInCarried)

/* func_ov104_0229cec4: the fixed choice (its first row set apart): texts 0x1a and 0x19 cancel,
 * text 0x15 picks the letter up. */
void LetterSend_OpenFixedMenu(LetterSendScene *self)
{
    LetterSend_SetFlags(self, LETTER_SEND_FLAG_FIXED_MENU);
    ChoiceEntries_Clear(&self->entries, LETTER_SEND_ACTION_CANCEL);
    ChoiceEntries_Add(&self->entries, 0x1a, LETTER_SEND_ACTION_CANCEL);
    ChoiceEntries_Add(&self->entries, 0x15, LETTER_SEND_ACTION_PICK_UP);
    ChoiceEntries_Add(&self->entries, 0x19, LETTER_SEND_ACTION_CANCEL);
    LetterSend_ShowChoice(self, 0);
}
CLEAN_AS(func_ov104_0229cec4, LetterSend_OpenFixedMenu)

/* func_ov104_0229cf14: the choice of the letter at `place`: text 0 (action 0) when state flag 2
 * is set; text 0x17 (state 7) or 0x14 (another state but 0) for action 1; text 0x15 for the
 * fixed menu when the letter has no item and its state is 1, 3, 4 or 6; text 2 to cancel. The
 * cursor sprite is hidden, the popup too unless the choice goes above it. */
void LetterSend_OpenLetterMenu(LetterSendScene *self, int place, int above_popup)
{
    LetterSend_ClearFlags(self, LETTER_SEND_FLAG_FIXED_MENU);
    self->slot = (u8) place;
    ChoiceEntries_Clear(&self->entries, LETTER_SEND_ACTION_CANCEL);
    Letter *letter = LetterSend_PlaceLetter(self, place);
    if (StateFlags_Test2() != 0) {
        ChoiceEntries_Add(&self->entries, 0, LETTER_SEND_ACTION_0);
    }
    int state = Letter_State(letter);
    if (state != LETTER_STATE_NONE) {
        if (state == LETTER_STATE_BETWEEN_VILLAGERS) {
            ChoiceEntries_Add(&self->entries, 0x17, LETTER_SEND_ACTION_1);
        } else {
            ChoiceEntries_Add(&self->entries, 0x14, LETTER_SEND_ACTION_1);
        }
    }
    if (Letter_Item(letter) == LETTER_NO_ITEM && (state == 3 || state == 6 || state == 1 || state == 4)) {
        ChoiceEntries_Add(&self->entries, 0x15, LETTER_SEND_ACTION_MENU);
    }
    ChoiceEntries_Add(&self->entries, 2, LETTER_SEND_ACTION_CANCEL);
    LetterSend_HideCursorSprite(self);
    if (above_popup == 0) {
        Popup_Hide(&self->popup, 1);
    }
    LetterSend_ShowChoice(self, above_popup);
}
CLEAN_AS(func_ov104_0229cf14, LetterSend_OpenLetterMenu)

/* func_ov104_0229cfe4: the cancel action, the cursor sprite put back at the cursor, the choice
 * asked to close, sub state 0x18. */
void LetterSend_CancelChoice(LetterSendScene *self)
{
    self->action = LETTER_SEND_ACTION_CANCEL;
    LetterSend_PlaceCursorSprite(self);
    PagedChoice_RequestClose(lsend_choice(self), 0);
    MenuScene_SetSubState(lsend_scene(self), 0x18);
}
CLEAN_AS(func_ov104_0229cfe4, LetterSend_CancelChoice)

/* func_ov104_0229d010: the entries shown in the choice (the first row set apart for the fixed
 * menu), placed above the popup or beside the open place, asked to open; sub state 0x16. */
void LetterSend_ShowChoice(LetterSendScene *self, int above_popup)
{
    int fixed = LetterSend_TestFlags(self, LETTER_SEND_FLAG_FIXED_MENU);
    PagedChoice_ShowEntries(lsend_choice(self), &self->entries, fixed);
    int x = LetterSend_PlaceX(self, self->slot);
    int y = LetterSend_PlaceY(self, self->slot);
    if (above_popup != 0) {
        PagedChoice_PlaceAboveWindow(lsend_choice(self), &self->popup);
    } else {
        PagedChoice_PlaceBeside(lsend_choice(self), x, y);
    }
    PagedChoice_RequestOpen(lsend_choice(self), 0);
    MenuScene_SetSubState(lsend_scene(self), 0x16);
}
CLEAN_AS(func_ov104_0229d010, LetterSend_ShowChoice)

/* func_ov104_0229d08c: the action picked (`action`); any value above 3 cancels. */
void LetterSend_RunAction(LetterSendScene *self)
{
    switch (self->action) {
        case LETTER_SEND_ACTION_0:
            LetterSend_RunAction0(self);
            break;
        case LETTER_SEND_ACTION_1:
            LetterSend_RunAction1(self);
            break;
        case LETTER_SEND_ACTION_PICK_UP:
            LetterSend_PickUpSlotLetter(self);
            break;
        case LETTER_SEND_ACTION_MENU:
            LetterSend_RunActionMenu(self);
            break;
        default:
            LetterSend_EndAction(self);
            break;
    }
}
CLEAN_AS(func_ov104_0229d08c, LetterSend_RunAction)

/* func_ov104_0229d0d4: the popup hidden, the sub state to go back to kept, `target` kept, the
 * cursor sprite's animation 6, sub state 0x13. */
void LetterSend_BeginSubState13(LetterSendScene *self, u8 target)
{
    Popup_Hide(&self->popup, 1);
    self->return_state = self->base.sub_state;
    self->target = target;
    Glider_SetAnim(&self->cursor_sprite, 6);
    MenuScene_SetSubState(lsend_scene(self), 0x13);
}
CLEAN_AS(func_ov104_0229d0d4, LetterSend_BeginSubState13)

/* func_ov104_0229d11c: the popup hidden, `target` kept, the cursor sprite's animation 5, sub
 * state 0x12. */
void LetterSend_BeginSubState12(LetterSendScene *self, u8 target)
{
    Popup_Hide(&self->popup, 1);
    self->target = target;
    Glider_SetAnim(&self->cursor_sprite, 5);
    MenuScene_SetSubState(lsend_scene(self), 0x12);
}
CLEAN_AS(func_ov104_0229d11c, LetterSend_BeginSubState12)

/* func_ov104_0229d158 (action 0): the cursor sprite's animation 4, sub state 0x10. */
void LetterSend_RunAction0(LetterSendScene *self)
{
    Glider_SetAnim(&self->cursor_sprite, 4);
    MenuScene_SetSubState(lsend_scene(self), 0x10);
}
CLEAN_AS(func_ov104_0229d158, LetterSend_RunAction0)

/* func_ov104_0229d178 */
void LetterSend_BeginSubState0e(LetterSendScene *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(lsend_scene(self), 0x0e);
}
CLEAN_AS(func_ov104_0229d178, LetterSend_BeginSubState0e)

/* func_ov104_0229d198: the first animation of the cursor sprite's set, then its update. */
void LetterSend_ShowCursorFirstOfSet(LetterSendScene *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    lsend_update_cursor_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov104_0229d198, LetterSend_ShowCursorFirstOfSet)

/* func_ov104_0229d1b8: the cursor sprite put at the cursor, animation 1. */
void LetterSend_PlaceCursorSprite(LetterSendScene *self)
{
    int x = LetterSend_CursorSpriteX(self);
    int y = LetterSend_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, 1);
}
CLEAN_AS(func_ov104_0229d1b8, LetterSend_PlaceCursorSprite)

/* func_ov104_0229d1ec: the cursor sprite put at the choice's row 1 for the fixed menu (its
 * first row set apart), else at row 0; animation 7. */
void LetterSend_PointAtDefaultRow(LetterSendScene *self)
{
    self->choice_row = LetterSend_TestFlags(self, LETTER_SEND_FLAG_FIXED_MENU) != 0 ? 1 : 0;
    int x = PagedChoice_TextX(lsend_choice(self));
    int y = PagedChoice_RowY(lsend_choice(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, 7);
}
CLEAN_AS(func_ov104_0229d1ec, LetterSend_PointAtDefaultRow)

/* func_ov104_0229d250: the cancel action, the choice's last row picked and the cursor sprite
 * put at it, showing animation 8 from its last frame; sub state 0x17. */
void LetterSend_PointAtLastRow(LetterSendScene *self)
{
    self->action = LETTER_SEND_ACTION_CANCEL;
    self->choice_row = PagedChoice_PickLastRow(lsend_choice(self), 1);
    int x = PagedChoice_TextX(lsend_choice(self));
    int y = PagedChoice_RowY(lsend_choice(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    CellLayerSprite_SetAnimAtEnd((CellLayerSprite *) (void *) &self->cursor_sprite, 8);
    MenuScene_SetSubState(lsend_scene(self), 0x17);
}
CLEAN_AS(func_ov104_0229d250, LetterSend_PointAtLastRow)

/* func_ov104_0229d2b4: the cursor sprite moved to the choice row in 2 steps; the sub state to
 * go back to kept, sub state 0x0d. */
void LetterSend_GlideToRow(LetterSendScene *self)
{
    int x = PagedChoice_TextX(lsend_choice(self));
    int y = PagedChoice_RowY(lsend_choice(self), self->choice_row);
    Glider_MoveTo(&self->cursor_sprite, x, y, 2);
    self->return_state = self->base.sub_state;
    MenuScene_SetSubState(lsend_scene(self), 0x0d);
}
CLEAN_AS(func_ov104_0229d2b4, LetterSend_GlideToRow)

/* func_ov104_0229d304: the cursor sprite put at the cursor at once when LETTER_SEND_FLAG_JUMP
 * is set (which this clears), else eased there in 3 steps with the sub state to go back to
 * kept, sub state 0x0d. */
void LetterSend_GlideToCursor(LetterSendScene *self)
{
    if (LetterSend_TestFlags(self, LETTER_SEND_FLAG_JUMP) != 0) {
        int x = LetterSend_CursorSpriteX(self);
        int y = LetterSend_CursorSpriteY(self);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
        LetterSend_ClearFlags(self, LETTER_SEND_FLAG_JUMP);
    } else {
        int x = LetterSend_CursorSpriteX(self);
        int y = LetterSend_CursorSpriteY(self);
        Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
        self->return_state = self->base.sub_state;
        MenuScene_SetSubState(lsend_scene(self), 0x0d);
    }
}
CLEAN_AS(func_ov104_0229d304, LetterSend_GlideToCursor)

/* func_ov104_0229d378: the cursor sprite's animation 0, then its update. */
void LetterSend_HideCursorSprite(LetterSendScene *self)
{
    Glider_SetAnim(&self->cursor_sprite, 0);
    lsend_update_cursor_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov104_0229d378, LetterSend_HideCursorSprite)

/* func_ov104_0229d39c: the cursor sprite's y, the cursor's place's. */
int LetterSend_CursorSpriteY(LetterSendScene *self)
{
    return LetterSend_PlaceY(self, self->cursor);
}
CLEAN_AS(func_ov104_0229d39c, LetterSend_CursorSpriteY)

/* func_ov104_0229d3ac: the cursor sprite's x, the cursor's place's plus 8; a screen width (256)
 * further right with LETTER_SEND_FLAG_WRAPPED_RIGHT, further left with
 * LETTER_SEND_FLAG_WRAPPED_LEFT. */
int LetterSend_CursorSpriteX(LetterSendScene *self)
{
    int x = LetterSend_PlaceX(self, self->cursor);
    if (LetterSend_TestFlags(self, LETTER_SEND_FLAG_WRAPPED_RIGHT) != 0) {
        x += 0x100;
    } else if (LetterSend_TestFlags(self, LETTER_SEND_FLAG_WRAPPED_LEFT) != 0) {
        x -= 0x100;
    }
    return x + 8;
}
CLEAN_AS(func_ov104_0229d3ac, LetterSend_CursorSpriteX)

/* func_ov104_0229d3f0: the cursor sprite put at the cursor, animation 7 on a place below the
 * letters and 1 elsewhere, then its set's first animation shown. */
void LetterSend_ShowCursorAtCursor(LetterSendScene *self)
{
    int x = LetterSend_CursorSpriteX(self);
    int y = LetterSend_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    if (LetterSend_IsBelowPlace(self, self->cursor) != 0) {
        Glider_SetAnim(&self->cursor_sprite, 7);
    } else {
        Glider_SetAnim(&self->cursor_sprite, 1);
    }
    LetterSend_ShowCursorFirstOfSet(self);
}
CLEAN_AS(func_ov104_0229d3f0, LetterSend_ShowCursorAtCursor)

/* func_ov104_0229d448: when a letter is held, it changes places with the letter at `place`: the
 * held one is copied aside, the place's letter picked up and the copy put at `place`. */
void LetterSend_SwapHeldWith(LetterSendScene *self, int place)
{
    if (self->held_kind == LETTER_SEND_HELD_LETTER) {
        Letter_Assign(&self->swapped, &self->held);
        LetterSend_PickUpLetter(self, place);
        LetterSend_PutLetterAt(self, place, &self->swapped);
    }
}
CLEAN_AS(func_ov104_0229d448, LetterSend_SwapHeldWith)

/* func_ov104_0229d484: the held letter, if any, put at `place`; nothing held after. */
void LetterSend_PutHeldAt(LetterSendScene *self, int place)
{
    if (self->held_kind == LETTER_SEND_HELD_LETTER) {
        LetterSend_PutLetterAt(self, place, &self->held);
    }
    self->held_kind = LETTER_SEND_HELD_NONE;
}
CLEAN_AS(func_ov104_0229d484, LetterSend_PutHeldAt)

/* func_ov104_0229d4a8: the letter at `place` (a carried letter or one to post; other places are
 * left alone) copied into `held` and taken from the letters object. */
void LetterSend_PickUpLetter(LetterSendScene *self, int place)
{
    if (!lsend_is_letter_place(self, place)) {
        return;
    }
    int index = lsend_letter_index(self, place);
    self->held_kind = LETTER_SEND_HELD_LETTER;
    Letter_Assign(&self->held, PocketsLetters_LetterAt(&self->letters, index));
    PocketsLetters_ClearPlace(&self->letters, index);
}
CLEAN_AS(func_ov104_0229d4a8, LetterSend_PickUpLetter)

/* func_ov104_0229d500: the held letter drawn where the glide is. */
void LetterSend_FollowGlide(LetterSendScene *self)
{
    self->held_x = Glide_X(&self->glide);
    self->held_y = Glide_Y(&self->glide);
}
CLEAN_AS(func_ov104_0229d500, LetterSend_FollowGlide)

/* func_ov104_0229d528: the held letter drawn at the cursor sprite's frame, 2 left and 4 up. */
void LetterSend_FollowCursorSprite(LetterSendScene *self)
{
    self->held_x = Glider_FrameX(&self->cursor_sprite) - 2;
    self->held_y = Glider_FrameY(&self->cursor_sprite) - 4;
}
CLEAN_AS(func_ov104_0229d528, LetterSend_FollowCursorSprite)

/* func_ov104_0229d554: the held letter drawn at the touch plus the grab's offset. */
void LetterSend_FollowTouch(LetterSendScene *self)
{
    self->held_x = (s32) ((u32) self->grab_dx + data_021f6c58);
    self->held_y = (s32) ((u32) self->grab_dy + data_021f6c54);
}
CLEAN_AS(func_ov104_0229d554, LetterSend_FollowTouch)

/* func_ov104_0229d580: the held letter drawn by the letters object, unless hidden. */
void LetterSend_DrawHeld(LetterSendScene *self)
{
    if (LetterSend_TestFlags(self, LETTER_SEND_FLAG_HELD_HIDDEN) != 0) {
        return;
    }
    if (self->held_kind == LETTER_SEND_HELD_LETTER) {
        PocketsLetters_DrawHeld(&self->letters, self->held_x, self->held_y, &self->held);
    }
}
CLEAN_AS(func_ov104_0229d580, LetterSend_DrawHeld)

/* func_ov104_0229d5c0: the popup queued to tell of the cursor's letter place when it holds a
 * letter; cleared on any other place. */
void LetterSend_UpdatePopup(LetterSendScene *self)
{
    if (lsend_is_letter_place(self, self->cursor)) {
        if (LetterSend_PlaceIsEmpty(self, self->cursor) != 0) {
            Popup_ClearQueued(&self->popup);
        } else {
            self->popup_place = self->cursor;
            Popup_Queue(&self->popup);
        }
    } else {
        Popup_ClearQueued(&self->popup);
    }
}
CLEAN_AS(func_ov104_0229d5c0, LetterSend_UpdatePopup)

/* func_ov104_0229d624: the popup's window put 0x6d left and 0x78 up of its place (8 more up
 * when state flag 2 is set), and filled by the letters object for a letter place. */
void LetterSend_PlacePopup(LetterSendScene *self)
{
    int x = LetterSend_PlaceX(self, self->popup_place) - 0x6d;
    int y = LetterSend_PlaceY(self, self->popup_place) - 0x78;
    if (StateFlags_Test2() != 0) {
        y -= 8;
    }
    /* The popup's base is main's sliding window (popup.h). */
    SlidingWindow_SetPlace((SlidingWindow *) (void *) &self->popup, x, y);
    if (lsend_is_letter_place(self, self->popup_place)) {
        int index = lsend_letter_index(self, self->popup_place);
        PocketsLetters_ShowPlaceText(&self->letters, &self->popup, index);
    }
}
CLEAN_AS(func_ov104_0229d624, LetterSend_PlacePopup)

/* func_ov104_0229d6a4: whether the touch at data_021f6c60/5c is more than 8 pixels from the one
 * at data_021f6c58/54, in x or in y. */
static int lsend_distance(int a, int b)
{
    return a > b ? a - b : b - a;
}

int LetterSend_TouchMoved(LetterSendScene *self)
{
    (void) self;
    return lsend_distance(data_021f6c60, data_021f6c58) > 8 || lsend_distance(data_021f6c5c, data_021f6c54) > 8;
}
CLEAN_AS(func_ov104_0229d6a4, LetterSend_TouchMoved)

/* func_ov104_0229d6e8: a letter place highlighted by the letters object. */
void LetterSend_HighlightPlace(LetterSendScene *self, int place)
{
    if (!lsend_is_letter_place(self, place)) {
        return;
    }
    PocketsLetters_MarkPlace(&self->letters, lsend_letter_index(self, place));
}
CLEAN_AS(func_ov104_0229d6e8, LetterSend_HighlightPlace)

/* func_ov104_0229d724: the highlights of the grid and the letters cleared. */
void LetterSend_ClearHighlights(LetterSendScene *self)
{
    PocketsGrid_ClearMarks(&self->grid);
    PocketsLetters_ClearMarks(&self->letters);
}
CLEAN_AS(func_ov104_0229d724, LetterSend_ClearHighlights)

/* func_ov104_0229d748: a letter place lifted in the letters object (the grid's lift dropped);
 * any other place drops both (LetterSend_ClearSelection). */
void LetterSend_SelectPlace(LetterSendScene *self, int place)
{
    if (lsend_is_letter_place(self, place)) {
        int index = lsend_letter_index(self, place);
        PocketsLetters_Lift(&self->letters, index);
        PocketsGrid_Unlift(&self->grid);
    } else {
        LetterSend_ClearSelection(self);
    }
}
CLEAN_AS(func_ov104_0229d748, LetterSend_SelectPlace)

/* The cursor sprite's base is main's cell layer sprite (glide.h). */
static CellLayerSprite *lsend_cursor_cells(LetterSendScene *self)
{
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

/* func_ov104_0229d798: the lifts of the grid and the letters dropped. */
void LetterSend_ClearSelection(LetterSendScene *self)
{
    PocketsGrid_Unlift(&self->grid);
    PocketsLetters_Unlift(&self->letters);
}
CLEAN_AS(func_ov104_0229d798, LetterSend_ClearSelection)

/* func_ov104_0229d7bc: whether a letter place holds no letter (by the letters object); other
 * places count as empty. */
int LetterSend_PlaceIsEmpty(LetterSendScene *self, int place)
{
    if (lsend_is_letter_place(self, place)) {
        return PocketsLetters_IsEmpty(&self->letters, lsend_letter_index(self, place));
    }
    return 1;
}
CLEAN_AS(func_ov104_0229d7bc, LetterSend_PlaceIsEmpty)

/* func_ov104_0229d7fc: whether a carried letter is dimmed by the letters object
 * (LetterSend_DimUnpostable); 0 for any other place. */
int LetterSend_PlaceIsDimmed(LetterSendScene *self, int place)
{
    if (LetterSend_IsCarriedPlace(self, (unsigned int) place)) {
        return PocketsLetters_IsDimmed(&self->letters, lsend_letter_index(self, place));
    }
    return 0;
}
CLEAN_AS(func_ov104_0229d7fc, LetterSend_PlaceIsDimmed)

/* The carried letters dimmed (PocketsLetters_DimByState's bits): those received, between
 * villagers or in a bottle; the ones the player wrote (state 1) stay usable. */
#define LETTER_SEND_DIM_UNPOSTABLE 0xe

/* func_ov104_0229d830: the grid's places 0 to 14 dimmed, and the carried letters that cannot be
 * posted. */
void LetterSend_DimUnpostable(LetterSendScene *self)
{
    PocketsGrid_DimPlaces(&self->grid, 0, 0xe);
    PocketsLetters_DimByState(&self->letters, LETTER_SEND_DIM_UNPOSTABLE);
}
CLEAN_AS(func_ov104_0229d830, LetterSend_DimUnpostable)

/* The two places below the letters, as the ROM tests them: by the place's low byte. */
static int lsend_is_below(int place)
{
    return (u8) ((u32) place - LETTER_SEND_BELOW_CARRIED) <= 1;
}

/* func_ov104_0229d858: the y of `place`: a letter's by the letters object less 0x10, 0xb6 for
 * both places below the letters, else 0. */
int LetterSend_PlaceY(LetterSendScene *self, int place)
{
    if (lsend_is_letter_place(self, place)) {
        return PocketsLetters_PlaceY(&self->letters, lsend_letter_index(self, place)) - 0x10;
    }
    if (lsend_is_below(place)) {
        return 0xb6;
    }
    return 0;
}
CLEAN_AS(func_ov104_0229d858, LetterSend_PlaceY)

/* func_ov104_0229d8a8: the x of `place`: a letter's by the letters object, 0xbc below the
 * carried letters, 0x74 below the letters to post, else 0. */
int LetterSend_PlaceX(LetterSendScene *self, int place)
{
    if (lsend_is_letter_place(self, place)) {
        return PocketsLetters_PlaceX(&self->letters, lsend_letter_index(self, place));
    }
    if (place == LETTER_SEND_BELOW_CARRIED) {
        return 0xbc;
    }
    if (place == LETTER_SEND_BELOW_OUTBOX) {
        return 0x74;
    }
    return 0;
}
CLEAN_AS(func_ov104_0229d8a8, LetterSend_PlaceX)

/* func_ov104_0229d8f8: the letter of a letter place (the letters object's), else NULL. */
Letter *LetterSend_PlaceLetter(LetterSendScene *self, int place)
{
    if (lsend_is_letter_place(self, place)) {
        return PocketsLetters_LetterAt(&self->letters, lsend_letter_index(self, place));
    }
    return NULL;
}
CLEAN_AS(func_ov104_0229d8f8, LetterSend_PlaceLetter)

/* func_ov104_0229d938: a copy of `letter` put at a letter place by the letters object. */
void LetterSend_PutLetterAt(LetterSendScene *self, int place, const Letter *letter)
{
    if (lsend_is_letter_place(self, place)) {
        PocketsLetters_SetPlace(&self->letters, lsend_letter_index(self, place), letter);
    }
}
CLEAN_AS(func_ov104_0229d938, LetterSend_PutLetterAt)

/* func_ov104_0229d974: the held letter put down at `place`; a letter there is copied aside
 * (`swapped`) and put at the held letter's place (`unk_b7`) first. Always 1. */
int LetterSend_PutHeldLetterAt(LetterSendScene *self, int place)
{
    if (LetterSend_PlaceIsEmpty(self, place) == 0) {
        Letter_Assign(&self->swapped, LetterSend_PlaceLetter(self, place));
        LetterSend_PutLetterAt(self, self->unk_b7, &self->swapped);
    }
    LetterSend_PutHeldAt(self, place);
    return 1;
}
CLEAN_AS(func_ov104_0229d974, LetterSend_PutHeldLetterAt)

/* func_ov104_0229d9bc: the letter place under the touch at (x, y), by the letters object (the
 * carried letters first, then the letters to post); with `with_letter`, only one holding a
 * letter. LETTER_SEND_NO_PLACE for none. */
int LetterSend_LetterPlaceAtTouch(LetterSendScene *self, int x, int y, int with_letter)
{
    int index = PocketsLetters_PocketAtTouch(&self->letters, x, y);
    if (index == POCKETS_LETTERS_NO_PLACE) {
        index = PocketsLetters_TenAt2dAtTouch(&self->letters, x, y);
    }
    if (index == POCKETS_LETTERS_NO_PLACE) {
        return LETTER_SEND_NO_PLACE;
    }
    if (with_letter != 0 && PocketsLetters_IsEmpty(&self->letters, index) != 0) {
        return LETTER_SEND_NO_PLACE;
    }
    return LetterSend_LetterPlace(self, (unsigned int) index);
}
CLEAN_AS(func_ov104_0229d9bc, LetterSend_LetterPlaceAtTouch)

/* The letters object's first place of the letters to post (PocketsLetters_SetTenAt2d). */
#define LETTER_SEND_OUTBOX_INDEX 0x2d

/* func_ov104_0229da18: the place of the letters object's letter `index` (0-9 carried,
 * 0x2d-0x36 to post), else LETTER_SEND_NO_PLACE. The scene is not read. */
u8 LetterSend_LetterPlace(LetterSendScene *self, unsigned int index)
{
    (void) self;
    if (index <= 9) {
        return (u8) (index + LETTER_SEND_CARRIED_FIRST);
    }
    if (index >= LETTER_SEND_OUTBOX_INDEX && index <= LETTER_SEND_OUTBOX_INDEX + 9) {
        return (u8) (index - LETTER_SEND_OUTBOX_INDEX + LETTER_SEND_OUTBOX_FIRST);
    }
    return LETTER_SEND_NO_PLACE;
}
CLEAN_AS(func_ov104_0229da18, LetterSend_LetterPlace)

/* func_ov104_0229da38: the letters object's index of a letter place, else 0. */
u8 LetterSend_LetterIndex(LetterSendScene *self, unsigned int place)
{
    (void) self;
    if (place >= LETTER_SEND_CARRIED_FIRST && place <= LETTER_SEND_CARRIED_LAST) {
        return (u8) (place - LETTER_SEND_CARRIED_FIRST);
    }
    if (place >= LETTER_SEND_OUTBOX_FIRST && place <= LETTER_SEND_OUTBOX_LAST) {
        return (u8) (place - LETTER_SEND_OUTBOX_FIRST + LETTER_SEND_OUTBOX_INDEX);
    }
    return 0;
}
CLEAN_AS(func_ov104_0229da38, LetterSend_LetterIndex)

/* func_ov104_0229da5c: either place below the letters (by the place's low byte). */
int LetterSend_IsBelowPlace(LetterSendScene *self, int place)
{
    (void) self;
    return lsend_is_below(place);
}
CLEAN_AS(func_ov104_0229da5c, LetterSend_IsBelowPlace)

/* func_ov104_0229da70 */
int LetterSend_IsOutboxPlace(LetterSendScene *self, unsigned int place)
{
    (void) self;
    return place >= LETTER_SEND_OUTBOX_FIRST && place <= LETTER_SEND_OUTBOX_LAST;
}
CLEAN_AS(func_ov104_0229da70, LetterSend_IsOutboxPlace)

/* func_ov104_0229da80 */
int LetterSend_IsCarriedPlace(LetterSendScene *self, unsigned int place)
{
    (void) self;
    return place >= LETTER_SEND_CARRIED_FIRST && place <= LETTER_SEND_CARRIED_LAST;
}
CLEAN_AS(func_ov104_0229da80, LetterSend_IsCarriedPlace)

/* func_ov104_0229da90: the layer load task at 0x2c0 taken off the main loop's queue and reset. */
void LetterSend_EndLayerTask(LetterSendScene *self)
{
    LayerTask_End((LayerTask *) (void *) self->unk_2c0);
}
CLEAN_AS(func_ov104_0229da90, LetterSend_EndLayerTask)

/* func_ov104_0229daa0: the place of the first letter to post that is empty (its state is 0),
 * else LETTER_SEND_NO_PLACE. */
u8 LetterSend_FreeOutboxPlace(LetterSendScene *self)
{
    for (int i = 0; i < LETTER_SEND_LETTERS; i++) {
        if (Letter_State(&self->outbox[i]) == 0) {
            return (u8) (i + LETTER_SEND_OUTBOX_FIRST);
        }
    }
    return LETTER_SEND_NO_PLACE;
}
CLEAN_AS(func_ov104_0229daa0, LetterSend_FreeOutboxPlace)

/* func_ov104_0229dad8: the carried place of the current player's first free letter slot (their
 * pockets', not the letters object's), else LETTER_SEND_NO_PLACE. */
int LetterSend_FreeCarriedPlace(LetterSendScene *self)
{
    (void) self;
    int index = CurrentPockets_FreeLetterIndex();
    if (index == -1) {
        return LETTER_SEND_NO_PLACE;
    }
    return (u8) (index + LETTER_SEND_CARRIED_FIRST);
}
CLEAN_AS(func_ov104_0229dad8, LetterSend_FreeCarriedPlace)

/* func_ov104_0229daf8: the letter at `from` picked up and drawn there, then glided to `to` in 4
 * steps. */
void LetterSend_HoldAndGlide(LetterSendScene *self, int from, int to)
{
    LetterSend_PickUpLetter(self, from);
    self->held_x = LetterSend_PlaceX(self, from);
    self->held_y = LetterSend_PlaceY(self, from);
    LetterSend_GlideHeldTo(self, to, 4);
}
CLEAN_AS(func_ov104_0229daf8, LetterSend_HoldAndGlide)

/* The x from which a letter let go is over the carried letters (they are at the right). */
#define LETTER_SEND_CARRIED_SIDE_X 0xc0

/* func_ov104_0229db30: the dragged letter let go with the touch at `x`: one to post dropped
 * over the carried letters goes to the player's first free letter slot, a carried one dropped
 * over the letters to post to the first empty one of them; else, or when there is none, it
 * glides back to `place`. 4 steps. QUIRK: the result is the address MenuScene_SetSubState
 * returns, as an int. */
int LetterSend_DropHeldAtTouch(LetterSendScene *self, int place, int x)
{
    int to = LETTER_SEND_NO_PLACE;
    if (x >= LETTER_SEND_CARRIED_SIDE_X) {
        if (LetterSend_IsOutboxPlace(self, (unsigned int) place)) {
            to = LetterSend_FreeCarriedPlace(self);
        }
    } else if (LetterSend_IsCarriedPlace(self, (unsigned int) place)) {
        to = LetterSend_FreeOutboxPlace(self);
    }
    if (to != LETTER_SEND_NO_PLACE) {
        place = to;
    }
    return (int) (uintptr_t) LetterSend_GlideHeldTo(self, place, 4);
}
CLEAN_AS(func_ov104_0229db30, LetterSend_DropHeldAtTouch)

/* func_ov104_0229db74: the held letter glides from where it is drawn to `place` (kept in
 * `unk_b7`) in `steps` steps, the first taken now. Sub state 0x15 follows it. QUIRK: returns
 * the sub state's address, as MenuScene_SetSubState. */
u8 *LetterSend_GlideHeldTo(LetterSendScene *self, int place, int steps)
{
    self->unk_b7 = (u8) place;
    Glide_SetPlace(&self->glide, self->held_x, self->held_y);
    int x = LetterSend_PlaceX(self, place);
    int y = LetterSend_PlaceY(self, place);
    Glide_MoveTo(&self->glide, x, y, steps);
    Glide_Step(&self->glide);
    LetterSend_FollowGlide(self);
    return MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_HELD_GLIDE);
}
CLEAN_AS(func_ov104_0229db74, LetterSend_GlideHeldTo)

/* func_ov104_0229dbd8: the letter at `place` picked up with the cursor, the popup hidden; when it
 * is held, the sub state to go back to is 8. It follows the cursor sprite; sound 0xd. */
void LetterSend_PickUpWithCursor(LetterSendScene *self, int place)
{
    self->unk_b7 = (u8) place;
    Popup_Hide(&self->popup, 1);
    LetterSend_PickUpLetter(self, place);
    if (self->held_kind == LETTER_SEND_HELD_LETTER) {
        self->return_state = LETTER_SEND_SUB_HOLD;
    }
    LetterSend_FollowCursorSprite(self);
    PocketsSound_Play0d();
}
CLEAN_AS(func_ov104_0229dbd8, LetterSend_PickUpWithCursor)

/* func_ov104_0229dc20: the letter at `place` picked up with the touch, the popup hidden; when it
 * is held, sub state 4 drags it. It follows the touch; sound 0xd. */
void LetterSend_PickUpWithTouch(LetterSendScene *self, int place)
{
    self->unk_b7 = (u8) place;
    Popup_Hide(&self->popup, 1);
    LetterSend_PickUpLetter(self, place);
    if (self->held_kind == LETTER_SEND_HELD_LETTER) {
        MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_DRAG);
    }
    LetterSend_FollowTouch(self);
    PocketsSound_Play0d();
}
CLEAN_AS(func_ov104_0229dc20, LetterSend_PickUpWithTouch)

/* func_ov104_0229dc68: `place` touched (kept in `unk_b5`): sub state 1, the offset from the
 * touch to the place kept, the popup told of the place and shown, its choice opening in 2
 * frames; the letter may be dragged (LETTER_SEND_FLAG_DRAGGABLE, sound 0xc) unless it is
 * dimmed. */
void LetterSend_TouchPlace(LetterSendScene *self, int place)
{
    self->unk_b5 = (u8) place;
    MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_TOUCH_HOLD);
    u8 touch_x = data_021f6c58;
    u8 touch_y = data_021f6c54;
    self->grab_dx = LetterSend_PlaceX(self, self->unk_b5) - touch_x;
    self->grab_dy = LetterSend_PlaceY(self, self->unk_b5) - touch_y;
    self->popup_place = (u8) place;
    Popup_Queue(&self->popup);
    Popup_ShowQueued(&self->popup);
    self->unk_bf = 2;
    if (LetterSend_PlaceIsDimmed(self, place)) {
        LetterSend_ClearFlags(self, LETTER_SEND_FLAG_DRAGGABLE);
    } else {
        LetterSend_SetFlags(self, LETTER_SEND_FLAG_DRAGGABLE);
        PocketsSound_Play0c();
    }
}
CLEAN_AS(func_ov104_0229dc68, LetterSend_TouchPlace)

/* func_ov104_0229dd00 (the cancel action): back to sub state 0 with the cursor sprite hidden
 * while state flag 2 is clear, else to sub state 7 with it at the cursor. */
void LetterSend_EndAction(LetterSendScene *self)
{
    if (StateFlags_IsClear2()) {
        LetterSend_EndActionHidden(self);
    } else {
        LetterSend_EndActionAtCursor(self);
    }
}
CLEAN_AS(func_ov104_0229dd00, LetterSend_EndAction)

/* func_ov104_0229dd20: no popup place, the cursor sprite shown at the cursor, the key repeat
 * reset, the popup told of the cursor's place, sub state 7 and the cursor's place selected. */
void LetterSend_EndActionAtCursor(LetterSendScene *self)
{
    self->popup_place = LETTER_SEND_NO_PLACE;
    LetterSend_ShowCursorAtCursor(self);
    MenuScene_ResetKeyRepeat(lsend_scene(self));
    LetterSend_UpdatePopup(self);
    MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_BROWSE);
    LetterSend_SelectPlace(self, self->cursor);
}
CLEAN_AS(func_ov104_0229dd20, LetterSend_EndActionAtCursor)

/* func_ov104_0229dd54 */
void LetterSend_EndActionHidden(LetterSendScene *self)
{
    LetterSend_HideCursorSprite(self);
    LetterSend_ClearSelection(self);
    MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_TOUCH_IDLE);
}
CLEAN_AS(func_ov104_0229dd54, LetterSend_EndActionHidden)

/* func_ov104_0229dd70 (sub state 0x1c, after LetterSend_PickUpSlotLetter): once the letters
 * object's pick-up is over, the held letter is let go (nothing held) and the action ends. */
void LetterSend_WaitLetGo(LetterSendScene *self)
{
    if (PocketsLetters_StepPickUp(&self->letters)) {
        self->held_kind = LETTER_SEND_HELD_NONE;
        LetterSend_EndAction(self);
    }
}
CLEAN_AS(func_ov104_0229dd70, LetterSend_WaitLetGo)

/* The panel's selected button, for its place. */
#define LETTER_SEND_PANEL_SELECTED (-1)

/* The label button's anchor the cursor sprite points at. */
#define LETTER_SEND_LABEL_ANCHOR 1

/* func_ov104_0229dd98 (sub state 0x1b, after a panel button): while the selected panel button's
 * press plays, the cursor sprite (when shown) follows it, offset by the press's frame; after,
 * the sprite is hidden and phase 1. */
void LetterSend_FollowPanelPress(LetterSendScene *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel) != 0) {
        if (CellLayerSprite_AnimNumber(lsend_cursor_cells(self)) != 0) {
            int frame = ButtonPanel_SelectedPressFrame(&self->panel);
            int x = ButtonPanel_ButtonX(&self->panel, LETTER_SEND_PANEL_SELECTED);
            int y = ButtonPanel_ButtonY(&self->panel, LETTER_SEND_PANEL_SELECTED);
            Glider_PlaceAt(&self->cursor_sprite, frame + x, frame + y);
        }
    } else {
        LetterSend_HideCursorSprite(self);
        MenuScene_SetPhase(lsend_scene(self), 1);
    }
}
CLEAN_AS(func_ov104_0229dd98, LetterSend_FollowPanelPress)

/* func_ov104_0229de04 (sub state 0x1a, after LetterSend_PressLabelButton): while the label
 * button's animation plays, the cursor sprite (when shown) follows its anchor; after, the sprite
 * is hidden, state 9 and phase 1. */
void LetterSend_FollowLabelPress(LetterSendScene *self)
{
    if (LabelButton_StepAnimation(&self->button) != 0) {
        if (CellLayerSprite_AnimNumber(lsend_cursor_cells(self)) != 0) {
            int x = LabelButton_AnchorX(&self->button, LETTER_SEND_LABEL_ANCHOR);
            int y = LabelButton_AnchorY(&self->button, LETTER_SEND_LABEL_ANCHOR);
            Glider_PlaceAt(&self->cursor_sprite, x, y);
        }
    } else {
        LetterSend_HideCursorSprite(self);
        MenuScene_SetState(lsend_scene(self), 9);
        MenuScene_SetPhase(lsend_scene(self), 1);
    }
}
CLEAN_AS(func_ov104_0229de04, LetterSend_FollowLabelPress)

/* func_ov104_0229de6c (sub state 0x19): once the error message is done, back to the sub state
 * kept, the cursor sprite's window flag set. */
void LetterSend_WaitError(LetterSendScene *self)
{
    if (ErrorMessage_Update(&self->error, 0)) {
        MenuScene_SetSubState(lsend_scene(self), self->return_state);
        CellLayerSprite_SetWindow(lsend_cursor_cells(self));
    }
}
CLEAN_AS(func_ov104_0229de6c, LetterSend_WaitError)

/* func_ov104_0229dea0 (sub state 0x18): the action picked runs once the choice is idle. */
void LetterSend_RunActionWhenIdle(LetterSendScene *self)
{
    if (PagedChoice_IsIdle(lsend_choice(self)) != 0) {
        LetterSend_RunAction(self);
    }
}
CLEAN_AS(func_ov104_0229dea0, LetterSend_RunActionWhenIdle)

/* func_ov104_0229dec0 (sub state 0x17): once the delay after the pick has run out, the choice
 * asked to close, the popup hidden, the cursor sprite (when shown) put back at the cursor; sub
 * state 0x18. */
void LetterSend_CloseChoice(LetterSendScene *self)
{
    if (PagedChoice_CountDown(lsend_choice(self)) != 0) {
        PagedChoice_RequestClose(lsend_choice(self), 0);
        Popup_Hide(&self->popup, 1);
        if (CellLayerSprite_AnimNumber(lsend_cursor_cells(self)) != 0) {
            LetterSend_PlaceCursorSprite(self);
        }
        MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_CHOICE_RUN);
    }
}
CLEAN_AS(func_ov104_0229dec0, LetterSend_CloseChoice)

/* func_ov104_0229df10 (sub state 0x16): once the choice is shown, it is run by the keys (the
 * cursor sprite at its default row, sub state 0x0b) when state flag 2 is set, else by the touch
 * (sub state 6). */
void LetterSend_WaitChoiceShown(LetterSendScene *self)
{
    if (PagedChoice_IsShown(lsend_choice(self)) != 0) {
        if (StateFlags_Test2()) {
            LetterSend_PointAtDefaultRow(self);
            MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_CHOICE_BY_KEYS);
        } else {
            MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_CHOICE_BY_TOUCH);
        }
    }
}
CLEAN_AS(func_ov104_0229df10, LetterSend_WaitChoiceShown)

/* func_ov104_0229df4c (sub state 0x15): the held letter follows its glide. When the glide is
 * over the letter is put at its place (`unk_b7`), the action ends, sound 0xe. */
void LetterSend_StepHeldGlide(LetterSendScene *self)
{
    if (Glide_Step(&self->glide) != 0) {
        LetterSend_PutHeldAt(self, self->unk_b7);
        LetterSend_EndAction(self);
        PocketsSound_Play0e();
    } else {
        LetterSend_FollowGlide(self);
    }
}
CLEAN_AS(func_ov104_0229df4c, LetterSend_StepHeldGlide)

/* func_ov104_0229df84 (sub state 0x14): back to the sub state kept once the cursor sprite's
 * animation has ended; once its turn has settled, a hidden held letter is shown again (sound
 * 0xd) and follows the sprite. */
void LetterSend_FinishSwap(LetterSendScene *self)
{
    if (CellLayerSprite_IsDone(lsend_cursor_cells(self))) {
        MenuScene_SetSubState(lsend_scene(self), self->return_state);
    }
    if (Glider_IsTurnSettled(&self->cursor_sprite)) {
        if (LetterSend_TestFlags(self, LETTER_SEND_FLAG_HELD_HIDDEN)) {
            LetterSend_ClearFlags(self, LETTER_SEND_FLAG_HELD_HIDDEN);
            PocketsSound_Play0d();
        }
        LetterSend_FollowCursorSprite(self);
    }
}
CLEAN_AS(func_ov104_0229df84, LetterSend_FinishSwap)

/* func_ov104_0229dfd4 (sub state 0x13): unless the cursor sprite's turn is at its frame 2, the
 * held letter changes places with the one at `target`, the new held letter hidden for now, the
 * popup updated; sub state 0x14. At frame 2, sub state 7. */
void LetterSend_Swap(LetterSendScene *self)
{
    if (Glider_IsTurnAtFrame2(&self->cursor_sprite) == 0) {
        LetterSend_SwapHeldWith(self, self->target);
        LetterSend_SetFlags(self, LETTER_SEND_FLAG_HELD_HIDDEN);
        MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_SWAP_END);
        LetterSend_UpdatePopup(self);
    } else {
        MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_BROWSE);
    }
}
CLEAN_AS(func_ov104_0229dfd4, LetterSend_Swap)

/* func_ov104_0229e01c (sub state 0x12): while the cursor sprite's turn has not settled, the held
 * letter is put down at `target` when the cursor is on it (the popup updated, sub state 7, sound
 * 0xe), else glided there in 4 steps; once it has, the letter follows the sprite. */
void LetterSend_PutDown(LetterSendScene *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite) == 0) {
        u8 target = self->target;
        if (self->cursor == target) {
            LetterSend_PutHeldLetterAt(self, target);
            LetterSend_UpdatePopup(self);
            MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_BROWSE);
            PocketsSound_Play0e();
        } else {
            LetterSend_GlideHeldTo(self, target, 4);
        }
    } else {
        LetterSend_FollowCursorSprite(self);
    }
}
CLEAN_AS(func_ov104_0229e01c, LetterSend_PutDown)

/* func_ov104_0229e070 (sub state 0x11): back to the sub state kept once the cursor sprite's
 * animation has ended; the held letter follows the sprite. */
void LetterSend_FinishPickUp(LetterSendScene *self)
{
    if (CellLayerSprite_IsDone(lsend_cursor_cells(self))) {
        MenuScene_SetSubState(lsend_scene(self), self->return_state);
    }
    LetterSend_FollowCursorSprite(self);
}
CLEAN_AS(func_ov104_0229e070, LetterSend_FinishPickUp)

/* func_ov104_0229e09c (sub state 0x10): once the cursor sprite's turn has settled, the letter at
 * the cursor is picked up; sub state 0x11. */
void LetterSend_PickUpAtCursor(LetterSendScene *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite)) {
        LetterSend_PickUpWithCursor(self, self->cursor);
        MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_PICK_UP_END);
    }
}
CLEAN_AS(func_ov104_0229e09c, LetterSend_PickUpAtCursor)

/* func_ov104_0229e0cc (sub state 0x0f): once the cursor sprite's animation has ended, its set's
 * first animation; sub state 7. */
void LetterSend_FinishPlacePress(LetterSendScene *self)
{
    if (CellLayerSprite_IsDone(lsend_cursor_cells(self))) {
        LetterSend_ShowCursorFirstOfSet(self);
        MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_BROWSE);
    }
}
CLEAN_AS(func_ov104_0229e0cc, LetterSend_FinishPlacePress)

/* func_ov104_0229e0f4 (sub state 0x0e): once the cursor sprite's animation has ended, the place
 * below the carried letters posts, the one below the letters to post cancels. */
void LetterSend_PressPlace(LetterSendScene *self)
{
    if (CellLayerSprite_IsDone(lsend_cursor_cells(self)) == 0) {
        return;
    }
    if (self->cursor == LETTER_SEND_BELOW_CARRIED) {
        LetterSend_Post(self);
    } else {
        LetterSend_Cancel(self);
    }
}
CLEAN_AS(func_ov104_0229e0f4, LetterSend_PressPlace)

/* Obj_ov104_0229f6d0::func_ov104_0229e128 (sub state 0x0d): once the cursor sprite stops moving,
 * back to the sub state kept (the cursor's place selected for sub state 7), which runs at once;
 * the held letter follows the sprite. */
void LetterSend_WaitCursorSprite(LetterSendScene *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) == 0) {
        MenuScene_SetSubState(lsend_scene(self), self->return_state);
        if (self->return_state == LETTER_SEND_SUB_BROWSE) {
            LetterSend_SelectPlace(self, self->cursor);
        }
        LetterSend_RunSubState(self);
    }
    LetterSend_FollowCursorSprite(self);
}
CLEAN_AS(_ZN18Obj_ov104_0229f6d019func_ov104_0229e128Ev, LetterSend_WaitCursorSprite)

/* The value kept with choice row `row` (ChoiceEntries.values), read as the ROM does at
 * 0x28f1 + row. */
static u8 lsend_entry_value(LetterSendScene *self, int row)
{
    const u8 *bytes = (const u8 *) self;
    return bytes[offsetof(LetterSendScene, entries) + offsetof(ChoiceEntries, values) + (size_t) row];
}

/* A choice row picked with the sound of a pick, except for the row of the pick-up action (sound
 * 0x24 instead); its action kept; sub state 0x17. */
static void lsend_pick_choice_row(LetterSendScene *self, int row)
{
    self->action = lsend_entry_value(self, row);
    int with_sound = 1;
    if (self->action == LETTER_SEND_ACTION_PICK_UP) {
        with_sound = 0;
        SoundSys_PlaySe(0x24);
    }
    PagedChoice_PickRowWithSound(lsend_choice(self), row, with_sound);
    MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_CHOICE_CLOSE);
}

/* func_ov104_0229e170 (sub state 0x0c): once the cursor sprite's animation has ended, the
 * choice row it points at is picked. */
void LetterSend_PickChoiceRow(LetterSendScene *self)
{
    if (CellLayerSprite_IsDone(lsend_cursor_cells(self)) == 0) {
        return;
    }
    lsend_pick_choice_row(self, self->choice_row);
}
CLEAN_AS(func_ov104_0229e170, LetterSend_PickChoiceRow)

/* The pen (autoload_2/input.c): down, and gone down or up this frame. */
extern u8 data_021fbdd8;
extern u8 data_021fbddc;

/* The pad (autoload_2/input.h) and the buttons read in `pressed`. */
extern PadState data_021fbe40;
#define LETTER_SEND_PAD_A 0x0001
#define LETTER_SEND_PAD_B 0x0002
#define LETTER_SEND_PAD_START 0x0008
#define LETTER_SEND_PAD_Y 0x0800

/* The pen went down this frame. */
static int lsend_pen_pressed(void)
{
    return data_021fbdd8 != 0 && data_021fbddc != 0;
}

/* func_ov104_0229e1d4 (sub state 0x0b): the choice by the keys. A touch cancels it; the keys
 * move the row (from row 1 round for the fixed menu), the cursor sprite gliding to it; A plays
 * the sprite's second animation of its set and picks the row (sub state 0x0c), B points at the
 * last row. */
void LetterSend_ChooseByKeys(LetterSendScene *self)
{
    if (MenuScene_TakeTouch(lsend_scene(self))) {
        LetterSend_CancelChoice(self);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(lsend_scene(self));
    u8 first = (u8) LetterSend_TestFlags(self, LETTER_SEND_FLAG_FIXED_MENU);
    if (PagedChoice_MoveCursor(lsend_choice(self), keys, &self->choice_row, first)) {
        LetterSend_GlideToRow(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & LETTER_SEND_PAD_A) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_CHOICE_PICK);
    } else if (pressed & LETTER_SEND_PAD_B) {
        LetterSend_PointAtLastRow(self);
    }
}
CLEAN_AS(func_ov104_0229e1d4, LetterSend_ChooseByKeys)

/* func_ov104_0229e260 (sub state 0x0a): the label button pressed once the cursor sprite's
 * animation has ended. */
void LetterSend_WaitLabelPress(LetterSendScene *self)
{
    if (CellLayerSprite_IsDone(lsend_cursor_cells(self))) {
        LetterSend_PressLabelButton(self);
    }
}
CLEAN_AS(func_ov104_0229e260, LetterSend_WaitLabelPress)

/* func_ov104_0229e280 (sub state 9): the label button by the keys. A hidden cursor sprite is
 * shown on the button's anchor (animation 1); a touch hides it (sub state 5); A or B plays the
 * sprite's second animation of its set, sub state 0x0a. */
void LetterSend_LabelByKeys(LetterSendScene *self)
{
    if (CellLayerSprite_AnimNumber(lsend_cursor_cells(self)) == 0) {
        int x = LabelButton_AnchorX(&self->button, LETTER_SEND_LABEL_ANCHOR);
        int y = LabelButton_AnchorY(&self->button, LETTER_SEND_LABEL_ANCHOR);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
        Glider_SetAnim(&self->cursor_sprite, 1);
    }
    if (MenuScene_TakeTouch(lsend_scene(self))) {
        LetterSend_HideCursorSprite(self);
        MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_LABEL_BY_TOUCH);
    } else if (data_021fbe40.pressed & (LETTER_SEND_PAD_A | LETTER_SEND_PAD_B)) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_LABEL_PRESS);
    }
}
CLEAN_AS(func_ov104_0229e280, LetterSend_LabelByKeys)

/* func_ov104_0229e314 (sub state 8): a held letter moved with the cursor. A move of the cursor
 * updates the popup and moves the sprite (the popup hidden, its queue kept). A puts the letter
 * down at the cursor (sub state 0x12) when the place is empty, else swaps (sub state 0x13); not
 * on a dimmed place. B sends the letter back to its place (sub state 0x12). Else the letter
 * follows the sprite and a queued popup is shown. */
void LetterSend_MoveHeldByKeys(LetterSendScene *self)
{
    int keys = (int) MenuScene_LatchRepeatedKeys(lsend_scene(self));
    if (LetterSend_MoveCursor(self, keys, 1) != 0) {
        LetterSend_UpdatePopup(self);
        LetterSend_GlideToCursor(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & LETTER_SEND_PAD_A) {
        if (LetterSend_PlaceIsDimmed(self, self->cursor)) {
            return;
        }
        if (LetterSend_PlaceIsEmpty(self, self->cursor)) {
            LetterSend_BeginSubState12(self, self->cursor);
        } else {
            LetterSend_BeginSubState13(self, self->cursor);
        }
    } else if (pressed & LETTER_SEND_PAD_B) {
        LetterSend_BeginSubState12(self, self->unk_b7);
    } else {
        LetterSend_FollowCursorSprite(self);
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov104_0229e314, LetterSend_MoveHeldByKeys)

/* func_ov104_0229e3b8 (sub state 7): the cursor moved by the keys, nothing held. A touch ends the
 * action without the sprite. A move updates the popup and moves the sprite (the popup hidden,
 * its queue kept). Unless the cursor's letter is dimmed: A on a letter opens its choice, A below
 * the letters presses the place; Y sends a carried letter to the first empty place to post, a
 * letter to post to the player's first free letter slot. Else B cancels and START posts, or a
 * queued popup is shown. */
void LetterSend_BrowseByKeys(LetterSendScene *self)
{
    if (MenuScene_TakeTouch(lsend_scene(self))) {
        LetterSend_EndActionHidden(self);
        Popup_Hide(&self->popup, 1);
        return;
    }
    if (LetterSend_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(lsend_scene(self)), 0) != 0) {
        LetterSend_UpdatePopup(self);
        LetterSend_GlideToCursor(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    if (LetterSend_PlaceIsDimmed(self, self->cursor) == 0) {
        u16 pressed = data_021fbe40.pressed;
        if (pressed & LETTER_SEND_PAD_A) {
            if (lsend_is_letter_place(self, self->cursor)) {
                if (LetterSend_PlaceIsEmpty(self, self->cursor) == 0) {
                    LetterSend_OpenLetterMenu(self, self->cursor, 0);
                }
            } else if (LetterSend_IsBelowPlace(self, self->cursor)) {
                LetterSend_BeginSubState0e(self);
            }
            return;
        }
        if (pressed & LETTER_SEND_PAD_Y) {
            if (lsend_is_letter_place(self, self->cursor) && LetterSend_PlaceIsEmpty(self, self->cursor) == 0) {
                int to;
                if (LetterSend_IsCarriedPlace(self, self->cursor)) {
                    to = LetterSend_FreeOutboxPlace(self);
                } else {
                    to = LetterSend_FreeCarriedPlace(self);
                }
                if (to != LETTER_SEND_NO_PLACE) {
                    LetterSend_HoldAndGlide(self, self->cursor, to);
                    Popup_Hide(&self->popup, 1);
                }
            }
            return;
        }
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & LETTER_SEND_PAD_B) {
        LetterSend_HideCursorSprite(self);
        LetterSend_Cancel(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    if (pressed & LETTER_SEND_PAD_START) {
        LetterSend_HideCursorSprite(self);
        LetterSend_Post(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    Popup_ShowQueued(&self->popup);
}
CLEAN_AS(func_ov104_0229e3b8, LetterSend_BrowseByKeys)

/* func_ov104_0229e54c (sub state 6): the choice by the touch, once shown. A button cancels it;
 * the pen going down picks the row under it (the last one outside the window), but not the set
 * apart first row of the fixed menu. */
void LetterSend_ChooseByTouch(LetterSendScene *self)
{
    if (PagedChoice_IsShown(lsend_choice(self)) == 0) {
        return;
    }
    if (MenuScene_TakeButtons(lsend_scene(self), 1)) {
        LetterSend_CancelChoice(self);
        return;
    }
    if (!lsend_pen_pressed()) {
        return;
    }
    int row = PagedChoice_RowAtOrLast(lsend_choice(self), data_021f6c58, data_021f6c54);
    if (row < 0) {
        return;
    }
    if (LetterSend_TestFlags(self, LETTER_SEND_FLAG_FIXED_MENU) != 0 && row == 0) {
        return;
    }
    lsend_pick_choice_row(self, row);
}
CLEAN_AS(func_ov104_0229e54c, LetterSend_ChooseByTouch)

/* func_ov104_0229e608 (sub state 5): the label button by the touch. A button gives it to the
 * keys (sub state 9); a touch on it presses it. */
void LetterSend_LabelByTouch(LetterSendScene *self)
{
    if (MenuScene_TakeButtons(lsend_scene(self), 1)) {
        MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_LABEL_BY_KEYS);
        return;
    }
    if (LabelButton_IsTouched(&self->button)) {
        LetterSend_PressLabelButton(self);
    }
}
CLEAN_AS(func_ov104_0229e608, LetterSend_LabelByTouch)

/* func_ov104_0229e63c (sub state 4): the held letter dragged with the touch, the highlights
 * cleared. The letter place under it (8 right and 0x18 below where it is drawn) is taken, but
 * not a place of the other set of letters that holds a letter. While the pen is down that place
 * is highlighted. Let go on it, when it is not dimmed, the letter is put down there (sound 0xe)
 * and the action ends; else LetterSend_DropHeldAtTouch sends it to its place or to the other
 * set. */
void LetterSend_DragHeld(LetterSendScene *self)
{
    LetterSend_FollowTouch(self);
    LetterSend_ClearHighlights(self);
    int x = (int) ((u32) self->held_x + 8);
    int place = LetterSend_LetterPlaceAtTouch(self, x, (int) ((u32) self->held_y + 0x18), 0);

    int crosses = (LetterSend_IsCarriedPlace(self, (unsigned int) place) && LetterSend_IsOutboxPlace(self, self->unk_b7)) ||
                  (LetterSend_IsOutboxPlace(self, (unsigned int) place) && LetterSend_IsCarriedPlace(self, self->unk_b7));
    if (crosses && LetterSend_PlaceIsEmpty(self, place) == 0) {
        place = LETTER_SEND_NO_PLACE;
    }

    if (place == LETTER_SEND_NO_PLACE) {
        if (data_021fbdd8 == 0) {
            LetterSend_DropHeldAtTouch(self, self->unk_b7, x);
        }
        return;
    }
    if (data_021fbdd8 != 0) {
        LetterSend_HighlightPlace(self, place);
        return;
    }
    if (LetterSend_PlaceIsDimmed(self, place) == 0 && LetterSend_PutHeldLetterAt(self, place) != 0) {
        PocketsSound_Play0e();
        LetterSend_EndAction(self);
        return;
    }
    LetterSend_DropHeldAtTouch(self, self->unk_b7, x);
}
CLEAN_AS(func_ov104_0229e63c, LetterSend_DragHeld)

/* After `unk_bf` more frames, the touched place's choice opens above the popup; sub state 2. */
static void lsend_count_down_to_choice(LetterSendScene *self)
{
    if (self->unk_bf != 0) {
        self->unk_bf--;
    } else {
        LetterSend_OpenLetterMenu(self, self->unk_b5, 1);
        MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_TOUCH_CHOICE);
    }
}

/* func_ov104_0229e714 (sub state 3): once the popup is up, the count down to the touched place's
 * choice. */
void LetterSend_OpenTouchedChoice(LetterSendScene *self)
{
    if (Popup_IsUp(&self->popup) == 0) {
        return;
    }
    lsend_count_down_to_choice(self);
}
CLEAN_AS(func_ov104_0229e714, LetterSend_OpenTouchedChoice)

/* func_ov104_0229e75c (sub state 2): a touched place's choice is open. The pen let go hands the
 * choice to the touch (sub state 6); the pen moving off a letter that may be dragged picks it up
 * (LetterSend_PickUpWithTouch), closing the choice and hiding the popup. */
void LetterSend_WatchChoiceTouch(LetterSendScene *self)
{
    if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_CHOICE_BY_TOUCH);
        return;
    }
    if (LetterSend_TestFlags(self, LETTER_SEND_FLAG_DRAGGABLE) == 0) {
        return;
    }
    if (LetterSend_TouchMoved(self) == 0) {
        return;
    }
    LetterSend_PickUpWithTouch(self, self->unk_b5);
    PagedChoice_RequestClose(lsend_choice(self), 0);
    Popup_Hide(&self->popup, 1);
}
CLEAN_AS(func_ov104_0229e75c, LetterSend_WatchChoiceTouch)

/* The frames a popup stays after the pen leaves a place. */
#define LETTER_SEND_POPUP_FRAMES 0x3c

/* Obj_ov104_0229f6d0::func_ov104_0229e7b8 (sub state 1): the pen holds a touched place. Let go
 * on a letter that may be dragged, sub state 3 runs at once; else sub state 0 with the popup
 * staying 0x3c frames. While held, the pen moving off a letter that may be dragged picks it up;
 * else, once the popup is up, the count down to the place's choice; before that, a queued popup
 * is shown. */
void LetterSend_HoldTouchOnPlace(LetterSendScene *self)
{
    if (data_021fbdd8 == 0) {
        if (LetterSend_TestFlags(self, LETTER_SEND_FLAG_DRAGGABLE) != 0) {
            MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_OPEN_TOUCHED);
            LetterSend_RunSubState(self);
        } else {
            MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_TOUCH_IDLE);
            Popup_SetTimer(&self->popup, LETTER_SEND_POPUP_FRAMES);
        }
        return;
    }
    if (LetterSend_TestFlags(self, LETTER_SEND_FLAG_DRAGGABLE) != 0) {
        if (LetterSend_TouchMoved(self) != 0) {
            LetterSend_PickUpWithTouch(self, self->unk_b5);
            return;
        }
        if (Popup_IsUp(&self->popup) != 0) {
            lsend_count_down_to_choice(self);
            return;
        }
    }
    Popup_ShowQueued(&self->popup);
}
CLEAN_AS(_ZN18Obj_ov104_0229f6d019func_ov104_0229e7b8Ev, LetterSend_HoldTouchOnPlace)

/* func_ov104_0229e864 (sub state 0): the touch is in use and the cursor sprite hidden. A button
 * puts the cursor sprite back at the cursor (sub state 7). The pen going down touches the letter
 * place under it (looked for 16 pixels lower) when it holds a letter; else presses the panel's
 * post button, else its cancel button, when on it. */
void LetterSend_IdleByTouch(LetterSendScene *self)
{
    if (MenuScene_TakeButtons(lsend_scene(self), 1) != 0) {
        LetterSend_EndActionAtCursor(self);
        return;
    }
    if (!lsend_pen_pressed()) {
        return;
    }
    int place = LetterSend_LetterPlaceAtTouch(self, data_021f6c58, data_021f6c54 + 0x10, 1);
    if (place != LETTER_SEND_NO_PLACE) {
        LetterSend_TouchPlace(self, place);
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, LETTER_SEND_BUTTON_POST) != 0) {
        LetterSend_Post(self);
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, LETTER_SEND_BUTTON_CANCEL) != 0) {
        LetterSend_Cancel(self);
    }
}
CLEAN_AS(func_ov104_0229e864, LetterSend_IdleByTouch)

/* The panel's message of its layout 6. */
#define LETTER_SEND_PANEL_MESSAGE 0x65

/* func_ov104_0229e8f8: a step of the wallet display's setup (its answer unused), the panel's
 * text colours loaded and its layout 6 with message 0x65. */
void LetterSend_PreparePanel(LetterSendScene *self)
{
    PocketsWallet_LoadObjFiles(&self->wallet);
    ButtonPanel_LoadTextColors(&self->panel);
    ButtonPanel_SetLayout6(&self->panel, LETTER_SEND_PANEL_MESSAGE);
}
CLEAN_AS(func_ov104_0229e8f8, LetterSend_PreparePanel)

/* The scene's layers: 6 the scene, 4 the page. */
#define LETTER_SEND_SCENE_LAYER 6
#define LETTER_SEND_PAGE_LAYER 4

/* The files of the page layer: its palettes, its screen and its characters; the heap they are
 * loaded with. */
extern const char data_ov104_0229f730[]; /* "menu/inventory/b_itm_post.bpl" */
extern const char data_ov104_0229f750[]; /* "menu/inventory/b_itm_bg_ltr2.bsc" */
extern const char data_ov104_0229f774[]; /* "menu/inventory/b_itm_post.bch" */
extern Heap *data_021fbe94;

/* func_ov104_0229e924: the page layer's palette 4, its screen and its characters 0x1e2-0x227
 * loaded from their files. */
void LetterSend_LoadPageLayer(LetterSendScene *self)
{
    (void) self;
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadPalettesFromFile(data_ov104_0229f730, heap, LETTER_SEND_PAGE_LAYER, 4, 4, 4);
    DisplayLayer_LoadScreenFromFile(data_ov104_0229f750, heap, LETTER_SEND_PAGE_LAYER);
    DisplayLayer_LoadCharsFromFile(data_ov104_0229f774, heap, LETTER_SEND_PAGE_LAYER, 0x1e2, 0x1e2, 0x227);
}
CLEAN_AS(func_ov104_0229e924, LetterSend_LoadPageLayer)

/* func_ov104_0229e978: the wallet's display set up, its `screen_a` 0. */
void LetterSend_PrepareWallet(LetterSendScene *self)
{
    PocketsWallet_SetUp(&self->wallet, 0);
}
CLEAN_AS(func_ov104_0229e978, LetterSend_PrepareWallet)

/* func_ov104_0229e98c: the scene layer at priority 2 and the page layer at priority 1, both with
 * their plain background settings. */
void LetterSend_SetUpLayers(void)
{
    DisplayLayer_SetPriority(LETTER_SEND_SCENE_LAYER, 2);
    DisplayLayer_SetBgControl(LETTER_SEND_SCENE_LAYER, 0, 0, 0);
    DisplayLayer_SetPriority(LETTER_SEND_PAGE_LAYER, 1);
    DisplayLayer_SetBgControl(LETTER_SEND_PAGE_LAYER, 0, 0, 0);
}
CLEAN_AS(func_ov104_0229e98c, LetterSend_SetUpLayers)

/* The letter's text layer (the letter view's, and the choice's). */
#define LETTER_SEND_TEXT_LAYER 3

/* The margin of the wipes on window 2. */
#define LETTER_SEND_WIPE_MARGIN 0x30

/* What the parent (overlay 92's) is told (func_ov092_02299324) when the scene ends without a
 * letter to show, and what it is told when the scene closes. */
#define LETTER_SEND_PARENT_CODE_END 0x44

/* A letter's constructor, handed to __cxa_vec_ctor with its destructor (so the game's symbols). */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void func_02066694(void *letter);

/* The tables of member functions (ov004/member_pointer.h): the guards, the tables and their
 * constants (the symbol table names the sub states' table's second part, from sub state 0x10,
 * data_ov104_0229f880). */
extern u32 data_ov104_0229f7a0; /* the sub states' guard */
extern u32 data_ov104_0229f7a4; /* the states' guard */
extern MemberPointer data_ov104_0229f7a8[LETTER_SEND_STATES];
extern MemberPointer data_ov104_0229f800[LETTER_SEND_SUB_STATES];
extern const MemberPointer data_ov104_0229f588, data_ov104_0229f590, data_ov104_0229f598, data_ov104_0229f5a0,
    data_ov104_0229f5a8, data_ov104_0229f5b0, data_ov104_0229f5b8, data_ov104_0229f5c0, data_ov104_0229f5c8,
    data_ov104_0229f5d0, data_ov104_0229f5d8, data_ov104_0229f5e0, data_ov104_0229f5e8, data_ov104_0229f5f0,
    data_ov104_0229f5f8, data_ov104_0229f600, data_ov104_0229f608, data_ov104_0229f610, data_ov104_0229f618,
    data_ov104_0229f620, data_ov104_0229f628, data_ov104_0229f630, data_ov104_0229f638, data_ov104_0229f640,
    data_ov104_0229f648, data_ov104_0229f650, data_ov104_0229f658, data_ov104_0229f660, data_ov104_0229f668,
    data_ov104_0229f670, data_ov104_0229f678, data_ov104_0229f680, data_ov104_0229f688, data_ov104_0229f690,
    data_ov104_0229f698, data_ov104_0229f6a0, data_ov104_0229f6a8, data_ov104_0229f6b0, data_ov104_0229f6b8,
    data_ov104_0229f6c0;

/* The parent process. */
static Process *lsend_parent(LetterSendScene *self)
{
    return Process_GetParent((Process *) (void *) self);
}

/* A member drawn through its class (vtable slot 2). */
static void lsend_draw_member(void *object)
{
    const u32 *vtable = (const u32 *) (uintptr_t) *(const u32 *) object;
    ((void (*)(void *))(uintptr_t) vtable[2])(object);
}

/* func_ov104_0229e9c0: the end of a frame: the choice and the wallet's display updated, and the
 * popup placed when its update asks for it. */
void LetterSend_EndFrame(LetterSendScene *self)
{
    PagedChoice_Update(lsend_choice(self));
    PocketsWallet_Update(&self->wallet);
    if (Popup_Update(&self->popup) != 0) {
        LetterSend_PlacePopup(self);
    }
}
CLEAN_AS(func_ov104_0229e9c0, LetterSend_EndFrame)

/* func_ov104_0229e9f8: the start of a frame: the layer task ended, the three objects of ov094's
 * updated and the panel's texts closed. */
void LetterSend_BeginFrame(LetterSendScene *self)
{
    LetterSend_EndLayerTask(self);
    PocketsWallet_BeginFrame(&self->wallet);
    PocketsGrid_BeginFrame(&self->grid);
    PocketsLetters_BeginFrame(&self->letters);
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov104_0229e9f8, LetterSend_BeginFrame)

/* func_ov104_0229ea38 */
void LetterSend_EndInteractiveFrame(LetterSendScene *self)
{
    LetterSend_EndFrame(self);
}
CLEAN_AS(func_ov104_0229ea38, LetterSend_EndInteractiveFrame)

/* func_ov104_0229ea40: the start of a frame, then the cursor sprite's update through its class
 * (vtable slot 3). */
void LetterSend_BeginInteractiveFrame(LetterSendScene *self)
{
    LetterSend_BeginFrame(self);
    lsend_update_cursor_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov104_0229ea40, LetterSend_BeginInteractiveFrame)

/* func_ov104_0229ea5c: the members' teardown before the scene closes. */
void LetterSend_Teardown(LetterSendScene *self)
{
    LetterSend_EndLayerTask(self);
    PocketsWallet_Teardown(&self->wallet);
    PocketsGrid_Teardown(&self->grid);
    PagedChoice_Dismiss(lsend_choice(self));
    LetterView_ReleaseBoxes(&self->view);
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov104_0229ea5c, LetterSend_Teardown)

/* func_ov104_0229eaa8: the scene's setup: no flags, the three objects of ov094's set up, no
 * popup place, the glide stopped, nothing held, the cursor on the first carried letter, the
 * choice and the letter view on layer 3; the ten letters to post emptied, the carried letters
 * saved for a cancel; no open delay. */
void LetterSend_Setup(LetterSendScene *self)
{
    self->flags = 0;
    PocketsGrid_Init(&self->grid, 2);
    PocketsLetters_Init(&self->letters, 1);
    PocketsWallet_Init(&self->wallet, 6);
    self->popup_place = LETTER_SEND_NO_PLACE;
    Glide_Stop(&self->glide);
    self->held_kind = LETTER_SEND_HELD_NONE;
    self->cursor = LETTER_SEND_CARRIED_FIRST;
    PagedChoice_Init(lsend_choice(self), LETTER_SEND_TEXT_LAYER, 0, NULL);
    LetterView_Init(&self->view, LETTER_SEND_TEXT_LAYER);
    for (int i = 0; i < LETTER_SEND_LETTERS; i++) {
        Letter_Clear(&self->outbox[i]);
    }
    LetterSend_SaveCarried(self);
    self->unk_bf = 0;
}
CLEAN_AS(func_ov104_0229eaa8, LetterSend_Setup)

/* func_ov104_0229eb48: the page layer scrolled by the wipe (16 pixels up), the wipe's x kept for
 * the letters to post. */
void LetterSend_ScrollOutboxLayer(LetterSendScene *self)
{
    MenuScene_ScrollWipe(lsend_scene(self), LETTER_SEND_PAGE_LAYER, 0, -0x10);
    self->unk_9c = MenuScene_WipeOffsetX(lsend_scene(self));
}
CLEAN_AS(func_ov104_0229eb48, LetterSend_ScrollOutboxLayer)

/* func_ov104_0229eb68: the scene layer scrolled by the wipe (16 pixels up), the wipe's y kept
 * for the objects and the panel. */
void LetterSend_ScrollSceneLayer(LetterSendScene *self)
{
    MenuScene_ScrollWipe(lsend_scene(self), LETTER_SEND_SCENE_LAYER, 0, -0x10);
    self->unk_98 = MenuScene_WipeOffsetY(lsend_scene(self));
}
CLEAN_AS(func_ov104_0229eb68, LetterSend_ScrollSceneLayer)

/* func_ov104_0229eb88: the letter's two layers (text and paper) scrolled by the wipe. */
void LetterSend_ScrollLetterLayers(LetterSendScene *self)
{
    MenuScene_ScrollWipe(lsend_scene(self), LETTER_SEND_TEXT_LAYER, 0, 0);
    MenuScene_ScrollWipe(lsend_scene(self), LETTER_SEND_PAGE_LAYER, 0, 0);
}
CLEAN_AS(func_ov104_0229eb88, LetterSend_ScrollLetterLayers)

/* func_ov104_0229eba8 (state 0x0a): the letter wipes out; when done, its layers hidden, the
 * label button no longer drawn and the scene set up again (state 0, run at once). Else its
 * layers follow the wipe. */
void LetterSend_LetterWipeOut(LetterSendScene *self)
{
    if (MenuScene_StepWipe(lsend_scene(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(LETTER_SEND_TEXT_LAYER);
        DisplayLayer_HideAndResetScroll(LETTER_SEND_PAGE_LAYER);
        LetterSend_ClearFlags(self, LETTER_SEND_FLAG_LETTER_SHOWN);
        LetterSend_StartSetup(self);
    } else {
        LetterSend_ScrollLetterLayers(self);
    }
}
CLEAN_AS(func_ov104_0229eba8, LetterSend_LetterWipeOut)

/* func_ov104_0229ebe0 (state 9, after the label button's press): the letter starts to wipe out
 * on window 2 (state 0x0a). */
void LetterSend_StartLetterWipeOut(LetterSendScene *self)
{
    MenuScene_StartWipeOnWindow2(lsend_scene(self), 3, 0, 0, LETTER_SEND_WIPE_MARGIN);
    LetterSend_ScrollLetterLayers(self);
    MenuScene_SetState(lsend_scene(self), LETTER_SEND_STATE_LETTER_WIPE_OUT);
}
CLEAN_AS(func_ov104_0229ebe0, LetterSend_StartLetterWipeOut)

/* func_ov104_0229ec0c (state 8): the letter wipes in; when done, phase 2 and its label button by
 * the touch (sub state 5) while state flag 2 is clear, else by the keys (sub state 9). Else its
 * layers follow the wipe. */
void LetterSend_LetterWipeIn(LetterSendScene *self)
{
    if (MenuScene_StepWipeBack(lsend_scene(self), 0) != 0) {
        MenuScene_SetPhase(lsend_scene(self), MENU_SCENE_PHASE_INTERACTIVE);
        if (StateFlags_IsClear2()) {
            MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_LABEL_BY_TOUCH);
        } else {
            MenuScene_SetSubState(lsend_scene(self), LETTER_SEND_SUB_LABEL_BY_KEYS);
        }
    } else {
        LetterSend_ScrollLetterLayers(self);
    }
}
CLEAN_AS(func_ov104_0229ec0c, LetterSend_LetterWipeIn)

/* func_ov104_0229ec4c (state 7): the letter of the place whose choice was open is shown:
 * Letter_AdvanceReceived moves its state on, the letter view shows it (layers 3 and 4, priority
 * 1), the two layers shown and wiping in on window 2 (state 8), and the label button is shown
 * with message 0x88 and drawn. */
void LetterSend_ShowLetter(LetterSendScene *self)
{
    Letter *letter = LetterSend_PlaceLetter(self, self->slot);
    Letter_AdvanceReceived(letter);
    LetterView_Show(&self->view, letter, LETTER_SEND_TEXT_LAYER, LETTER_SEND_PAGE_LAYER, 1);
    MenuScene_StartWipeCoveredOnWindow2(lsend_scene(self), 3, 0, 0, LETTER_SEND_WIPE_MARGIN);
    DisplayLayer_Show(LETTER_SEND_TEXT_LAYER);
    DisplayLayer_Show(LETTER_SEND_PAGE_LAYER);
    LetterSend_ScrollLetterLayers(self);
    MenuScene_SetState(lsend_scene(self), LETTER_SEND_STATE_LETTER_WIPE_IN);
    LabelButton_ShowLowerRight(&self->button, 0x88);
    LetterSend_SetFlags(self, LETTER_SEND_FLAG_LETTER_SHOWN);
}
CLEAN_AS(func_ov104_0229ec4c, LetterSend_ShowLetter)

/* func_ov104_0229ecc0 (state 6): the scene wipes out; when done, its layer hidden and its
 * objects no longer drawn: with LETTER_SEND_FLAG_ACTION_1 the letter is shown (state 7, run at
 * once), else the scene is no longer drawn and the run phase begins. Else the scene layer follows
 * the wipe. */
void LetterSend_SceneWipeOut(LetterSendScene *self)
{
    if (MenuScene_StepWipe(lsend_scene(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(LETTER_SEND_SCENE_LAYER);
        LetterSend_ClearFlags(self, LETTER_SEND_FLAG_SCROLLED);
        if (LetterSend_TestFlags(self, LETTER_SEND_FLAG_ACTION_1) != 0) {
            MenuScene_SetState(lsend_scene(self), LETTER_SEND_STATE_SHOW_LETTER);
            LetterSend_ShowLetter(self);
        } else {
            LetterSend_ClearFlags(self, LETTER_SEND_FLAG_SHOWN);
            MenuScene_SetPhase(lsend_scene(self), MENU_SCENE_PHASE_DELETE);
        }
    } else {
        LetterSend_ScrollSceneLayer(self);
    }
}
CLEAN_AS(func_ov104_0229ecc0, LetterSend_SceneWipeOut)

/* func_ov104_0229ed1c (state 5): the letters to post wipe out; when done, the page layer hidden,
 * its letters no longer drawn, and the scene starts to wipe out on window 2 (state 6, run at
 * once). Else the page layer follows the wipe. */
void LetterSend_OutboxWipeOut(LetterSendScene *self)
{
    if (MenuScene_StepWipe(lsend_scene(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(LETTER_SEND_PAGE_LAYER);
        LetterSend_ClearFlags(self, LETTER_SEND_FLAG_OUTBOX_SHOWN);
        MenuScene_StartWipeOnWindow2(lsend_scene(self), 8, 0, 0, LETTER_SEND_WIPE_MARGIN);
        MenuScene_SetState(lsend_scene(self), LETTER_SEND_STATE_SCENE_WIPE_OUT);
        LetterSend_SceneWipeOut(self);
    } else {
        LetterSend_ScrollOutboxLayer(self);
    }
}
CLEAN_AS(func_ov104_0229ed1c, LetterSend_OutboxWipeOut)

/* func_ov104_0229ed6c (state 4, set by LetterSend_Post and LetterSend_Cancel): the popup hidden
 * (its queue dropped) and the cursor sprite hidden; the parent told the scene ends (code 0x44)
 * unless a letter is to be shown (LETTER_SEND_FLAG_ACTION_1); the letters to post start to wipe
 * out on window 2 over 0xc0 pixels (state 5). */
void LetterSend_StartWipeOut(LetterSendScene *self)
{
    Popup_Hide(&self->popup, 1);
    LetterSend_HideCursorSprite(self);
    if (LetterSend_TestFlags(self, LETTER_SEND_FLAG_ACTION_1) == 0) {
        MenuDispatch_SetMode((MenuDispatch *) (void *) lsend_parent(self), LETTER_SEND_PARENT_CODE_END, 1);
    }
    MenuScene_StartWipeOnWindow2(lsend_scene(self), 2, 0, 2, LETTER_SEND_WIPE_MARGIN);
    MenuScene_SetWipeExtent(lsend_scene(self), 0xc0);
    MenuScene_SetState(lsend_scene(self), LETTER_SEND_STATE_OUTBOX_WIPE_OUT);
}
CLEAN_AS(func_ov104_0229ed6c, LetterSend_StartWipeOut)

/* func_ov104_0229edcc (state 3): the letters to post wipe in; when done, phase 2 and the action
 * ends. The page layer follows the wipe. */
void LetterSend_OutboxWipeIn(LetterSendScene *self)
{
    if (MenuScene_StepWipeBack(lsend_scene(self), 0) != 0) {
        MenuScene_SetPhase(lsend_scene(self), MENU_SCENE_PHASE_INTERACTIVE);
        LetterSend_EndAction(self);
    }
    LetterSend_ScrollOutboxLayer(self);
}
CLEAN_AS(func_ov104_0229edcc, LetterSend_OutboxWipeIn)

/* func_ov104_0229edf4 (state 2): the scene wipes in, its layer following; when done, the page
 * layer loaded and shown, the letters to post drawn and wiping in on window 2 over 0xc0 pixels
 * (state 3). */
void LetterSend_SceneWipeIn(LetterSendScene *self)
{
    int done = MenuScene_StepWipeBack(lsend_scene(self), 0);
    LetterSend_ScrollSceneLayer(self);
    if (done != 0) {
        LetterSend_LoadPageLayer(self);
        MenuScene_StartWipeCoveredOnWindow2(lsend_scene(self), 2, 0, 2, LETTER_SEND_WIPE_MARGIN);
        MenuScene_SetWipeExtent(lsend_scene(self), 0xc0);
        DisplayLayer_Show(LETTER_SEND_PAGE_LAYER);
        LetterSend_SetFlags(self, LETTER_SEND_FLAG_OUTBOX_SHOWN);
        LetterSend_ScrollOutboxLayer(self);
        MenuScene_SetState(lsend_scene(self), LETTER_SEND_STATE_OUTBOX_WIPE_IN);
    }
}
CLEAN_AS(func_ov104_0229edf4, LetterSend_SceneWipeIn)

/* func_ov104_0229ee54 (state 1): the panel prepared, the grid's and the letters' objects
 * prepared, the ten letters to post given to the letters object at its places 0x2d-0x36, the
 * letters that cannot be posted dimmed, the scene layer shown and wiping in on window 2 (state
 * 2); the scene and its objects drawn. */
void LetterSend_StartWipeIn(LetterSendScene *self)
{
    LetterSend_PreparePanel(self);
    PocketsGrid_LoadPockets(&self->grid);
    PocketsLetters_LoadPockets(&self->letters);
    PocketsLetters_SetTenAt2d(&self->letters, self->outbox);
    LetterSend_DimUnpostable(self);
    MenuScene_StartWipeCoveredOnWindow2(lsend_scene(self), 8, 0, 0, LETTER_SEND_WIPE_MARGIN);
    DisplayLayer_Show(LETTER_SEND_SCENE_LAYER);
    MenuScene_SetState(lsend_scene(self), LETTER_SEND_STATE_SCENE_WIPE_IN);
    LetterSend_SetFlags(self, LETTER_SEND_FLAG_SHOWN);
    LetterSend_SetFlags(self, LETTER_SEND_FLAG_SCROLLED);
    LetterSend_ScrollSceneLayer(self);
}
CLEAN_AS(func_ov104_0229ee54, LetterSend_StartWipeIn)

/* func_ov104_0229eec8 (state 0): the layers set up and the wallet's display prepared, then
 * state 1. */
void LetterSend_StartSetup(LetterSendScene *self)
{
    LetterSend_SetUpLayers();
    LetterSend_PrepareWallet(self);
    MenuScene_SetState(lsend_scene(self), LETTER_SEND_STATE_START_WIPE_IN);
}
CLEAN_AS(func_ov104_0229eec8, LetterSend_StartSetup)

/* func_ov104_0229eee4 (vtable slot 0x18): the scene's frame: the letters sent to the linked host
 * one at a time (LetterSend_ContinueLinkedPost), then the base's frame (MenuScene_Update), whose
 * answer it gives. */
int LetterSend_Update(LetterSendScene *self)
{
    LetterSend_ContinueLinkedPost(self);
    return MenuScene_Update(lsend_scene(self));
}
CLEAN_AS(func_ov104_0229eee4, LetterSend_Update)

/* func_ov104_0229eef8 (vtable slot 0x5c, phase 4): the scene's end, by how it ended. Answers 1.
 *
 * - Cancelled: the carried letters as they were (LetterSend_RestoreCarried), main told nothing
 *   changed (GroupParams_SetC4C(0)).
 * - Linked: while letters are still being sent nothing happens (and the scene is not deleted);
 *   after, main told whether anything was posted, the letters not taken back with the carried
 *   ones and `result` kept as the letter screen's result flags.
 * - Else the letters are posted here: main told the letters changed; the ten letters to post
 *   compacted (none: LETTER_SEND_RESULT_NOTHING), handed to the villagers when the current
 *   player's record has flag 1, then the one to the player themself taken and the rest posted.
 *   With nothing to post main is told nothing changed; when the post office was full, its held
 *   letters are delivered (Mail_DeliverHeld) and the letters tried once more, then delivered
 *   directly when still full. The letters not posted go back to the carried ones and the result
 *   is kept as the letter screen's result flags; when the letter screen's kind is 1 or its flag
 *   0x200 is set, VillagerPart_CurrentMarkSecondPick.
 *
 * Then (but for the linked wait) Mail_DoNothing and the scene asks to be deleted. */
int LetterSend_End(LetterSendScene *self)
{
    if (LetterSend_TestFlags(self, LETTER_SEND_FLAG_CANCELLED) != 0) {
        LetterSend_RestoreCarried(self);
        GroupParams_SetC4C(0);
    } else if (LetterSend_TestFlags(self, LETTER_SEND_FLAG_LINKED) != 0) {
        if (LetterSend_TestFlags(self, LETTER_SEND_FLAG_SENDING) != 0) {
            return 1;
        }
        if (self->result & LETTER_SEND_RESULT_NOTHING) {
            GroupParams_SetC4C(0);
        } else {
            GroupParams_SetC4C(1);
        }
        LetterSend_ReturnUnsent(self, 1);
        GroupParams_SetLetterFlags(self->result);
    } else {
        GroupParams_SetC4C(1);
        int result = 0;
        if (Mail_Compact(lsend_mail(self->outbox), LETTER_SEND_LETTERS) <= 0) {
            result = LETTER_SEND_RESULT_NOTHING;
        }
        if (PlayerRecord_TestFlag(PlayerRecords_Current(), 1) != 0) {
            result |= LetterSend_GiveToVillagers(self, self->outbox);
        }
        result |= LetterSend_TakeLetterToSelf(self, self->outbox);
        result |= LetterSend_PostAll(self, self->outbox, 0);
        if (result & LETTER_SEND_RESULT_NOTHING) {
            GroupParams_SetC4C(0);
        } else if (result & LETTER_SEND_RESULT_POST_OFFICE_FULL) {
            Mail_DeliverHeld();
            result |= LetterSend_RetryHold(self, self->outbox);
            if (result & LETTER_SEND_RESULT_STILL_FULL) {
                result |= LetterSend_DeliverDirectly(self, self->outbox);
            }
        }
        LetterSend_ReturnUnsent(self, 0);
        GroupParams_SetLetterFlags((u16) result);
        if (GroupParams_LetterKind() == 1 || GroupParams_LetterFlag200()) {
            VillagerPart_CurrentMarkSecondPick();
        }
    }
    Mail_DoNothing();
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov104_0229eef8, LetterSend_End)

/* func_ov104_0229f038 (vtable slot 0x58, phase 1): nothing. */
int LetterSend_Phase1Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov104_0229f038, LetterSend_Phase1Idle)

/* func_ov104_0229f03c (vtable slot 0x54, phase 0): nothing. */
int LetterSend_Phase0Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov104_0229f03c, LetterSend_Phase0Idle)

/* Obj_ov104_0229f6d0::func_ov104_0229f040 (vtable slot 0x50, phase 2): a frame of the scene in
 * use: the frame's start, its sub state and its end. Answers 1. */
int LetterSend_RunInteractive(LetterSendScene *self)
{
    LetterSend_BeginInteractiveFrame(self);
    LetterSend_RunSubState(self);
    LetterSend_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov104_0229f6d019func_ov104_0229f040Ev, LetterSend_RunInteractive)

/* Obj_ov104_0229f6d0::func_ov104_0229f05c: the sub state's function (LetterSendSubState)
 * through the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 0x1d; the game reads past the table for others. */
void LetterSend_RunSubState(LetterSendScene *self)
{
    static const MemberPointer *const sub_states[LETTER_SEND_SUB_STATES] = {
        &data_ov104_0229f5e0, &data_ov104_0229f658, &data_ov104_0229f650, &data_ov104_0229f648, &data_ov104_0229f640,
        &data_ov104_0229f638, &data_ov104_0229f630, &data_ov104_0229f628, &data_ov104_0229f620, &data_ov104_0229f618,
        &data_ov104_0229f610, &data_ov104_0229f608, &data_ov104_0229f600, &data_ov104_0229f5f8, &data_ov104_0229f5f0,
        &data_ov104_0229f670, &data_ov104_0229f5e8, &data_ov104_0229f5d8, &data_ov104_0229f5d0, &data_ov104_0229f5c8,
        &data_ov104_0229f5c0, &data_ov104_0229f5b8, &data_ov104_0229f5b0, &data_ov104_0229f5a0, &data_ov104_0229f5a8,
        &data_ov104_0229f598, &data_ov104_0229f590, &data_ov104_0229f588, &data_ov104_0229f660,
    };
    MemberTable_InitOnce(&data_ov104_0229f7a0, data_ov104_0229f800, sub_states, LETTER_SEND_SUB_STATES);
    MemberPointer_CallVoid(&data_ov104_0229f800[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov104_0229f6d019func_ov104_0229f05cEv, LetterSend_RunSubState)

/* func_ov104_0229f248 (vtable slot 0x4c, the run phase): a frame of the scene's states
 * (LetterSendState) between the frame's start and end, through the table of member functions
 * (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 0x0b; the game reads past the table for others. */
int LetterSend_RunState(LetterSendScene *self)
{
    static const MemberPointer *const states[LETTER_SEND_STATES] = {
        &data_ov104_0229f668, &data_ov104_0229f6c0, &data_ov104_0229f6b8, &data_ov104_0229f6b0,
        &data_ov104_0229f6a8, &data_ov104_0229f6a0, &data_ov104_0229f698, &data_ov104_0229f690,
        &data_ov104_0229f688, &data_ov104_0229f680, &data_ov104_0229f678,
    };
    MemberTable_InitOnce(&data_ov104_0229f7a4, data_ov104_0229f7a8, states, LETTER_SEND_STATES);
    LetterSend_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov104_0229f7a8[self->base.state], self);
    LetterSend_EndFrame(self);
    return 1;
}
CLEAN_AS(func_ov104_0229f248, LetterSend_RunState)

/* func_ov104_0229f33c (vtable slot 0x24): the scene's draw, while it is drawn: the popup
 * (through its class, slot 2), the cursor sprite (with the keys in use), the held letter. With
 * the objects drawn: the panel at the wipe's y, and the grid, the carried letters and the wallet
 * 16 pixels above it. With the page shown: the letters to post at the wipe's x. With a letter
 * shown: the label button at the wipe's y (through its class, slot 2). Answers 1. */
int LetterSend_Draw(LetterSendScene *self)
{
    if (LetterSend_TestFlags(self, LETTER_SEND_FLAG_SHOWN) == 0) {
        return 1;
    }
    lsend_draw_member(&self->popup);
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    LetterSend_DrawHeld(self);
    if (LetterSend_TestFlags(self, LETTER_SEND_FLAG_SCROLLED) != 0) {
        ButtonPanel_Draw(&self->panel, self->unk_98);
        int y = (int) ((u32) self->unk_98 - 0x10);
        PocketsGrid_DrawPockets(&self->grid, 0, y);
        PocketsLetters_DrawPockets(&self->letters, 0, y);
        PocketsWallet_Draw(&self->wallet, y);
    }
    if (LetterSend_TestFlags(self, LETTER_SEND_FLAG_OUTBOX_SHOWN) != 0) {
        PocketsLetters_DrawTenAt2d(&self->letters, self->unk_9c, -0x10);
    }
    if (LetterSend_TestFlags(self, LETTER_SEND_FLAG_LETTER_SHOWN) != 0) {
        int y = MenuScene_WipeOffsetY(lsend_scene(self));
        /* The button's base is main's labelled sprite (label_button.h). */
        LabelSprite_SetOffset((LabelSprite *) (void *) &self->button, 0, y);
        lsend_draw_member(&self->button);
    }
    return 1;
}
CLEAN_AS(func_ov104_0229f33c, LetterSend_Draw)

/* func_ov104_0229f424 (vtable slot 0x0c): the scene closes: the parent told and the members
 * torn down. Answers 1. */
int LetterSend_Close(LetterSendScene *self)
{
    MenuDispatch_ChildClosed((MenuDispatch *) (void *) lsend_parent(self));
    LetterSend_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov104_0229f424, LetterSend_Close)

/* func_ov104_0229f440 (vtable slot 0x00): the scene starts: its setup, state 0 and phase 0.
 * Answers 1. */
int LetterSend_Start(LetterSendScene *self)
{
    LetterSend_Setup(self);
    MenuScene_SetState(lsend_scene(self), LETTER_SEND_STATE_START_SETUP);
    MenuScene_SetPhase(lsend_scene(self), MENU_SCENE_PHASE_WAIT);
    return 1;
}
CLEAN_AS(func_ov104_0229f440, LetterSend_Start)

/* func_ov104_0229f460 (named by the profile at 0x0229f580): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order, the two arrays of ten letters by __cxa_vec_ctor. */
LetterSendScene *LetterSend_New(void)
{
    LetterSendScene *self = MenuScene_Alloc(sizeof(LetterSendScene));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov104_0229f6d0;
    Letter_Construct(&self->held);
    Letter_Construct(&self->swapped);
    LayerTask_ConstructPair((LayerTaskPair *) (void *) self->unk_2c0);
    PocketsGrid_Construct(&self->grid);
    PocketsLetters_Construct(&self->letters);
    PocketsWallet_Construct(&self->wallet);
    Popup_Construct(&self->popup);
    Glide_Construct(&self->glide);
    Glider0_Construct(&self->cursor_sprite);
    PagedChoice_Construct(lsend_choice(self));
    ErrorMessage_Construct(&self->error);
    LetterView_Construct(&self->view);
    LabelButton0_Construct(&self->button);
    __cxa_vec_ctor(self->outbox, LETTER_SEND_LETTERS, sizeof(Letter), func_02066694, func_02066688);
    __cxa_vec_ctor(self->carried_copy, LETTER_SEND_LETTERS, sizeof(Letter), func_02066694, func_02066688);
    ButtonPanel_Construct(&self->panel);
    return self;
}
CLEAN_AS(func_ov104_0229f460, LetterSend_New)
