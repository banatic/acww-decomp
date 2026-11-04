/* sound_emitter_class_3: 7 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f5970 @ 0x020f5970, 0x18 bytes, ARM
 * func_020f5958 @ 0x020f5958, 0x18 bytes, ARM
 * func_020f5948 @ 0x020f5948, 0x10 bytes, ARM
 * func_020f5924 @ 0x020f5924, 0x24 bytes, ARM
 * func_020f5914 @ 0x020f5914, 0x10 bytes, ARM
 * func_020f58e0 @ 0x020f58e0, 0x34 bytes, ARM
 * func_020f58cc @ 0x020f58cc, 0x14 bytes, ARM
 */

#include "types.h"

typedef struct {
    void *p;
    char pad_04[0x3a];
    char flag;
} UnkStruct_020f5970;

typedef struct {
    int *unk_00;
    char pad_04[0x3a];
    char unk_3E;
} UnkStruct_020f5958;

typedef struct UnkStruct_020f58e0 {
    u8 pad_00[0x3c];
    u16 unk_3C;
} UnkStruct_020f58e0;

extern char data_0213f074;
extern void func_020edb3c(int argument0);
extern void func_020ef760(void *sub);
extern void func_020ef840(void *sub, int flag);
extern void func_020ef498(int p, void *argument1);

void func_020f5970(UnkStruct_020f5970 *s)
{
    s->p = &data_0213f074;
    s->flag = 0;
}

void func_020f5958(UnkStruct_020f5958 *p)
{
    p->unk_00 = ((int *) &data_0213f074);
    p->unk_3E = 0;
}

void func_020f5948(int *p)
{
    *p = (int) ((int *) &data_0213f074);
}

void *func_020f5924(void *p)
{
    *((void **) p) = (void *) &data_0213f074;
    func_020edb3c((int) p);
    return p;
}

void func_020f5914(char **p)
{
    *p = &data_0213f074;
}

void func_020f58e0(UnkStruct_020f58e0 *self)
{
    void *arg2;
    func_020ef760(self ? (u8 *) self + 4 : (void *) self);
    arg2 = self;
    if (self != 0) {
        arg2 = (u8 *) self + 4;
    }
    func_020ef840(arg2, 1);
    self->unk_3C = 0;
}

void func_020f58cc(int p, void *argument1)
{
    if (p) {
        p += 4;
    }
    func_020ef498(p, argument1);
}
