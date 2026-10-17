/* The post office's letter posting scene of overlay 104 (letter_send.h): its destructors, its
 * flags, the posting of the letters (here or through the linked host), the cursor's moves, the
 * choices it opens, the held letter and its places. */
#include "letter_send.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/group_params.h"
#include "main/label_sprite.h"
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
#include "ov002/key_repeat.h"

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

/* The scene's place tests, its places' positions and letters, and the letters object's place of
 * a letter place. */
extern int func_ov104_0229da80(LetterSendScene *self, unsigned int place); /* a carried letter */
extern int func_ov104_0229da70(LetterSendScene *self, unsigned int place); /* a letter to post */
extern int func_ov104_0229da5c(LetterSendScene *self, int place);          /* a place below them */
extern unsigned char func_ov104_0229da38(LetterSendScene *self, unsigned int place);
extern int func_ov104_0229d8a8(LetterSendScene *self, int place);                        /* the place's x */
extern int func_ov104_0229d858(LetterSendScene *self, int place);                        /* the place's y */
extern Letter *func_ov104_0229d8f8(LetterSendScene *self, int place);                    /* its letter, NULL for none */
extern int func_ov104_0229d7bc(LetterSendScene *self, int place);                        /* whether it holds no letter */
extern void func_ov104_0229d938(LetterSendScene *self, int place, const Letter *letter); /* a copy put there */
extern void func_ov104_0229d798(LetterSendScene *self);                                  /* the lifts dropped */
extern int func_ov104_0229dad8(LetterSendScene *self); /* a free carried place, LETTER_SEND_NO_PLACE for none */
/* The cancel action. */
extern void func_ov104_0229dd00(LetterSendScene *self);

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

static MailLetter *lsend_mail(Letter *letter)
{
    return (MailLetter *) (void *) letter;
}

/* The place is a letter of the letters object: carried or to post. */
static int lsend_is_letter_place(LetterSendScene *self, int place)
{
    return func_ov104_0229da80(self, (unsigned int) place) != 0 || func_ov104_0229da70(self, (unsigned int) place) != 0;
}

static int lsend_letter_index(LetterSendScene *self, int place)
{
    return func_ov104_0229da38(self, (unsigned int) place);
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

/* func_ov104_0229c3dc (each frame, from the sub state func_ov104_0229eee4): while sending to the
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
            int place = func_ov104_0229dad8(self);
            if (place != LETTER_SEND_NO_PLACE) {
                func_ov104_0229d938(self, place, letter);
            }
        }
    }
}
CLEAN_AS(func_ov104_0229caa0, LetterSend_ReturnUnsent)

/* func_ov104_0229cb04: the carried letters put back as the scene began. */
void LetterSend_RestoreCarried(LetterSendScene *self)
{
    for (int i = 0; i < LETTER_SEND_LETTERS; i++) {
        func_ov104_0229d938(self, LETTER_SEND_CARRIED_FIRST + i, &self->carried_copy[i]);
    }
}
CLEAN_AS(func_ov104_0229cb04, LetterSend_RestoreCarried)

/* func_ov104_0229cb38: the carried letters copied aside. */
void LetterSend_SaveCarried(LetterSendScene *self)
{
    for (int i = 0; i < LETTER_SEND_LETTERS; i++) {
        Letter *letter = func_ov104_0229d8f8(self, LETTER_SEND_CARRIED_FIRST + i);
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
    self->held_x = func_ov104_0229d8a8(self, place);
    self->held_y = func_ov104_0229d858(self, place);
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
    if (func_ov104_0229da80(self, self->cursor) != 0) {
        LetterSend_MoveCursorInCarried(self, keys, mode);
    } else if (func_ov104_0229da70(self, self->cursor) != 0) {
        LetterSend_MoveCursorInOutbox(self, keys, mode);
    } else if (func_ov104_0229da5c(self, self->cursor) != 0) {
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

    if (func_ov104_0229da70(self, self->cursor) == 0 || LetterSend_TestFlags(self, LETTER_SEND_FLAGS_WRAPPED) != 0) {
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

    if (func_ov104_0229da80(self, self->cursor) == 0 || LetterSend_TestFlags(self, LETTER_SEND_FLAGS_WRAPPED) != 0) {
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
    Letter *letter = func_ov104_0229d8f8(self, place);
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
    int x = func_ov104_0229d8a8(self, self->slot);
    int y = func_ov104_0229d858(self, self->slot);
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
            func_ov104_0229dd00(self);
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
    return func_ov104_0229d858(self, self->cursor);
}
CLEAN_AS(func_ov104_0229d39c, LetterSend_CursorSpriteY)

/* func_ov104_0229d3ac: the cursor sprite's x, the cursor's place's plus 8; a screen width (256)
 * further right with LETTER_SEND_FLAG_WRAPPED_RIGHT, further left with
 * LETTER_SEND_FLAG_WRAPPED_LEFT. */
int LetterSend_CursorSpriteX(LetterSendScene *self)
{
    int x = func_ov104_0229d8a8(self, self->cursor);
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
    if (func_ov104_0229da5c(self, self->cursor) != 0) {
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
        func_ov104_0229d938(self, place, &self->swapped);
    }
}
CLEAN_AS(func_ov104_0229d448, LetterSend_SwapHeldWith)

/* func_ov104_0229d484: the held letter, if any, put at `place`; nothing held after. */
void LetterSend_PutHeldAt(LetterSendScene *self, int place)
{
    if (self->held_kind == LETTER_SEND_HELD_LETTER) {
        func_ov104_0229d938(self, place, &self->held);
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
        if (func_ov104_0229d7bc(self, self->cursor) != 0) {
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
    int x = func_ov104_0229d8a8(self, self->popup_place) - 0x6d;
    int y = func_ov104_0229d858(self, self->popup_place) - 0x78;
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
 * any other place drops both (func_ov104_0229d798). */
void LetterSend_SelectPlace(LetterSendScene *self, int place)
{
    if (lsend_is_letter_place(self, place)) {
        int index = lsend_letter_index(self, place);
        PocketsLetters_Lift(&self->letters, index);
        PocketsGrid_Unlift(&self->grid);
    } else {
        func_ov104_0229d798(self);
    }
}
CLEAN_AS(func_ov104_0229d748, LetterSend_SelectPlace)
