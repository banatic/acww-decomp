/* villager_talk_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201d5cc @ 0x0201d5cc, 0x64 bytes, Thumb
 * func_0201d514 @ 0x0201d514, 0xb8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u32 lo;
    u32 hi;
} Pair;

typedef struct {
    u8 pad_00[0x100];
    unsigned char *unk_100;
    u8 pad_104[0x98];
    u16 unk_19C;
    u8 unk_19E;
    u8 pad_19F;
    int unk_1A0;
} UnkStruct_0201d514;

extern int func_02015330(void *self, void *ctx, int a, int b, int c);
extern void func_0207df18(void *a, void *b);
extern void func_02081ac0(void *a, void *b);
extern void func_02068440(void *a);
extern int func_020984e8(void);
extern int func_02099734(int);
extern int func_02098eb8(int object);
extern int func_02098f0c(int, void *, int, int);
extern int func_020996ac(int);
extern int func_0203cd2c(int, void *, int, int);
extern int func_0207de70(int, void *);
extern void func_02098a24(int, int, int);
extern int func_020154b4(void *, void *, int, int, int);
extern Pair data_020d93f8;
extern void func_0202dbf0(void *, Pair);

void func_0201d5cc(void *selfv)
{
    unsigned char *self = (unsigned char *) selfv;
    void *ptr;
    void *val;

    ptr = *(void **) (self + 0x100);
    val = *(void **) ((unsigned char *) ptr + 0x830);

    func_02015330(self, self + 0x124, 0, 5, 0);

    if (val != 0) {
        if (*(unsigned short *) (self + 0x124) != 0xfff1) {
            func_0207df18(val, self + 0x124);
            if (*(void **) (self + 0x12c) != 0) {
                func_02081ac0(*(void **) (self + 0x12c), self + 0x124);
            }
        }
    }
    func_02068440(*(void **) (self + 0x40));
}

int func_0201d514(UnkStruct_0201d514 *p)
{
    int a, b, c;

    if (p->unk_1A0 > 0 && p->unk_19C != 0xfff1) {
        a = func_020984e8();
        b = func_02099734(a);
        c = func_02098eb8((int) b);

        if (c >= 0) {
            func_02098f0c(b, &p->unk_19C, c, 0);
            func_0203cd2c(func_020996ac(a), &p->unk_19C, 0, 1);

            if (p->unk_19E == 1) {
                func_0207de70(*(unsigned int *) (p->unk_100 + 0x830), &p->unk_19C);
            }

            func_02098a24(b, -p->unk_1A0, 1);

            func_020154b4(p, &p->unk_19C, 0, 5, 0);

            func_0202dbf0(p, data_020d93f8);

            return 1;
        }
    }
    return 0;
}
