/* The town's mail (mail.h). */
#include "mail.h"

#include "actor_table.h"
#include "autoload_2/heap.h"
#include "clean.h"
#include "date_time.h"
#include "npc_id.h"
#include "session.h"

/* The delivery hours. */
#define MORNING_HOUR 9
#define EVENING_HOUR 17

/* The fields DateTime_Compare looks at here: the date, and the date with the hour. */
#define DATE_FIELDS (DATE_TIME_YEAR | DATE_TIME_MONTH | DATE_TIME_DAY)
#define HOUR_FIELDS (DATE_FIELDS | DATE_TIME_HOUR)

/* What a dated letter's date is reset to once it is posted: 1/1/00. */
#define DATED_RESET_DAY 1
#define DATED_RESET_MONTH 1

/* A player's id as func_0209529c constructs it (0x20 bytes). */
typedef struct MailPlayerId {
    u8 bytes[0x20];
} MailPlayerId;

extern MailBox data_021ef8ec[MAIL_PLAYERS]; /* the players' mailboxes */
extern MailPostOffice data_021f20fc;        /* the letters at the post office */
extern MailLetter data_021f37f4;            /* a letter waiting for the current player */
extern u8 data_021dc7bc[];                  /* the four players' records (0x249c bytes each) */
extern u8 data_021e5a2c[];                  /* the villagers (0x7ec bytes each) */
extern NetSession *data_020ccf94;           /* the session */
extern const u8 data_020da13c[];            /* the base class's vtable */
extern const u8 data_020e30b8[];            /* MailTask's */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
/* The letter's state (byte 0xfa, low six bits); 0: no letter. */
extern u8 func_02065ec0(const MailLetter *letter);
extern void func_02066650(MailLetter *letter);                       /* empty it */
extern int func_02066830(MailLetter *dst, const MailLetter *src);    /* copy it */
extern void func_020664e0(MailLetter *letter);                       /* move its state on (1 to 2, 4 to 5) */
extern void *func_02065f64(const MailLetter *letter);                /* its villager addressee, or NULL */
extern void *func_02065f70(const MailLetter *letter);                /* its player addressee, or NULL */
extern void func_02066560(MailLetter *letter, int player);           /* address it to a player of the town */
extern void func_02066478(MailLetter *letter);                       /* mark it as delivered */
extern MailLetter *func_02097ff0(MailPostOffice *office, int index); /* NULL past 9 */
extern MailLetter *func_02098090(MailBox *box, int index);           /* NULL past 9 */
extern MailTime *func_02097f98(MailPostOffice *office);              /* its last_check */
extern int func_02097f70(MailPostOffice *office, u32 flags);         /* any of its flags set */
extern void func_02097f88(MailPostOffice *office, u16 flags);        /* set its flags */
/* The letter waiting at data_021f37f4: whether there is one, it, and empty it. */
extern int func_02090000(MailLetter *letter);
extern MailLetter *func_0208ffe4(MailLetter *letter);
extern void func_02090018(MailLetter *letter);
extern void *func_020984e8(void);                    /* the current player's record */
extern int func_0209985c(void *player);              /* its number in the town (0-3) */
extern int func_020988a4(u8 *players, int player);   /* whether there is such a player */
extern void *func_02098844(u8 *players, int player); /* a player's record; NULL past 3 */
extern u8 *func_02098a18(void *player);              /* its dated letter (0x100 bytes) */
extern MailLetter *func_02097e14(u8 *dated);         /* the letter */
extern MailTime *func_02097e08(u8 *dated);           /* its date, after it */
extern void func_02097dd4(u8 *dated);                /* empty it, date 1/1/00 */
extern void *func_0209529c(MailPlayerId *id);        /* construct */
extern void func_02095208(MailPlayerId *id, void *addressee);
extern int func_0209871c(u8 *players, MailPlayerId *id); /* the player of the town it names */
extern int func_020988d8(u32 player);                    /* 1 for 0-3 */
extern int func_0209526c(MailPlayerId *id);              /* destruct */
extern int func_0207cf14(u8 *villagers, NpcId *npc);     /* the villager it names */
extern int func_0207a51c(u8 *villagers, MailLetter *letter);
extern int func_020b65d0(void);

static MailLetter *letter_at(MailLetter *letters, int index)
{
    return (MailLetter *) ((u8 *) letters + index * MAIL_LETTER_SIZE);
}

/* func_020975c4: the letter waiting at data_021f37f4 goes to the current player, addressed and
 * marked delivered, when the player's mailbox has room; then it is emptied. */
void Mail_DeliverWaiting(void)
{
    if (func_02090000(&data_021f37f4) == 0) {
        return;
    }
    if (Mail_IsMailboxFull(-1) != 0) {
        return;
    }
    MailLetter *letter = func_0208ffe4(&data_021f37f4);
    int player = func_0209985c(func_020984e8());
    func_02066560(letter, player);
    func_02066478(letter);
    if (Mail_PutInMailbox(letter, player, 0) == 0) {
        return;
    }
    func_02090018(&data_021f37f4);
}
CLEAN_AS(func_020975c4, Mail_DeliverWaiting)

/* func_020976a4: unless the console is linked to others, deliver the post office's letters for
 * each delivery hour (9:00 and 17:00) that has come since the last check, at most two; then post
 * each player's dated letter whose date has come (from 9:00 on). The first time only notes the
 * time. QUIRK: the hour of last_check holds the next delivery hour until it is set to now's. */
void Mail_DeliverDue(void)
{
    if (Session_IsLinked(data_020ccf94)) {
        return;
    }
    MailPostOffice *office = &data_021f20fc;
    MailTime *last = func_02097f98(office);
    DateTime now = {0};
    DateTime_Now(&now);
    DateTime next = {0};
    DateTime after = {0};
    if (func_02097f70(office, MAIL_CHECKED) != 0) {
        next = (DateTime){0};
        next.year = last->year;
        next.month = last->month;
        next.day = last->day;
        MI_CpuCopy8(&next, &after, sizeof(DateTime));
        if (last->hour < MORNING_HOUR) {
            last->hour = MORNING_HOUR;
            after.hour = EVENING_HOUR;
        } else if (last->hour < EVENING_HOUR) {
            last->hour = EVENING_HOUR;
            after.hour = MORNING_HOUR;
            DateTime_AddDays(&after, 1);
        } else {
            last->hour = MORNING_HOUR;
            DateTime_AddDays(&next, 1);
            after.hour = EVENING_HOUR;
            DateTime_AddDays(&after, 1);
        }
        next.hour = last->hour;
        if (DateTime_Compare(&now, &next, HOUR_FIELDS) != -1) {
            Mail_DeliverHeld();
            if (DateTime_Compare(&now, &after, HOUR_FIELDS) != -1) {
                Mail_DeliverHeld();
            }
        }
    } else {
        func_02097f88(office, MAIL_CHECKED);
    }

    for (int i = 0; i < MAIL_PLAYERS; i++) {
        if (func_020988a4(data_021dc7bc, i) == 0) {
            continue;
        }
        void *player = func_02098844(data_021dc7bc, i);
        MailTime *date = func_02097e08(func_02098a18(player));
        MailLetter *letter = func_02097e14(func_02098a18(player));
        if (func_02065ec0(letter) == 0) {
            continue;
        }
        next = (DateTime){0};
        next.year = date->year;
        next.month = date->month;
        next.day = date->day;
        next.hour = MORNING_HOUR;
        if (DateTime_Compare(&now, &next, HOUR_FIELDS) == -1) {
            continue;
        }
        if (Mail_PutInMailbox(letter, i, 0) == 0) {
            continue;
        }
        func_02097dd4(func_02098a18(player));
    }

    last->year = now.year;
    last->month = now.month;
    last->day = now.day;
    last->hour = now.hour;
}
CLEAN_AS(func_020976a4, Mail_DeliverDue)

/* func_0209782c: whether the post office has an empty place. */
int Mail_PostOfficeHasRoom(void)
{
    MailLetter *letter = func_02097ff0(&data_021f20fc, 0);
    for (int i = 0; i < MAILBOX_LETTERS; i++) {
        if (func_02065ec0(letter) == 0) {
            return 1;
        }
        letter = letter_at(letter, 1);
    }
    return 0;
}
CLEAN_AS(func_0209782c, Mail_PostOfficeHasRoom)

/* func_02097864: whether a player's record (NULL: the current player's) keeps a dated letter. */
int Mail_HasDatedLetter(void *player)
{
    if (player == NULL) {
        player = func_020984e8();
    }
    return func_02065ec0(func_02097e14(func_02098a18(player))) != 0;
}
CLEAN_AS(func_02097864, Mail_HasDatedLetter)

/* func_0209788c */
void Mail_DoNothing(void) {}
CLEAN_AS(func_0209788c, Mail_DoNothing)

/* func_02097890: how many of `count` letters are there. */
int Mail_CountLetters(MailLetter *letters, int count)
{
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (func_02065ec0(letter_at(letters, i)) != 0) {
            found++;
        }
    }
    return found;
}
CLEAN_AS(func_02097890, Mail_CountLetters)

/* func_020978bc: move the letters among `count` to the front, in order, emptying the places
 * they leave; how many there are. */
int Mail_Compact(MailLetter *letters, int count)
{
    int kept = 0;
    for (int i = 0; i < count; i++) {
        MailLetter *letter = letter_at(letters, i);
        if (func_02065ec0(letter) == 0) {
            continue;
        }
        if (i != kept) {
            func_02066830(letter_at(letters, kept), letter);
            func_02066650(letter);
        }
        kept++;
    }
    return kept;
}
CLEAN_AS(func_020978bc, Mail_Compact)

/* func_02097900: the number (0-7) of the town's villager the letter is addressed to, or
 * MAIL_NOT_THAT_KIND / MAIL_NOT_HERE. */
int Mail_FindVillagerAddressee(MailLetter *letter)
{
    void *addressee = func_02065f64(letter);
    if (addressee == NULL) {
        return MAIL_NOT_THAT_KIND;
    }
    NpcId npc;
    NpcId_Construct(&npc);
    NpcId_Assign(&npc, addressee);
    int villager = func_0207cf14(data_021e5a2c, &npc);
    int found = ActorTable_IsKindESlot((u32) villager);
    NpcId_Destruct(&npc);
    return found ? villager : MAIL_NOT_HERE;
}
CLEAN_AS(func_02097900, Mail_FindVillagerAddressee)

/* func_02097958: the number (0-3) of the town's player the letter is addressed to, or
 * MAIL_NOT_THAT_KIND / MAIL_NOT_HERE. */
int Mail_FindPlayerAddressee(MailLetter *letter)
{
    void *addressee = func_02065f70(letter);
    if (addressee == NULL) {
        return MAIL_NOT_THAT_KIND;
    }
    MailPlayerId id;
    func_0209529c(&id);
    func_02095208(&id, addressee);
    int player = func_0209871c(data_021dc7bc, &id);
    int found = func_020988d8((u32) player);
    func_0209526c(&id);
    return found ? player : MAIL_NOT_HERE;
}
CLEAN_AS(func_02097958, Mail_FindPlayerAddressee)

/* func_020979ac: whether the letter is addressed to a player or a villager of this town. */
int Mail_HasAddressee(MailLetter *letter)
{
    int player = Mail_FindPlayerAddressee(letter);
    if (player == MAIL_NOT_HERE) {
        return 0;
    }
    if (player == MAIL_NOT_THAT_KIND) {
        int villager = Mail_FindVillagerAddressee(letter);
        if (villager == MAIL_NOT_HERE || villager == MAIL_NOT_THAT_KIND) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_020979ac, Mail_HasAddressee)

/* func_020979f0: a copy of the letter in the post office's first empty place, its state moved
 * on when `advance`; 0 when there is no room. */
int Mail_HoldAtPostOffice(MailLetter *letter, int advance)
{
    MailLetter *place = func_02097ff0(&data_021f20fc, 0);
    for (int i = 0; i < MAILBOX_LETTERS; i++, place++) {
        if (func_02065ec0(place) != 0) {
            continue;
        }
        func_02066830(place, letter);
        if (advance != 0) {
            func_020664e0(place);
        }
        return 1;
    }
    return 0;
}
CLEAN_AS(func_020979f0, Mail_HoldAtPostOffice)

/* func_02097a44: the letter goes to the villager it is addressed to (func_0207a51c). */
void Mail_GiveToVillager(MailLetter *letter)
{
    func_0207a51c(data_021e5a2c, letter);
}
CLEAN_AS(func_02097a44, Mail_GiveToVillager)

/* func_02097a54: a copy of the letter in the mailbox of the town's player it is addressed to;
 * 0 when it is for no player here or the mailbox is full. */
int Mail_Post(MailLetter *letter)
{
    int player = Mail_FindPlayerAddressee(letter);
    if (player < 0) {
        return 0;
    }
    return Mail_PutInMailbox(letter, player, 0);
}
CLEAN_AS(func_02097a54, Mail_Post)

/* func_02097a74: a copy of the letter in the first empty place of player `player`'s mailbox,
 * its state moved on when `advance`; 0 when the mailbox is full. REQUIRES: `player` is 0-3. */
int Mail_PutInMailbox(MailLetter *letter, int player, int advance)
{
    MailLetter *place = func_02098090(&data_021ef8ec[player], 0);
    for (int i = 0; i < MAILBOX_LETTERS; i++) {
        if (func_02065ec0(place) == 0) {
            func_02066830(place, letter);
            if (advance != 0) {
                func_020664e0(place);
            }
            return 1;
        }
        place = letter_at(place, 1);
    }
    return 0;
}
CLEAN_AS(func_02097a74, Mail_PutInMailbox)

/* func_02097ad0: whether player `player`'s mailbox (-1: the current player's) is full.
 * REQUIRES: `player` is -1 or 0-3. */
int Mail_IsMailboxFull(int player)
{
    if (player == -1) {
        player = func_0209985c(func_020984e8());
    }
    MailLetter *place = func_02098090(&data_021ef8ec[player], 0);
    for (int i = 0; i < MAILBOX_LETTERS; i++) {
        if (func_02065ec0(place) == 0) {
            return 0;
        }
        place = letter_at(place, 1);
    }
    return 1;
}
CLEAN_AS(func_02097ad0, Mail_IsMailboxFull)

/* func_02097b24: hand out the post office's letters: to a player of the town into the mailbox
 * (a letter stays when the mailbox is full), to a villager of the town; a letter for anyone
 * else is thrown away. The letters left are moved to the front; how many there are. */
int Mail_DeliverHeld(void)
{
    MailLetter *letters = func_02097ff0(&data_021f20fc, 0);
    int count = Mail_Compact(letters, MAILBOX_LETTERS);
    for (int i = 0; i < count; i++) {
        MailLetter *letter = letter_at(letters, i);
        if (func_02065ec0(letter) == 0) {
            continue;
        }
        int player = Mail_FindPlayerAddressee(letter);
        if (player == MAIL_NOT_HERE) {
            func_02066650(letter);
        } else if (player == MAIL_NOT_THAT_KIND) {
            if (Mail_FindVillagerAddressee(letter) < 0) {
                func_02066650(letter);
            } else {
                Mail_GiveToVillager(letter);
                func_02066650(letter);
            }
        } else if (Mail_PutInMailbox(letter, player, 0) != 0) {
            func_02066650(letter);
        }
    }
    return Mail_Compact(letters, MAILBOX_LETTERS);
}
CLEAN_AS(func_02097b24, Mail_DeliverHeld)

/* ---- The delivery process ---- */

/* func_02097bbc: the destructor. Returns the task. */
MailTask *MailTask_Destruct(MailTask *task)
{
    task->base.vtable = (const u32 *) data_020e30b8;
    task->base.vtable = (const u32 *) data_020da13c;
    Process_Destruct(&task->base);
    return task;
}
CLEAN_AS(func_02097bbc, MailTask_Destruct)

/* func_02097bdc: the deleting destructor. Returns the freed task. */
MailTask *MailTask_DestructFree(MailTask *task)
{
    task->base.vtable = (const u32 *) data_020e30b8;
    task->base.vtable = (const u32 *) data_020da13c;
    Process_Destruct(&task->base);
    Heap_FreeAux(task);
    return task;
}
CLEAN_AS(func_02097bdc, MailTask_DestructFree)

/* func_02097c04 */
void MailTask_ClearFlags(MailTask *task, u16 flags)
{
    task->flags &= (u16) ~flags;
}
CLEAN_AS(func_02097c04, MailTask_ClearFlags)

/* func_02097c14 */
void MailTask_SetFlags(MailTask *task, u32 flags)
{
    task->flags |= (u16) flags;
}
CLEAN_AS(func_02097c14, MailTask_SetFlags)

/* func_02097c24: whether any of `flags` is set. */
int MailTask_TestFlags(MailTask *task, u32 flags)
{
    return (task->flags & flags) != 0;
}
CLEAN_AS(func_02097c24, MailTask_TestFlags)

/* func_02097c38 */
void MailTask_Deliver(MailTask *task)
{
    (void) task;
    Mail_DeliverDue();
}
CLEAN_AS(func_02097c38, MailTask_Deliver)

/* func_02097c40: the delete phase's work (vtable slot 3): done at once. */
int MailTask_Delete(void)
{
    return 1;
}
CLEAN_AS(func_02097c40, MailTask_Delete)

/* func_02097c44: the draw phase's work (vtable slot 9): nothing to draw. */
int MailTask_Draw(void)
{
    return 1;
}
CLEAN_AS(func_02097c44, MailTask_Draw)

/* func_02097c48: the execute phase's work (vtable slot 6): the first time, deliver the mail when
 * func_020b65d0 allows, and not again. */
int MailTask_Execute(MailTask *task)
{
    if (MailTask_TestFlags(task, MAIL_TASK_PENDING)) {
        if (func_020b65d0() != 0) {
            MailTask_Deliver(task);
        }
        MailTask_ClearFlags(task, MAIL_TASK_PENDING);
    }
    return 1;
}
CLEAN_AS(func_02097c48, MailTask_Execute)

/* func_02097c74: the create phase's work (vtable slot 0): the delivery is pending. */
int MailTask_Create(MailTask *task)
{
    task->flags = 0;
    MailTask_SetFlags(task, MAIL_TASK_PENDING);
    return 1;
}
CLEAN_AS(func_02097c74, MailTask_Create)

/* func_02097c90: a new task, constructed (its profile's create function); NULL when there is no
 * memory for it. The vtable is the base class's while its constructor runs, then this class's. */
MailTask *MailTask_New(void)
{
    MailTask *task = Heap_AllocAuxZeroed(sizeof(MailTask));
    if (task != NULL) {
        Process_Construct(&task->base);
        task->base.vtable = (const u32 *) data_020da13c;
        task->base.vtable = (const u32 *) data_020e30b8;
    }
    return task;
}
CLEAN_AS(func_02097c90, MailTask_New)

static_assert(sizeof(MailLetter) == 0x100, "MailLetter layout");
static_assert(sizeof(MailBox) == 0xa04, "MailBox layout");
static_assert(offsetof(MailPostOffice, last_check) == 0xa00, "MailPostOffice layout");
static_assert(offsetof(MailPostOffice, flags) == 0xa04, "MailPostOffice layout");
static_assert(offsetof(MailTask, flags) == 0x50, "MailTask layout");
static_assert(sizeof(MailTask) == 0x54, "MailTask layout");

/* ---- The letter a player's record keeps for a date, the post office and the mailboxes ---- */

/* A letter's constructor and destructor; handed to the game's array helpers, so the game's
 * symbols. */
extern void func_02066694(void *letter);
extern void func_02066688(void *letter);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* func_02097dd4: empty the letter, its date 1/1/00 at 0:00. */
void MailDated_Init(MailDatedLetter *dated)
{
    func_02066650(&dated->letter);
    dated->date.day = DATED_RESET_DAY;
    dated->date.month = DATED_RESET_MONTH;
    dated->date.year = 0;
    dated->date.hour = 0;
}
CLEAN_AS(func_02097dd4, MailDated_Init)

/* func_02097e08 */
MailTime *MailDated_Date(MailDatedLetter *dated)
{
    return &dated->date;
}
CLEAN_AS(func_02097e08, MailDated_Date)

/* func_02097e14 */
MailLetter *MailDated_Letter(MailDatedLetter *dated)
{
    return &dated->letter;
}
CLEAN_AS(func_02097e14, MailDated_Letter)

/* func_02097e18: the destructor. */
MailDatedLetter *MailDated_Destruct(MailDatedLetter *dated)
{
    func_02066688(&dated->letter);
    return dated;
}
CLEAN_AS(func_02097e18, MailDated_Destruct)

/* func_02097e28: the constructor. */
MailDatedLetter *MailDated_Construct(MailDatedLetter *dated)
{
    func_02066694(&dated->letter);
    return dated;
}
CLEAN_AS(func_02097e28, MailDated_Construct)

/* func_02097f70: whether any of `flags` is set. */
int MailPostOffice_TestFlags(MailPostOffice *office, u32 flags)
{
    return (office->flags & flags) != 0;
}
CLEAN_AS(func_02097f70, MailPostOffice_TestFlags)

/* func_02097f88 */
void MailPostOffice_SetFlags(MailPostOffice *office, u16 flags)
{
    office->flags |= flags;
}
CLEAN_AS(func_02097f88, MailPostOffice_SetFlags)

/* func_02097f98 */
MailTime *MailPostOffice_LastCheck(MailPostOffice *office)
{
    return &office->last_check;
}
CLEAN_AS(func_02097f98, MailPostOffice_LastCheck)

/* func_02097fa4: empty every letter, no flag, the last check 1/1/00 at 0:00. */
void MailPostOffice_Init(MailPostOffice *office)
{
    for (int i = 0; i < MAILBOX_LETTERS; i++) {
        func_02066650(letter_at(office->letters, i));
    }
    office->flags = 0;
    office->last_check.day = DATED_RESET_DAY;
    office->last_check.month = DATED_RESET_MONTH;
    office->last_check.year = 0;
    office->last_check.hour = 0;
}
CLEAN_AS(func_02097fa4, MailPostOffice_Init)

/* func_02097ff0: letter `index`; NULL outside 0-9. */
MailLetter *MailPostOffice_Letter(MailPostOffice *office, int index)
{
    if (index >= 0 && index < MAILBOX_LETTERS) {
        return letter_at(office->letters, index);
    }
    return NULL;
}
CLEAN_AS(func_02097ff0, MailPostOffice_Letter)

/* func_02098004: the destructor. */
MailPostOffice *MailPostOffice_Destruct(MailPostOffice *office)
{
    __cxa_vec_cleanup(office->letters, MAILBOX_LETTERS, MAIL_LETTER_SIZE, func_02066688);
    return office;
}
CLEAN_AS(func_02098004, MailPostOffice_Destruct)

/* func_02098024: the constructor. */
MailPostOffice *MailPostOffice_Construct(MailPostOffice *office)
{
    __cxa_vec_ctor(office->letters, MAILBOX_LETTERS, MAIL_LETTER_SIZE, func_02066694, func_02066688);
    return office;
}
CLEAN_AS(func_02098024, MailPostOffice_Construct)

static u16 *mailbox_mark(MailBox *box)
{
    return (u16 *) (void *) box->unk_a00;
}

/* func_02098050: the mark of the last letter put in from elsewhere (func_0203f5e4 compares a
 * letter's mark with it, so the same letter is not put in twice). QUIRK: kept in 16 bits. */
void MailBox_SetMark(MailBox *box, u32 mark)
{
    *mailbox_mark(box) = (u16) mark;
}
CLEAN_AS(func_02098050, MailBox_SetMark)

/* func_0209805c */
u16 MailBox_Mark(MailBox *box)
{
    return *mailbox_mark(box);
}
CLEAN_AS(func_0209805c, MailBox_Mark)

/* func_02098068: empty every letter, no mark. */
void MailBox_Init(MailBox *box)
{
    for (int i = 0; i < MAILBOX_LETTERS; i++) {
        func_02066650(letter_at(box->letters, i));
    }
    *mailbox_mark(box) = 0;
}
CLEAN_AS(func_02098068, MailBox_Init)

/* func_02098090: letter `index`; NULL outside 0-9. */
MailLetter *MailBox_Letter(MailBox *box, int index)
{
    if (index >= 0 && index < MAILBOX_LETTERS) {
        return letter_at(box->letters, index);
    }
    return NULL;
}
CLEAN_AS(func_02098090, MailBox_Letter)

/* func_020980a4: the destructor. */
MailBox *MailBox_Destruct(MailBox *box)
{
    __cxa_vec_cleanup(box->letters, MAILBOX_LETTERS, MAIL_LETTER_SIZE, func_02066688);
    return box;
}
CLEAN_AS(func_020980a4, MailBox_Destruct)

/* func_020980c4: the constructor. */
MailBox *MailBox_Construct(MailBox *box)
{
    __cxa_vec_ctor(box->letters, MAILBOX_LETTERS, MAIL_LETTER_SIZE, func_02066694, func_02066688);
    return box;
}
CLEAN_AS(func_020980c4, MailBox_Construct)

static_assert(offsetof(MailDatedLetter, date) == 0x100, "MailDatedLetter layout");
