/* func_ov120_0229be00 @ 0x0229be00, 0xdc bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x94];
    int unk_94;
    u16 unk_98;
    u8 pad_9A[0xAC - 0x9A];
    u8 unk_AC;
    u8 unk_AD;
    u8 unk_AE;
    u8 pad_AF[0x2743 - 0xAF];
    u8 table[1024];
} UnkStruct_0229be00;

extern int func_ov002_02207f48(void *, int);
extern void func_ov002_022080a0(void *, int);
extern void func_ov002_02207e80(void *, int, int, int);
extern int func_ov002_02207f60(void *);
extern void func_ov120_0229a438(UnkStruct_0229be00 *, int);
extern void func_ov120_0229b604(UnkStruct_0229be00 *);

void func_ov120_0229be00(UnkStruct_0229be00 *self)
{
    if (func_ov002_02207f48(self, 0)) {
        func_ov002_022080a0(self, 2);
        self->unk_AC = 8;
        self->unk_AD = self->table[self->unk_AC * 3];
        self->unk_AE = *(self->table + (self->unk_AC * 3) + 1);
        if (self->unk_AE > 4) {
            self->unk_AE -= 4;
        } else {
            self->unk_AE = 0;
        }
        if (self->unk_AD < 0xFC) {
            self->unk_AD += 4;
        } else {
            self->unk_AD = 0xFF;
        }
        func_ov120_0229a438(self, 0x800);
        func_ov120_0229b604(self);
    }
    func_ov002_02207e80(self, 4, 0, 0);
    func_ov002_02207e80(self, 6, 0, 0x50 - self->unk_98);
    self->unk_94 = func_ov002_02207f60(self);
}
