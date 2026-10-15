/* func_020196e8 @ 0x020196e8, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 data_020c80f8;

typedef struct {
    u32 pad_00;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u8 pad_18[2];
    s16 unk_1A;
    u16 unk_1C;
} SrcStruct;

typedef struct {
    u32 a;
    u32 b;
    u32 c;
} StackStruct;

typedef struct {
    u8 pad_00[4];
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0xe];
    u32 unk_14;
    u8 pad_18[4];
    u32 unk_1C;
} ObjStruct;

extern SrcStruct *func_02019de4(int);
extern void func_0201b044(void *dst, const StackStruct *src);
extern void func_0201afd4(void *dst, const StackStruct *src);
extern void func_0201b1a4(void *dst, void *base, int n, int m, u16 p);
extern void func_0201b350(void *dst, int v);
extern void func_020123ec(u32 a, u16 b, u32 c);
extern void func_02019ac0(void *dst, u32 a, u32 b, u32 c, u32 d, s16 e, u16 f);
extern void func_02019af0(void *dst, int v);

int func_020196e8(ObjStruct *obj, char *base)
{
    StackStruct s[2];
    SrcStruct *src;
    u32 c0, a0, c1, a1;

    src = func_02019de4((int) obj);

    c0 = src->unk_08;
    a0 = src->unk_04;
    s[0].a = a0;
    s[0].b = 0;
    s[0].c = c0;

    c1 = src->unk_10;
    a1 = src->unk_0C;
    s[1].a = a1;
    s[1].b = 0;
    s[1].c = c1;

    func_0201b044((void *) (base + 0x350), &s[0]);
    func_0201afd4((void *) (base + 0x350), &s[1]);

    func_0201b1a4((void *) (base + 0x350), base, 2, src->unk_1A, src->unk_1C);
    func_0201b350((void *) (base + 0x3aa), 1);

    if (*(u32 *) (base + 0x628) != 0) {
        func_020123ec(*(u32 *) (base + 0x628), data_020c80f8, 0);
    }

    obj->unk_04 = (u8) obj->unk_1C;
    obj->unk_05 = (u8) obj->unk_14;

    func_02019ac0((void *) ((char *) obj + 6), src->unk_04, src->unk_08, src->unk_0C, src->unk_10, src->unk_1A, src->unk_1C);
    func_02019af0(obj, 0);

    return 0;
}
