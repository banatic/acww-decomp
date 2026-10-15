/* func_0202703c @ 0x0202703c, 0x134 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Pair {
    int a;
    int b;
};

struct ST {
    int pad_00[8];
    char a;
    char b;
    u8 pad2[2];
};

struct UnkStruct_0202703c {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xbc];
    char *unk_100;
    char pad2[0x20];
    u16 unk_124;
    char pad_126[0x7a];
    int unk_1A0;
};

extern struct Pair data_020d9460;

extern void *func_0202d9c4(struct UnkStruct_0202703c *a);
extern int func_0209bc40(void *a);
extern void func_0201cfb4(struct UnkStruct_0202703c *a, struct ST *st);
extern void func_0201cf90(struct UnkStruct_0202703c *a, struct ST *st, int idx, int w, int h, void *str);
extern void func_0201cec8(struct UnkStruct_0202703c *a, struct ST *st);
extern void func_0202da74(struct UnkStruct_0202703c *a, struct Pair p);
extern void func_02068388(int a, int b);
extern int func_020644cc(int a);
extern void func_0207de14(u16 *out, int p);
extern int func_0207de70(int p, u16 *out);
extern int func_0205be38(void);
extern int func_0202b510(int a);
extern void func_02027170(u16 *out, int p);
extern void func_0202d5e4(u16 *out, int p);
extern void func_02026c1c(struct UnkStruct_0202703c *a, int b);

void func_0202703c(struct UnkStruct_0202703c *self, int param1)
{
    u16 buf[4];
    struct ST st;
    int r;

    switch (func_0209bc40(func_0202d9c4(self))) {
        case 0xa:
            func_0201cfb4(self, &st);
            func_0201cf90(self, &st, 0, 0x24, 0x24, 0);
            func_0201cf90(self, &st, 1, 0x25, 0x25, 0);
            func_0201cf90(self, &st, 2, 0x26, 0x26, 0);
            st.a = 3;
            st.b = 0xffffffff;
            func_0201cec8(self, &st);
            func_0202da74(self, data_020d9460);
            func_02068388(self->unk_40, 1);
            break;
        case 0x13:
            r = func_020644cc(100);
            self->unk_124 = 0xfff1;
            if (r < 0x14) {
                func_0207de14(&buf[0], *(int *) (self->unk_100 + 0x830));
                self->unk_124 = buf[0];
                if (self->unk_124 != 0xfff1) {
                    func_0207de70(*(int *) (self->unk_100 + 0x830), &self->unk_124);
                }
            } else if (r < 0x28) {
                self->unk_1A0 = 0x1f4 + func_0205be38() * 4;
                self->unk_1A0 = func_0202b510(self->unk_1A0);
                func_02027170(&buf[1], self->unk_1A0);
                self->unk_124 = buf[1];
            }
            if (self->unk_124 == 0xfff1) {
                func_0202d5e4(&buf[2], 0);
                self->unk_124 = buf[2];
            }
            func_02026c1c(self, param1);
            break;
    }
}
