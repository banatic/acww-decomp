/* func_ov072_02278ae8 @ 0x02278ae8, 0x114 bytes, Thumb, module ov072
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02278ae8_4 {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
} UnkStruct_02278ae8_4;

typedef struct UnkStruct_02278ae8 {
    u8 b;
    u8 pad_01;
    u16 h;
} UnkStruct_02278ae8;
typedef struct UnkStruct_02278ae8_2 {
    u16 a;
    u16 b;
} UnkStruct_02278ae8_2;
typedef struct UnkStruct_02278ae8_3 {
    int w[2];
} UnkStruct_02278ae8_3;

extern u8 data_021ebcd2;
extern int data_ov072_02279a00;

extern int func_02015590(UnkStruct_02278ae8_4 *self, int a);
extern void func_ov072_02278f00(UnkStruct_02278ae8_4 *self, int a);
extern void func_ov072_02279098(void);
extern int func_02015330(UnkStruct_02278ae8_4 *self, u16 *p, int a, int b, int c);
extern int func_020871a8(u8 *p);
extern void func_02063ccc(UnkStruct_02278ae8_3 *o, int a, int b);
extern void func_020638d4(u16 *p, UnkStruct_02278ae8_3 *o, int a, int b, int c, int d, int e);
extern void func_02063cc8(UnkStruct_02278ae8_3 *o);
extern int func_020154b4(UnkStruct_02278ae8_4 *self, u16 *p, int a, int b, int c);
extern int func_0209a000(u16 *p, int a);
extern void func_0204093c(int a);
extern void func_0206844c(int h, u8 *p, int k);

void func_ov072_02278ae8(UnkStruct_02278ae8_4 *self)
{
    UnkStruct_02278ae8 m;
    UnkStruct_02278ae8_2 n;
    UnkStruct_02278ae8_3 o;
    u8 *p;
    int k;
    int code;

    p = &data_021ebcd2;
    m.h = 0xfff1;
    k = (int) &data_ov072_02279a00;
    code = 0xff;
    switch (self->unk_1E) {
        case 0:
            func_02015590(self, 0);
            func_ov072_02278f00(self, 1);
            break;
        case 0xb:
            func_ov072_02279098();
            break;
        case 0x14:
        case 0x15:
            n.a = 0x1568;
            func_02015330(self, &n.a, 0, 5, 0);
            code = 0x16;
            break;
        case 0x16:
            if (func_020871a8(p) >= 5) {
                code = 0x17;
            } else {
                code = (u8) (func_020871a8(p) + 0x19);
            }
            break;
        case 0x18:
            func_02063ccc(&o, 0, 0x13);
            func_020638d4(&n.b, &o, 0, 0, 1, 1, 0);
            m.h = n.b;
            func_02063cc8(&o);
            func_020154b4(self, &m.h, 0, 5, 0);
            func_0209a000(&m.h, 0);
            code = 0x19;
            break;
        case 0x19:
            func_0204093c(0x44);
            break;
    }
    if (code != 0xff) {
        m.b = (u8) code;
        func_0206844c(self->unk_40, &m.b, k);
    }
}
