/* The panther: its talk's message and speaker (panther.h). */
#include "panther.h"

#include <stdint.h>

#include "autoload_2/heap.h" /* Heap_FreeAux, Heap_AllocAuxZeroed */
#include "clean.h"
#include "main/calendar.h"   /* DateTime */
#include "main/text_label.h" /* TextVtable */

static_assert(offsetof(Panther, receiver_vtable) == 0xec, "receiver");
static_assert(offsetof(Panther, message) == 0x10a, "receiver byte 0x1e");
static_assert(offsetof(Panther, hour) == 0x2b4, "hour");
static_assert(sizeof(Panther) == 0x2b8, "the size Panther_New allocates");

#define PANTHER_RECEIVER_OFFSET 0xec
#define PANTHER_HOUR_FROM 6
#define PANTHER_MESSAGE_EARLY 0xf
#define PANTHER_MESSAGE_LATE 0x12
/* A name code of main (func_02082438): 0xd in the top four bits takes entry `low twelve bits`
 * of main's list of names, here 10. */
#define PANTHER_NAME_CODE 0xd00a

/* "sp_npc_panther" */
extern const char data_ov003_02238ef8[];
/* The vtables: the class's and its receiver part's. */
extern const u8 data_ov003_02238dbc[];
extern const u8 data_ov003_02238e80[];

/* The clock's date and time (DateTime_Now). */
extern void func_0209e474(DateTime *now);
/* Copies at most 25 characters of `name` into the receiver's name. */
extern void func_020a8164(void *receiver, const char *name);
/* Sets the receiver's speaker name. */
extern void func_02066954(void *receiver, const char *name, int a);
/* A string object (0x24 bytes): built by func_02094fd4, destroyed by func_02094fbc;
 * func_02082438 loads the name of `*code` into it (whether it could). */
extern void *func_02094fd4(void *text);
extern void *func_02094fbc(void *text);
extern int func_02082438(void *text, u16 *code);
/* Overlay 9's scene actor: its destructor and its constructor. */
extern void *func_ov009_0226539c(Panther *panther);
extern void *func_ov009_0226552c(Panther *panther);

typedef struct PantherText {
    const TextVtable *vtable;
    u8 unk_04[0x24 - 0x04];
} PantherText;

/* func_ov003_0221d10c (vtable slot 0x78, before a talk): names the receiver "sp_npc_panther",
 * picks PANTHER_MESSAGE_LATE when vtable slot 0x8c (Panther_IsAfterSix) agrees, else
 * PANTHER_MESSAGE_EARLY, and sets the speaker to the name PANTHER_NAME_CODE gives (the string
 * object's vtable slot 0x0c gives its characters). */
void Panther_PrepareTalk(Panther *panther)
{
    typedef int (*PantherSlot)(Panther *panther);
    typedef const char *(*PantherTextBuffer)(void *text);

    func_020a8164(&panther->receiver_vtable, data_ov003_02238ef8);
    PantherSlot after_six = (PantherSlot) (uintptr_t) *(const u32 *) ((const u8 *) panther->vtable + 0x8c);
    if (after_six(panther) == 0) {
        panther->message = PANTHER_MESSAGE_EARLY;
    } else {
        panther->message = PANTHER_MESSAGE_LATE;
    }

    PantherText text;
    func_02094fd4(&text);
    u16 code = PANTHER_NAME_CODE;
    func_02082438(&text, &code);
    const char *name = ((PantherTextBuffer) (uintptr_t) text.vtable->buffer)(&text);
    func_02066954(&panther->receiver_vtable, name, 1);
    func_02094fbc(&text);
}
CLEAN_AS(func_ov003_0221d10c, Panther_PrepareTalk)

/* func_ov003_0221d17c (vtable slot 0x8c): whether both the clock's hour now and the hour
 * Panther_KeepHour kept are 6 or later. */
int Panther_IsAfterSix(Panther *panther)
{
    DateTime now = {0};
    func_0209e474(&now);
    return now.hour >= PANTHER_HOUR_FROM && panther->hour >= PANTHER_HOUR_FROM;
}
CLEAN_AS(func_ov003_0221d17c, Panther_IsAfterSix)

/* func_ov003_0221d1b4 (vtable slot 0x18, its update): always 1. */
int Panther_Update(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0221d1b4, Panther_Update)

/* func_ov003_0221d1b8 (vtable slot 0x70, setting it up): keeps the clock's hour now; always
 * 1. */
int Panther_KeepHour(Panther *panther)
{
    DateTime now = {0};
    func_0209e474(&now);
    panther->hour = now.hour;
    return 1;
}
CLEAN_AS(func_ov003_0221d1b8, Panther_KeepHour)

/* The vtables set back, then overlay 9's destructor. */
static void panther_destroy_parts(Panther *panther)
{
    panther->vtable = data_ov003_02238dbc;
    panther->receiver_vtable = data_ov003_02238e80;
    func_ov009_0226539c(panther);
}

/* func_ov003_0221d1e0 (vtable slot 0x44, the deleting destructor): the destructor's work, then
 * the memory freed. */
Panther *Panther_DestroyAndFree(Panther *panther)
{
    panther_destroy_parts(panther);
    Heap_FreeAux(panther);
    return panther;
}
CLEAN_AS(func_ov003_0221d1e0, Panther_DestroyAndFree)

/* func_ov003_0221d20c (vtable slot 0x40): the destructor, without freeing. */
Panther *Panther_Destroy(Panther *panther)
{
    panther_destroy_parts(panther);
    return panther;
}
CLEAN_AS(func_ov003_0221d20c, Panther_Destroy)

/* func_ov003_0221d230: the constructor: overlay 9's, then the vtables. */
Panther *Panther_Construct(Panther *panther)
{
    func_ov009_0226552c(panther);
    panther->vtable = data_ov003_02238dbc;
    panther->receiver_vtable = data_ov003_02238e80;
    return panther;
}
CLEAN_AS(func_ov003_0221d230, Panther_Construct)

/* func_ov003_0221d254 (the class's entry in the overlay's table of profiles): allocates and
 * constructs one; nothing keeps the pointer here. */
void Panther_New(void)
{
    Panther *panther = Heap_AllocAuxZeroed(sizeof(Panther));
    if (panther != NULL) {
        Panther_Construct(panther);
    }
}
CLEAN_AS(func_ov003_0221d254, Panther_New)

/* The panther around its receiver part, as the receiver vtable's thunks find it. */
static Panther *panther_from_receiver(void *receiver)
{
    return (Panther *) (void *) ((u8 *) receiver - PANTHER_RECEIVER_OFFSET);
}

/* _ZThn236_N18Obj_ov003_02238dbcD0Ev (receiver slot 0x04): Panther_DestroyAndFree. */
Panther *Panther_ReceiverDestroyAndFree(void *receiver)
{
    return Panther_DestroyAndFree(panther_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02238dbcD0Ev, Panther_ReceiverDestroyAndFree)

/* _ZThn236_N18Obj_ov003_02238dbcD1Ev (receiver slot 0x00): Panther_Destroy. */
Panther *Panther_ReceiverDestroy(void *receiver)
{
    return Panther_Destroy(panther_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02238dbcD1Ev, Panther_ReceiverDestroy)
