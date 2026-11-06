/* local_search_3: 3 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_02267ef8 @ 0x02267ef8, 0xf0 bytes, ARM
 * func_ov066_02267e28 @ 0x02267e28, 0xd0 bytes, ARM
 * func_ov066_02267e00 @ 0x02267e00, 0x28 bytes, ARM
 */

#include "types.h"

struct State {
    u8 pad_00[9];
    u8 count;
    u8 pad_0A[2];
    u8 unk_0C;
};

struct Context {
    void *unk_00;
    void *unk_04;
    void *unk_08;
};

typedef struct Obj1 {
    char pad_00[9];
    unsigned char unk_09;
} Obj1;

typedef struct Work {
    void *unk_00;
    void *unk_04;
    void *unk_08;
    int unk_0C;
    char sub_10[0x3c - 0x10];
    char sub_3c[0x6c - 0x3c];
    int unk_6C;
} Work;

struct UnkStruct_02267e00 {
    unsigned char pad_00[0x6C];
    unsigned int unk_6C;
};

extern void *func_ov066_02266908(u32 size, u32 align);
extern void func_ov066_0226a810(void *dest, u8 idx, u8 width);
extern void OS_CreateAlarm(void *p);
extern struct Context *data_ov066_0226bdf0;
extern struct State *data_ov066_0226bdec;
void func_ov066_0226a7d8(void *);
void func_ov066_022668c4(void *);
void OS_CancelAlarm(void *);
extern unsigned int OS_DisableInterrupts(void);
extern unsigned int OS_RestoreInterrupts(int value);

void func_ov066_02267ef8(void)
{
    int i;

    data_ov066_0226bdf0 = (struct Context *) func_ov066_02266908(0x70, 4);
    data_ov066_0226bdf0->unk_00 = func_ov066_02266908(0x20, 0x20);
    data_ov066_0226bdf0->unk_04 = func_ov066_02266908(0xc0, 0x20);
    data_ov066_0226bdf0->unk_08 = func_ov066_02266908(data_ov066_0226bdec->count << 4, 4);

    for (i = 0; i < data_ov066_0226bdec->count; i++) {
        func_ov066_0226a810((char *) data_ov066_0226bdf0->unk_08 + i * 0x10, (u8) i, data_ov066_0226bdec->unk_0C);
    }

    OS_CreateAlarm((char *) data_ov066_0226bdf0 + 0x10);
    OS_CreateAlarm((char *) data_ov066_0226bdf0 + 0x3c);
}

void func_ov066_02267e28(void)
{
    int i = (*(Obj1 **) &data_ov066_0226bdec)->unk_09 - 1;
    int off;

    if (i >= 0) {
        off = i * 16;
        do {
            func_ov066_0226a7d8((char *) (*(Work **) &data_ov066_0226bdf0)->unk_08 + off);
            off -= 16;
        } while (--i >= 0);
    }

    func_ov066_022668c4((*(Work **) &data_ov066_0226bdf0)->unk_08);
    func_ov066_022668c4((*(Work **) &data_ov066_0226bdf0)->unk_04);
    func_ov066_022668c4((*(Work **) &data_ov066_0226bdf0)->unk_00);

    (*(Work **) &data_ov066_0226bdf0)->unk_6C = 0;
    (*(Work **) &data_ov066_0226bdf0)->unk_0C &= ~1;

    OS_CancelAlarm(&(*(Work **) &data_ov066_0226bdf0)->sub_3c);
    OS_CancelAlarm(&(*(Work **) &data_ov066_0226bdf0)->sub_10);

    func_ov066_022668c4((*(Work **) &data_ov066_0226bdf0));
    (*(Work **) &data_ov066_0226bdf0) = 0;
}

void func_ov066_02267e00(unsigned int param)
{
    int ret = OS_DisableInterrupts();
    (*(struct UnkStruct_02267e00 **) &data_ov066_0226bdf0)->unk_6C = param;
    OS_RestoreInterrupts(ret);
}
