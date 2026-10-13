/* func_ov004_0223a8f0 @ 0x0223a8f0, 0x78 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 unk_00, unk_01, unk_02, unk_03, unk_04, unk_05, unk_06, unk_07;
} Tm;
typedef union {
    Tm t;
    u32 w[2];
} TmBuf;
typedef struct {
    u8 a, b, c, d;
} Date;
extern void func_0209e474(TmBuf *);
extern int func_0209dc10(Date *);

int func_ov004_0223a8f0(void)
{
    TmBuf tm;
    Date d;
    tm.w[0] = 0;
    tm.w[1] = 0;
    func_0209e474(&tm);
    d.a = 1;
    d.b = 1;
    d.c = 0;
    d.d = 0;
    d.c = tm.t.unk_05;
    d.b = tm.t.unk_04;
    d.a = tm.t.unk_03;
    switch (func_0209dc10(&d)) {
        case 0:
        case 1:
        case 2:
        case 0xe:
        case 0xf:
        case 0x10:
        case 0x11:
        case 0x12:
            return 1;
        default:
            return 0;
    }
}
