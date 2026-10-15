/* func_ov140_0229b038 @ 0x0229b038, 0x1f4 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229b038 UnkStruct_0229b038;
struct UnkStruct_0229b038 {
    u8 pad_00[0x94];
    void *unk_94;
    u32 unk_98;
    int unk_9C;
    u32 unk_A0;
    u32 unk_A4;
    u32 unk_A8;
    u8 pad_AC[0x8e0 - 0xac];
    unsigned char arr8e0[6];
    u8 pad_8E6[0x8e8 - 0x8e6];
    u8 sub8e8[0x128c - 0x8e8];
    u8 use128c[4];
    u8 pad_1290[0x12f0 - 0x1290];
    u8 use12f0[4];
};

typedef struct {
    u32 d[5];
} Table5;

extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *);
extern void *func_ov139_022995d8(void *, int);
extern void func_ov139_02299a68(void *, int, void *);
extern void func_ov002_0220ad18(void *, u32);
extern int func_ov140_02299fb0(UnkStruct_0229b038 *, int);
extern void func_02088df8(int, const void *, int, void *, int, int, int, int, int, int, int, int);

extern const u8 data_ov140_0229b3a4[];
extern const u8 data_ov140_0229b3cc[];
extern const u8 data_ov140_0229b464[];
extern const Table5 data_ov140_0229b390;

int func_ov140_0229b038(UnkStruct_0229b038 *self)
{
    char *base;
    void *res5;
    void *res6;
    void *res7;
    Table5 table;
    int unknown;
    int i;

    if (func_0206fe54()) {
        func_ov002_02209eb8(&self->use128c);
    }

    if (!func_ov140_02299fb0(self, 1)) {
        return 0;
    }

    func_ov002_0220ad18(&self->use12f0, self->unk_98);

    base = (char *) self->unk_94 + 0x60;

    func_02088df8(1, data_ov140_0229b3a4, 0x80, base, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);

    res5 = func_ov139_022995d8(&self->sub8e8, 5);
    res6 = func_ov139_022995d8(&self->sub8e8, 6);
    res7 = func_ov139_022995d8(&self->sub8e8, 7);

    if (self->unk_9C != -1) {
        func_02088df8(1, data_ov140_0229b3cc, 0x80, base + self->unk_9C * 0x10, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    }

    func_02088df8(1, data_ov140_0229b464, 0x80, base, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);

    func_02088df8(1, res5, 0x80, base, self->unk_A8, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    func_02088df8(1, res6, 0x80, base, self->unk_A4, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    func_02088df8(1, res7, 0x80, base, self->unk_A0, 2, 0x1000, 0x1000, 0, -1, 0, 0);

    func_ov139_02299a68(&self->sub8e8, 0, self->unk_94);

    if (func_ov140_02299fb0(self, 0x20)) {
        // skip the loop
    } else {
        table = data_ov140_0229b390;
        unknown = 0;

        for (i = 0; i < 6; i++) {
            unsigned char b = self->arr8e0[i];
            void *p = (void *) table.d[b];
            if (p) {
                func_02088df8(1, p, 0x80, base, -1, 2, 0x1000, 0x1000, unknown, -1, unknown, unknown);
            }
            base += 0x10;
        }
    }

    return 1;
}
