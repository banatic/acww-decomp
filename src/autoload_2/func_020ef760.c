/* func_020ef760 @ 0x020ef760, 0x9c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u8 pad_00[8];
    u8 pad_08[0x2c - 0x08];
    void (*func1)(void);
    void (*func2)(void);
    u16 unk_34;
    u8 unk_36;
} UnkStruct_020ef760;

typedef struct {
    u8 pad_00[0xc];
    volatile int unk_0C;
} UnkStruct_020ef760_2;

extern UnkStruct_020ef760_2 data_021fd054;
extern void func_020efbb8(void);
extern void func_020efb64(void);
extern void func_020efa3c(void *);
extern void OS_Terminate(void);

void func_020ef760(void *self)
{
    UnkStruct_020ef760 *p = (UnkStruct_020ef760 *) self;
    int i;
    u8 *q;

    p->unk_36 = 3;
    p->func1 = func_020efbb8;
    p->func2 = func_020efb64;

    if (p->unk_36 > 3) {
        OS_Terminate();
    }

    p->unk_34 = 0;
    if ((int) p->unk_36 > 0) {
        i = 0;
        q = (u8 *) p + 8;
        do {
            func_020efa3c(q);
            i++;
            q += 0xc;
        } while (i < p->unk_36);
    }

    {
        UnkStruct_020ef760_2 *g = &data_021fd054;

        if (g->unk_0C >= 1 && g->unk_0C < 4) {
            return;
        }
    }

    OS_Terminate();
}