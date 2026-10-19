/* func_ov053_022613b0 @ 0x022613b0, 0xd4 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x5c];
    Vec3 pos;
    char pad_68[0x3b0 - 0x68];
    char unk_3B0;
    char pad_3B1[0x618 - 0x3b1];
    char unk_618;
    char pad_619[0x658 - 0x619];
    char unk_658;
    char pad_659[0x71b - 0x659];
    u8 unk_71B;
} UnkStruct_022613b0;

extern char data_021fbee8[];
extern int data_020c814c;

extern void func_0201ad18(void *p, int a, int b, int c, void *d, int e, int f, int g);
extern int func_02016104(void *p);
extern int func_0201c314(UnkStruct_022613b0 *self, int a);
extern int func_ov053_02260ba8(void *p);
extern int func_ov004_0224719c(Vec3 *v);
extern int func_020147fc(void *p, int a, int b, int c);

int func_ov053_022613b0(UnkStruct_022613b0 *self)
{
    Vec3 v;
    Vec3 *q;
    int n;
    int x;

    func_0201ad18(&self->unk_3B0, 1, 0, 0, data_021fbee8, 4, data_020c814c, 1);
    x = func_02016104(&self->unk_658);
    n = 0;
    if (x != 0) {
        n = func_0201c314(self, x);
    }
    if (func_ov053_02260ba8(&self->unk_658) == 5) {
        q = &self->pos;
        v.x = q->x;
        v.y = q->y;
        v.z = q->z;
        v.y = v.y + 0x2000;
        func_ov004_0224719c(&v);
        self->unk_71B = 0x1f;
    }
    if (func_ov053_02260ba8(&self->unk_658) == 5 || func_ov053_02260ba8(&self->unk_658) == 8 ||
        func_ov053_02260ba8(&self->unk_658) == 0xa) {
        func_020147fc(&self->unk_618, 0, n, 1);
        return 1;
    }
    func_020147fc(&self->unk_618, 0, n, 0);
    return 1;
}
