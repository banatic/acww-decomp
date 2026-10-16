/* The kinds of the acre models (acre_kind.h). */
#include "acre_kind.h"

#include "autoload_2/heap.h"
#include "clean.h"

/* The flags counted by AcreKind_CountFlags1000: seven bits from 0x1000. */
#define ACRE_KIND_FLAGS_1000 0x7f000
#define ACRE_KIND_FLAG_FIRST_BIT 12
#define ACRE_KIND_FLAG_BITS 7

/* Each kind's flags. */
extern const s32 data_020ca008[ACRE_KINDS];
/* The kind of each model number ("/bg/bkattr.bin"), and its size in bytes. */
extern u8 *data_021c590c;
extern u32 data_021c5910;
/* The current heap. */
extern Heap *data_021fbe94;
/* "/bg/bkattr.bin". */
extern const char data_020da4b4[];

/* A file read whole into `heap` (from its start when `align` is positive); its size into *size. */
extern u8 *func_02064b2c(const char *path, Heap *heap, int align, u32 *size);

/* func_02037b14: how many of the flags 0x1000-0x40000 kind `kind` has. */
u32 AcreKind_CountFlags1000(int kind)
{
    u32 flags = (u32) AcreKind_Flags(kind);
    u8 count = 0;

    if ((flags & ACRE_KIND_FLAGS_1000) == 0) {
        return 0;
    }
    for (int bit = 0; bit < ACRE_KIND_FLAG_BITS; bit++) {
        if (flags & (1u << (ACRE_KIND_FLAG_FIRST_BIT + bit))) {
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_02037b14, AcreKind_CountFlags1000)

/* func_02037bc4: the flags of kind `kind`; 0 from ACRE_KINDS on.
 * QUIRK: a negative kind is not refused: the word that far before the table is read, which is
 * why the address is computed by hand here. */
int AcreKind_Flags(int kind)
{
    if (kind >= ACRE_KINDS) {
        return 0;
    }
    return *(const s32 *) ((uintptr_t) data_020ca008 + (uintptr_t) kind * sizeof(s32));
}
CLEAN_AS(func_02037bc4, AcreKind_Flags)

/* func_02037bd8: the flags of model `model`'s kind. */
int AcreKind_ModelFlags(unsigned int model)
{
    return AcreKind_Flags(AcreKind_OfModel(model));
}
CLEAN_AS(func_02037bd8, AcreKind_ModelFlags)

/* func_02037bec: the first kind whose flags are exactly `flags`; ACRE_KIND_LAST when none is.
 * The flags 0 give kind 9, the first without any. */
int AcreKind_Find(int flags)
{
    for (int kind = 0; kind < ACRE_KINDS; kind++) {
        if (data_020ca008[kind] == flags) {
            return kind;
        }
    }
    return ACRE_KIND_LAST;
}
CLEAN_AS(func_02037bec, AcreKind_Find)

/* func_02037c0c: the kind of model `model`; 0 past the end of the file. */
u8 AcreKind_OfModel(unsigned int model)
{
    if (model < data_021c5910) {
        return data_021c590c[model];
    }
    return 0;
}
CLEAN_AS(func_02037c0c, AcreKind_OfModel)

/* func_02037c28: the file freed; 1.
 * QUIRK: its size is left as it was, so AcreKind_OfModel would read the freed block. */
int AcreKind_Free(void)
{
    Heap_FreeCurrent(data_021c590c);
    data_021c590c = NULL;
    return 1;
}
CLEAN_AS(func_02037c28, AcreKind_Free)

/* func_02037c48: the file read into the current heap; 1. */
int AcreKind_Load(void)
{
    data_021c590c = func_02064b2c(data_020da4b4, data_021fbe94, 4, &data_021c5910);
    return 1;
}
CLEAN_AS(func_02037c48, AcreKind_Load)
