/* func_0200da3c @ 0x0200da3c, 0x148 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02073908(void *a, u32 b);
extern int func_020b65c4(void);
extern int func_0200f290(void *a, int b);
extern int func_02096614(u16 *a, u32 *b, u32 *c, int d, u32 e);
extern int func_0209658c(u16 *a, int b, u32 c);
extern void func_020110a0(void *a, u16 *b);
extern int func_020984fc(u32 a);
extern u16 *func_02099728(unsigned int);
extern void func_0205eb8c(void *a, u16 *b, int c);
extern int func_0204bcdc(u16 *a);
extern int func_0204bc64(u16 *a);
extern void func_020109fc(void *a, int b, int c, int d);
extern void func_0205ea60(void *a);
extern void *data_020ccf94;

typedef struct {
    unsigned char pad_00[0x5c];
    u32 unk_5C;                           // 0x5c
    unsigned char pad_60[0x8];            // 0x60-0x67
    u32 unk_68;                           // 0x68
    unsigned char pad_6C[0x4];            // 0x6c-0x6f
    u32 unk_70;                           // 0x70
    unsigned char pad_74[0x7f8 - 0x74];   // 0x74-0x7f7
    u32 unk_7F8;                          // 0x7f8
    unsigned char pad_7FC[0x800 - 0x7fc]; // 0x7fc-0x7ff
    u32 unk_800;                          // 0x800
} UnkStruct_0200da3c;

void func_0200da3c(UnkStruct_0200da3c *self, int kind)
{
    void *g;
    u16 buf[4];
    u32 x, y;
    int q;
    int ok;

    g = data_020ccf94;

    if (func_02073908(g, self->unk_800) != 0 || (kind != 2 && kind != 0x8b)) {
        self->unk_7F8 = 1;
    }

    if (func_02073908(g, self->unk_800) == 0) {
        kind = func_020b65c4();

        if (func_0200f290(self, 0x10) == 0 && kind != 0x2e && kind != 0xd && kind != 0xe && kind != 0xc && kind != 0x2f) {

            if (func_02096614(buf, &x, &y, -1, self->unk_800) != 0) {
                u32 *p0 = (u32 *) ((unsigned char *) self + 0x5c);
                u32 *p1 = (u32 *) ((unsigned char *) self + 0x68);

                p1[0] = x;
                p0[0] = p1[0];
                p1[2] = y;
                p0[2] = p1[2];
            }

            if (func_0209658c(buf + 1, -1, self->unk_800) != 0) {
                func_020110a0(self, buf + 1);
            }
        }
    }

    if (func_0200f290(self, 0) != 0) {
        q = func_020984fc(self->unk_800);
        buf[2] = *func_02099728(q);
        func_0205eb8c((unsigned char *) self + 0x5a0, &buf[2], q);

        if (func_0204bcdc(&buf[2]) != 0) {
            buf[3] = 0xfff1;
            ok = (func_0204bc64(&buf[2]) == func_0204bc64(&buf[3])) ? 1 : 0;
        } else {
            ok = (buf[2] == 0xfff1) ? 1 : 0;
        }

        if (ok == 0) {
            func_020109fc(self, 0, 0, 0);
            func_0205ea60((unsigned char *) self + 0x5a0);
        }
    }
}
