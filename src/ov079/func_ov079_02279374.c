/* func_ov079_02279374 @ 0x02279374, 0x188 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0206fc6c(void);
extern int func_0206fc8c(void);
extern int func_0209a034(int);
extern int func_0209a050(void);
extern void func_02015330(void *, u16 *, int, int, int);
extern void func_020155cc(void *);
extern void func_ov079_02279508(void *, int);
extern void func_0206844c(int, u8 *, void *);
extern char data_ov079_0227a1b0;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x80];
    u16 unk_C4;
    char pad_C6[2];
    int unk_C8;
} UnkStruct_02279374;

void func_ov079_02279374(UnkStruct_02279374 *p)
{
    u8 m;
    int h;
    u16 v;
    unsigned int ok;

    h = p->unk_40;
    m = 1;
    p->unk_C8 = -1;
    if (func_0206fc6c() != 0) {
        p->unk_C8 = func_0206fc8c();
        p->unk_C4 = (u16) func_0209a034(p->unk_C8);
        m = 2;

        ok = 0;
        v = p->unk_C4;
        if (v >= 0x12e8 && v <= 0x131f) {
            ok = 1;
        }
        if (ok > 0 || (v >= 0x1531 && v <= 0x153a) || (v >= 0x1518 && v <= 0x151c) || (v >= 0x1542 && v <= 0x1546) ||
            (v >= 0x1548 && v <= 0x1548) || (v >= 0x153b && v <= 0x1541)) {
            m = 3;
        }

        ok = 0;
        v = p->unk_C4;
        if (v >= 0x136a && v <= 0x136a) {
            ok = 1;
        }
        if (ok > 0 || (v >= 0x1373 && v <= 0x1373) || (v >= 0x1375 && v <= 0x1375) || (v >= 0x1377 && v <= 0x1377) ||
            (v >= 0x1379 && v <= 0x1379) || (v >= 0x137b && v <= 0x137b)) {
            m = 0xb;
            p->unk_C8 = -1;
        }

        if (p->unk_C8 >= 0) {
            func_0209a050();
            p->unk_C8 = -1;
        }
        func_02015330(p, &p->unk_C4, 0, 4, 0);
        func_ov079_02279508(p, 1);
    } else {
        func_020155cc(p);
    }

    func_0206844c(h, &m, &data_ov079_0227a1b0);
}
