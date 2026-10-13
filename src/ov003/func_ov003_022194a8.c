/* func_ov003_022194a8 @ 0x022194a8, 0x100 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u16 id;
    u16 pad;
    int unk_04;
    int unk_08;
    u8 unk_0C;
    u8 unk_0D;
} UnkStruct_022194a8;

typedef struct {
    char pad[0xc];
    u16 unk_0C;
} Src;

extern void *data_020ccf94;

extern void func_ov003_0222e898(int a, int b);
extern int func_0204fea4(void);
extern void func_020109a0(void *self, int a, int b, int c);
extern void func_0200f328(void *self, int a);
extern int func_02073908(void *a, int b);
extern void func_ov003_022195c0(void *q, int a);
extern void func_ov003_022195ac(void *q, int a);
extern unsigned int func_ov003_022195a8(void *q);

void func_ov003_022194a8(char *self, Src *src)
{
    u16 v;
    u16 id;
    UnkStruct_022194a8 *w;
    int f;
    u16 a0, a1;
    int code;
    void *q;
    int x;
    u16 h;

    w = (UnkStruct_022194a8 *) (self + 0x7d4);
    id = src->unk_0C;
    v = id;
    w->id = id;
    f = 0;
    w->unk_04 = -1;
    w->unk_08 = 0;

    a0 = *(volatile u16 *) &v;
    a1 = *(volatile u16 *) &v;
    if (a1 >= 0x12e8 && a0 <= 0x131f) {
        f = 1;
    }
    w->unk_0C = (u8) f;
    w->unk_0D = 0;

    if (w->unk_0C == 0) {
        f = 0;
        a0 = *(volatile u16 *) &v;
        a1 = *(volatile u16 *) &v;
        if (a1 >= 0x12b0 && a0 <= 0x12e7) {
            f = 1;
        }
        x = f ? (a0 - 0x12b0) : -1;
        func_ov003_0222e898((u8) x, (u8) * (int *) (self + 0x800));
        code = 0x9f;
    } else {
        w->unk_08 = func_0204fea4();
        code = 0x9e;
    }

    func_020109a0(self, code, 3, 3);
    func_0200f328(self, 0x4f);

    q = self + 0x8f0;
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        func_ov003_022195c0(q, id);
        func_ov003_022195ac(q, 0);
    } else {
        if (func_ov003_022195a8(q) >= 1) {
            w->unk_0D = 1;
            h = (u16) (*(u32 *) (self + 0x2d4) >> 12);
            h = h - 1;
            *(int *) (self + 0x2d8) = h << 12;
        }
    }
}
