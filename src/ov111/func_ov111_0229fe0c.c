/* func_ov111_0229fe0c @ 0x0229fe0c, 0xcc bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov002_02207f60(void *);
extern void func_ov095_0229b1c8(void *, int, void *, int);
extern void func_ov095_0229b0d8(void *, int, void *);
extern void func_ov095_0229b090(void *, int, void *, int, int);
extern int func_ov095_0229af58(void *, int, void *, int);
extern void func_ov095_0229aeec(void *, int, void *);

struct UnkStruct_0229fe0c {
    u8 pad_00[0x9a];
    u8 unk_9A;
    u8 unk_9B;
    u8 unk_9C;
    u8 pad_9D[4];
    u8 unk_A1;
    u8 pad_A2[10];
    u8 obj[1];
};

void func_ov111_0229fe0c(struct UnkStruct_0229fe0c *self)
{
    u8 *work;
    int mode;

    work = (u8 *) func_ov002_02207f60(self) + 0x60;

    func_ov095_0229b1c8(self->obj, 0x80, work, 2);
    func_ov095_0229b0d8(self->obj, 0x80, work);

    if (self->unk_9A != 0) {
        if (self->unk_9B < 2) {
            self->unk_9B++;
        }
        mode = 7;
    } else {
        if (self->unk_9B != 0) {
            self->unk_9B--;
        }
        mode = 6;
    }

    func_ov095_0229b090(self->obj, 0x80, work, mode, self->unk_9B);
    self->unk_9C++;

    if (self->unk_9A == 0 && (self->unk_9C & 0x10) != 0) {
        func_ov095_0229af58(self->obj, self->unk_A1 + 0x18, work - 0x38, 2);
    }

    func_ov095_0229aeec(self->obj, 0x80, work);
}
