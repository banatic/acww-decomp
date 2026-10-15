/* func_ov087_02278ab8 @ 0x02278ab8, 0x1f8 bytes, Thumb, module ov087
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_loop_invariants off
extern void *func_020160b4(void *);
extern unsigned int func_020ab504(void *);
extern void *func_020984e8(void);
extern void *func_02099670(void *);
extern u16 func_0209a034(unsigned int);
extern void func_0209a050(int);
extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);
extern unsigned int func_020644cc(unsigned int);
extern void func_02088b98(void *, int);
extern int func_02015330(void *, u16 *, unsigned int, u8, unsigned int);
extern int func_0209a1e8(void);
extern void *func_0209a1d0(void);
extern void *func_020a8228(void *);
extern void *func_020a8210(void *);
extern int func_020b4a20(void *, u8 *, int);
extern int func_0203d7c4(int, void *);
extern void *func_02099870(void *);
extern void func_02066024(void *, u8 *, void *, void *, void *, void *);
extern unsigned int func_0204bd20(unsigned int, unsigned int);
extern void *func_020996ac(void *);
extern int OS_UnlockByWord_IrqAndFiq(void *, u16 *, int);
extern int func_0202ea80(int, int);
extern void func_0206844c(void *, u8 *, void *);
typedef struct {
    int a;
    int b;
} UnkStruct_02278ab8_2;
extern UnkStruct_02278ab8_2 data_ov087_02279304[];
extern char data_ov087_022793c0;
extern char data_ov087_022793c4;
extern char data_ov087_022795a8;
extern char data_ov087_02279598;
typedef struct {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad1[0x21];
    void *unk_40;
} UnkStruct_02278ab8;
void func_ov087_02278ab8(UnkStruct_02278ab8 *p)
{
    struct {
        u8 b0;
        u8 pad1[2];
        u8 b3;
        volatile u16 h4;
        u16 h6;
        u16 h8;
        u16 ha;
    } m;
    int buf[0x18];
    long long randomBase;
    int v;
    int i;
    void *g;
    void *q;
    void *h;
    int c5;
    int c6;
    int code;
    int t;
    int r5;
    int w;
    UnkStruct_02278ab8_2 *e;
    int ok;
    u16 a1;
    u16 a2;
    r5 = func_020ab504(func_020160b4(p));
    g = func_020984e8();
    code = 0xff;
    switch (p->unk_1E) {
        case 5: {
            int i;
            if (r5 != 0) {
                break;
            }
            q = func_02099670(g);
            m.h4 = 0xfff1;
            i = 0;
            c5 = 0;
            c6 = 0;
            for (; i < 0xf; i++) {
                m.h4 = (u16) func_0209a034(i);
                ok = 0;
                a2 = m.h4;
                a1 = m.h4;
                if ((a1 >= 0x1542) && (a2 <= 0x1546)) {
                    ok = 1;
                }
                if (ok == 0) {
                    continue;
                }
                if (func_0204bcdc((u16 *) (&m.h4)) != 0) {
                    m.h8 = 0x1546;
                    t = func_0204bc64((u16 *) (&m.h4));
                    ok = (t == func_0204bc64(&m.h8)) ? (1) : (0);
                } else {
                    ok = (m.h4 == 0x1546) ? (1) : (0);
                }
                if (ok != 0) {
                    c6++;
                } else {
                    c5++;
                }
                func_0209a050(i);
            }

            m.h4 = 0x1542;
            if (c6 == 0) {
                code = (u8) (func_020644cc(3) + 7);
                while (c5 > 0) {
                    func_02088b98(q, 1);
                    c5--;
                }

            } else if (c5 != 0) {
                m.h4 = 0x1546;
                code = 0x18;
            } else {
                code = 0x19;
            }
            func_02015330(p, (u16 *) (&m.h4), 0, 5, 0);
            break;
        }
        case 0x10:
            if (r5 != 0) {
                break;
            }
            code = 0x12;
            if (func_0209a1e8() == (-1)) {
                break;
            }
            h = func_0209a1d0();
            if (h == 0) {
                break;
            }
            code = 0x13;
            m.b0 = 2;
            func_020a8228(buf);
            randomBase = func_020644cc(4) + 4;
            w = randomBase;
            v = w;
            for (i = 0; i < 4; i++) {
                m.b0 = (u8) v;
                e = &data_ov087_02279304[i];
                func_020b4a20(buf, &m.b0, data_ov087_02279304[i].a);
                func_0203d7c4(e->b, buf);
                v = (w - 4) * 4;
                v += func_020644cc(4);
                v += i * 16;
            }

            m.b0 = 2;
            func_02066024(h, &m.b0, &data_ov087_022795a8, &data_ov087_022793c4, &data_ov087_022793c0, func_02099870(g));
            if (g != 0) {
                m.h6 = (u16) func_0204bd20(0x1d, 4);
                OS_UnlockByWord_IrqAndFiq(func_020996ac(g), &m.h6, 0);
            }
            func_0202ea80(0x1a, 1);
            func_020a8210(buf);
            break;
    }

    if (code != 0xff) {
        m.b3 = (u8) code;
        func_0206844c(p->unk_40, &m.b3, &data_ov087_02279598);
    }
}
