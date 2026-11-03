/* turtle6_talk: 3 functions, module ov086
 * mwccarm 1.2/base -O4,s
 * func_ov086_02278cf0 @ 0x02278cf0, 0x17c bytes, Thumb
 * func_ov086_02278b24 @ 0x02278b24, 0x1cc bytes, Thumb
 * func_ov086_02278ab8 @ 0x02278ab8, 0x6c bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xb4];
    int unk_B4;
} UnkStruct_02278cf0;

typedef struct {
    void *ptr;
    u8 byte;
} UnkStruct_02278cf0_2;

typedef struct {
    u16 a;
    u8 b[6];
    u32 c;
    u32 d;
} Locals;

typedef struct {
    int a;
    int b;
} UnkStruct_02278b24_2;

typedef struct {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x21];
    int unk_40;
    char pad2[0x70];
    int unk_B4;
} UnkStruct_02278b24;

extern int func_020984e8(void);
extern int func_02099640(int);
extern int func_02099e9c(u16 *);
extern void func_0209df64(void *);
extern void func_0209e474(void *);
extern int func_0209dcac(void);
extern int func_020644cc(int);
extern int func_0208602c(void);
extern int func_02086108(int, int);
extern int func_02099fe8(void);
extern u8 data_ov086_02279448[];
extern u8 data_ov086_02279438[];
extern int func_020154b4(void *, u16 *, int, int, int);
extern int func_0209a000(u16 *, int);
extern int func_0209a1e8(void);
extern int func_0209a1d0(void);
extern void *func_020a8228(void *);
extern void *func_020a8210(void *);
extern int func_020b4a20(void *, u8 *, int);
extern int func_0203d7c4(int, void *);
extern int func_02099870(int);
extern void func_02066024(int, u8 *, void *, void *, void *, int);
extern int func_0204bd20(int, int);
extern int func_020996ac(int);
extern int func_0203cd1c(int object, u16 *item, int mode);
extern void func_020860f0(int, int);
extern void func_0206844c(int, u8 *, void *);
extern char data_ov086_02279458;
extern char data_ov086_02279260;
extern char data_ov086_02279264;
extern UnkStruct_02278b24_2 data_ov086_022791d0[];
extern int func_020160b4(int);
extern int func_020ab504(int);
extern void func_0209a050(int);
extern int func_02015330(int, unsigned short *, int, int, int);

void func_ov086_02278cf0(UnkStruct_02278cf0 *self, UnkStruct_02278cf0_2 *out)
{
    Locals loc;
    unsigned int flag;

    func_02099640((int) func_020984e8());

    out->ptr = data_ov086_02279448;
    if (self->unk_B4 == -1) {
        loc.a = 0x37e0;
        self->unk_B4 = func_02099e9c(&loc.a);
        if (self->unk_B4 >= 0) {
            out->ptr = data_ov086_02279438;
            out->byte = 0;
            return;
        }
    }

    func_0209df64(loc.b);
    loc.c = 0;
    loc.d = 0;
    func_0209e474(&loc.c);
    flag = 0;

    if (loc.b[1] == 12) {
        if (func_0209dcac() == 0) {
            out->byte = func_020644cc(3);
        } else if (func_0209dcac() == 1) {
            out->byte = func_020644cc(3);
            if (out->byte != 0) {
                out->byte += 2;
            }
        } else if (((u8 *) &loc.c)[2] < 23) {
            out->byte = func_020644cc(3);
            if (out->byte != 0) {
                out->byte += 4;
            }
        } else if (((u8 *) &loc.c)[2] == 23 && ((u8 *) &loc.c)[1] < 30) {
            out->byte = func_020644cc(3);
            if (out->byte != 0) {
                out->byte += 6;
            }
        } else if (((u8 *) &loc.c)[2] == 23 && ((u8 *) &loc.c)[1] < 55) {
            out->byte = func_020644cc(3) + 9;
        } else if (((u8 *) &loc.c)[2] == 23 && ((u8 *) &loc.c)[1] < 59) {
            out->byte = func_020644cc(2) + 12;
            flag = 1;
        } else {
            out->byte = func_020644cc(2) + 14;
            flag = 1;
        }
    } else {
        if (((u8 *) &loc.c)[2] < 6) {
            out->byte = func_020644cc(3) + 16;
            flag = 1;
        } else if (func_02086108(func_0208602c(), 4) != 0) {
            out->byte = func_020644cc(3) + 22;
            flag = 1;
        } else {
            out->byte = 0x13;
            flag = 1;
        }
    }

    if (flag != 0) {
        return;
    }
    if (func_02099fe8() == -1) {
        return;
    }
    if (func_020644cc(2) != 0) {
        return;
    }
    out->byte = func_020644cc(3) + 25;
}

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
            func_0206844c(p->unk_40, &m.b1, ((char *) data_ov086_02279438));
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
        func_0206844c(p->unk_40, &m.b4, ((char *) data_ov086_02279448));
    }
}

void func_ov086_02278ab8(int arg0)
{
    int val;
    int cond;
    void *ptr;
    int s;
    int unused;
    void *g;
    struct {
        unsigned char c;
        unsigned short h;
        int pad;
    } st;
    val = func_020ab504(func_020160b4(arg0));
    s = 0xff;
    cond = *((int *) (((char *) arg0) + 0xb4));
    if (cond < 0) {
        return;
    }
    ptr = (void *) (((int *) data_ov086_02279438));
    g = ptr;
    if (((*((unsigned char *) (((char *) arg0) + 0x1e))) == 0) && (val == 0)) {
        if (cond >= 0) {
            func_0209a050(cond);
            st.h = 0x37e0;
            func_02015330(arg0, &st.h, 0, 5, 0);
        }
        s = 2;
    }
    if (s != 0xff) {
        st.c = (unsigned char) s;
        func_0206844c(*((int *) (((char *) arg0) + 0x40)), (u8 *) (&st), g);
    }
}
