/* func_ov086_02278b24 @ 0x02278b24, 0x1cc bytes, Thumb, module ov086
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020154b4(void *, u16 *, int, int, int);
extern int func_0209a000(u16 *, int);
extern int func_0209a1e8(void);
extern int func_0209a1d0(void);
extern int func_020984e8(void);
extern void *func_020a8228(void *);
extern void *func_020a8210(void *);
extern int func_020644cc(int);
extern int func_020b4a20(void *, u8 *, int);
extern int func_0203d7c4(int, void *);
extern int func_02099870(int);
extern void func_02066024(int, u8 *, void *, void *, void *, int);
extern int func_0204bd20(int, int);
extern int func_020996ac(int);
extern int func_0203cd1c(int object, u16 *item, int mode);
extern int func_0208602c(void);
extern void func_020860f0(int, int);
extern void func_0206844c(int, u8 *, void *);

extern char data_ov086_02279438;
extern char data_ov086_02279448;
extern char data_ov086_02279458;
extern char data_ov086_02279260;
extern char data_ov086_02279264;

typedef struct {
    int a;
    int b;
} UnkStruct_02278b24_2;
extern UnkStruct_02278b24_2 data_ov086_022791d0[];

typedef struct {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x21];
    int unk_40;
    char pad2[0x70];
    int unk_B4;
} UnkStruct_02278b24;

void func_ov086_02278b24(UnkStruct_02278b24 *p)
{
    struct {
        u8 b0;
        u8 b1;
        u8 pad2[2];
        u8 b4;
        u8 pad5;
        u16 h6;
        u16 h8;
        u16 ha;
        u16 hc;
        u16 he;
        u16 h10;
    } m;
    int buf[0x18];
    int code;
    int r;
    int v;
    int w;
    int t;
    int i;
    int h;

    code = 0xff;
    if (p->unk_B4 >= 0) {
        if (p->unk_1E == 1 || p->unk_1E == 4) {
            p->unk_B4 = -2;
        }
        if (p->unk_1E == 2) {
            m.h6 = 0x1559;
            func_020154b4(p, &m.h6, 0, 5, 0);
            m.h8 = 0x1559;
            func_0209a000(&m.h8, 0);
            m.b1 = 4;
            func_0206844c(p->unk_40, &m.b1, &data_ov086_02279438);
        }
        return;
    }

    r = func_0209a1e8();
    switch (p->unk_1E) {
        case 0x13:
            code = 0x14;
            if (r == -1) {
                break;
            }
            h = func_0209a1d0();
            if (h == 0) {
                break;
            }
            {
                int g = func_020984e8();
                m.b0 = 2;
                func_020a8228(buf);
                v = func_020644cc(4);
                w = v;
                for (i = 0; i < 4; i++) {
                    m.b0 = (u8) v;
                    func_020b4a20(buf, &m.b0, data_ov086_022791d0[i].a);
                    func_0203d7c4(data_ov086_022791d0[i].b, buf);
                    t = w * 4 + func_020644cc(4);
                    v = t + i * 16;
                }
                m.b0 = 0;
                func_02066024(h, &m.b0, &data_ov086_02279458, &data_ov086_02279260, &data_ov086_02279264, func_02099870(g));
                if (g != 0) {
                    m.ha = (u16) func_0204bd20(0x1d, 4);
                    func_0203cd1c(func_020996ac(g), &m.ha, 0);
                }
                func_020860f0(func_0208602c(), 4);
                m.hc = 0x1565;
                func_020154b4(p, &m.hc, 0, 5, 0);
                code = 0x15;
                func_020a8210(buf);
            }
            break;
        case 0x19:
        case 0x1a:
        case 0x1b:
            m.he = 0x137d;
            func_020154b4(p, &m.he, 0, 5, 0);
            m.h10 = 0x137d;
            func_0209a000(&m.h10, 0);
            code = (u8) (func_020644cc(3) + 0x1c);
            break;
    }

    if (code != 0xff) {
        m.b4 = (u8) code;
        func_0206844c(p->unk_40, &m.b4, &data_ov086_02279448);
    }
}
