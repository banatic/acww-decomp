/* func_ov084_02278c18 @ 0x02278c18, 0x1d4 bytes, Thumb, module ov084
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned short unk_02;
    unsigned short unk_04;
    unsigned short unk_06;
    unsigned short unk_08;
    unsigned short unk_0A;
    unsigned short unk_0C;
    unsigned short unk_0E;
} Msg;

typedef struct UnkStruct_02278c18 UnkStruct_02278c18;
struct UnkStruct_02278c18 {
    char pad_00[0x1e];
    unsigned char unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
    char pad_44[0xb4 - 0x44];
    int unk_B4;
};

extern int data_ov084_02279558;
extern int data_ov084_02279568;
extern void func_020154b4(UnkStruct_02278c18 *p, void *m, int a, int b, int c);
extern void func_0209a000(unsigned short *h, int a);
extern void func_0206844c(int a, void *m, int *t);
extern int func_02099fe8(UnkStruct_02278c18 *p);
extern int func_02099e9c(unsigned short *h);
extern int func_020644cc(int a);
extern int func_020984e8(void);
extern int func_02099670(int a);
extern unsigned int func_02088b14(int a);
extern void func_02088ad4(int a);
extern int func_02099870(int a);
extern int func_020950c0(int a);
extern void func_02015de4(UnkStruct_02278c18 *p, void *m, int a, int b);

void func_ov084_02278c18(UnkStruct_02278c18 *p)
{
    Msg msg;
    int res, n, t, m;
    int *tbl;

    tbl = &data_ov084_02279558;
    res = 0xff;
    if (p->unk_B4 >= 0) {
        if (p->unk_1E == 1 || p->unk_1E == 4) {
            p->unk_B4 = -2;
        }
        if (p->unk_1E != 2) {
            return;
        }
        msg.unk_04 = 0x1559;
        func_020154b4(p, &msg.unk_04, 0, 5, 0);
        msg.unk_06 = 0x1559;
        func_0209a000(&msg.unk_06, 0);
        msg.unk_00 = 4;
        func_0206844c(p->unk_40, &msg, &data_ov084_02279568);
        return;
    }
    switch (p->unk_1E) {
        case 0:
        case 1:
        case 2:
        case 6:
            n = func_02099fe8(p);
            msg.unk_02 = 0xfff1;
            msg.unk_08 = 0x137e;
            m = func_02099e9c(&msg.unk_08);
            t = 0;
            if (m == -1) {
                t = 1;
            }
            if (t != 0) {
                msg.unk_0A = 0x137f;
                m = func_02099e9c(&msg.unk_0A);
                t = 0;
                if (m == -1) {
                    t = 1;
                }
                if (t != 0) {
                    msg.unk_02 = 0x137e;
                    if (func_020644cc(2) == 0) {
                        msg.unk_02 = 0x137f;
                    }
                    goto joined;
                }
            }
            msg.unk_0C = 0x137e;
            m = func_02099e9c(&msg.unk_0C);
            t = 0;
            if (m == -1) {
                t = 1;
            }
            if (t != 0) {
                msg.unk_02 = 0x137e;
            } else {
                msg.unk_02 = 0x137f;
            }
        joined:
            if (n >= 0) {
                n = func_02099670(func_020984e8());
                if (func_02088b14(n) < 0xa) {
                    func_02088ad4(n);
                    n = func_020950c0(func_02099870(func_020984e8()));
                    func_020154b4(p, &msg.unk_02, 0, 5, 0);
                    func_0209a000(&msg.unk_02, 0);
                    func_02015de4(p, &msg.unk_02, 0, 7);
                    if (n == 0) {
                        res = 3;
                    } else {
                        res = 4;
                    }
                } else {
                    res = 0xb;
                }
            } else {
                func_02015de4(p, &msg.unk_02, 0, 7);
                res = 5;
            }
            break;
        case 9:
            msg.unk_0E = 0x1565;
            func_020154b4(p, &msg.unk_0E, 0, 5, 0);
            res = 0xa;
            break;
    }
    if (res == 0xff) {
        return;
    }
    msg.unk_01 = (unsigned char) res;
    func_0206844c(p->unk_40, &msg.unk_01, tbl);
}
