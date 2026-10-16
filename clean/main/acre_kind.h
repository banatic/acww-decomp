/* The kinds of the acre models: "/bg/bkattr.bin", loaded into the current heap
 * (data_021c590c, its size data_021c5910), gives each model number a kind, and the table
 * data_020ca008 gives each of the 55 kinds its flags (the acres' flags func_02037d64 and
 * func_02037d80 test). */
#ifndef CLEAN_MAIN_ACRE_KIND_H
#define CLEAN_MAIN_ACRE_KIND_H

#include "types.h"

#define ACRE_KINDS 55
/* The kind AcreKind_Find answers when no kind has the flags. */
#define ACRE_KIND_LAST (ACRE_KINDS - 1)

u32 AcreKind_CountFlags1000(int kind);
int AcreKind_Flags(int kind);
int AcreKind_ModelFlags(unsigned int model);
int AcreKind_Find(int flags);
u8 AcreKind_OfModel(unsigned int model);
int AcreKind_Free(void);
int AcreKind_Load(void);

#endif
