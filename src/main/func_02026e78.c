/* func_02026e78 @ 0x02026e78, 0x148 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x830];
    void *unk_830;
} UnkStruct_02026e78;

typedef struct Res {
    u8 type;
} Res;

typedef struct {
    u8 pad_00[0x100];
    UnkStruct_02026e78 *unk_100;
    u8 unk_104[0x1E];
    u8 unk_122;
    u16 unk_124;
    u8 pad_126[0x160 - 0x126];
    void *unk_160;
    u8 pad_164[0x1A0 - 0x164];
    u32 unk_1A0;
} UnkStruct_02026e78_2;

typedef struct {
    void *ptr;
    u8 byte;
} UnkStruct_02026e78_3;

typedef struct {
    u32 word;
    u8 byte;
} Global;

extern Global data_020c8da8;

extern Res *func_0209b408(void *p);
extern void func_0202d5e4(u16 *buf, int zero);
extern void func_0207de14(u16 *out, void *p);
extern void func_0207de70(void *p, u16 *val);
extern int func_0205be38(void);
extern int func_0202b510(int val);
extern void func_02027170(void *buf, int val);
extern void func_0208150c(void *p);
extern int func_020036e8(void);
extern void func_0202da38(UnkStruct_02026e78_2 *self, void *r1, void *r2, int r3, int a5, int a6, int a7, int a8, int a9);

void func_02026e78(UnkStruct_02026e78_2 *self, UnkStruct_02026e78_3 *out)
{
    u16 local[5];
    int a5;
    u8 type;

    type = func_0209b408(self->unk_160)->type;
    self->unk_124 = 0xfff1;

    switch (type) {
        case 0:
            func_0202d5e4(local, 0);
            self->unk_124 = local[0];
            break;
        case 1:
            func_0207de14(&local[1], self->unk_100->unk_830);
            self->unk_124 = local[1];
            if (self->unk_124 == 0xfff1) {
                break;
            }
            func_0207de70(self->unk_100->unk_830, &self->unk_124);
            break;
        default:
            func_0207de14(&local[2], self->unk_100->unk_830);
            self->unk_124 = local[2];
            if (self->unk_124 != 0xfff1) {
                func_0207de70(self->unk_100->unk_830, &self->unk_124);
            } else {
                func_0202d5e4(&local[3], 0);
                self->unk_124 = local[3];
            }
            break;
    }

    if (self->unk_124 == 0xfff1) {
        int n = func_0205be38();
        self->unk_1A0 = (n << 2) + 0x1f4;
        self->unk_1A0 = func_0202b510(self->unk_1A0);
        func_02027170(&local[4], self->unk_1A0);
        self->unk_124 = local[4];
    }

    func_0208150c(self->unk_100->unk_830);
    a5 = func_020036e8();
    func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, a5, data_020c8da8.word, data_020c8da8.byte, 0, 0);

    out->ptr = self->unk_104;
    out->byte = self->unk_122;
}
