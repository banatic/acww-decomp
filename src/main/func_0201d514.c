/* func_0201d514 @ 0x0201d514, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020984e8(void);
extern int func_02099734(int);
extern int func_02098eb8(int object);
extern int func_02098f0c(int, void *, int, int);
extern int func_020996ac(int);
extern int func_0203cd2c(int, void *, int, int);
extern int func_0207de70(int, void *);
extern void func_02098a24(int, int, int);
extern int func_020154b4(void *, void *, int, int, int);

typedef struct {
    u32 lo;
    u32 hi;
} Pair;

extern Pair data_020d93f8;

extern void func_0202dbf0(void *, Pair);

typedef struct {
    u8 pad_00[0x100];
    unsigned char *unk_100;
    u8 pad_104[0x98];
    u16 unk_19C;
    u8 unk_19E;
    u8 pad_19F;
    int unk_1A0;
} UnkStruct_0201d514;

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
