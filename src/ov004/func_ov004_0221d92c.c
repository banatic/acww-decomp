/* func_ov004_0221d92c @ 0x0221d92c, 0x2ec bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off
extern void *func_ov004_0221d4e8(void);
extern int func_020ea990(void *a, void *b);
extern int data_020ca0ec;
extern int func_02019e00(void *p);
extern int func_02019c6c(void *p, int a, int b);
extern int func_ov004_0221dd24(void *self, int k);
extern int func_ov004_0221e1e0(void *a, void *b, int c);
extern int func_020644cc(int k);
extern int func_020e8ed8(int a, int b);
extern int func_020e8b4c(int a, int b);
extern int func_02019d0c(void *p, int a, int b, int c4, int c5, int c6, int c7, int c8, int c9, int c10, int c11);
extern int func_02019de8(void *p);
extern int func_0201c194(void *self, int *t);
extern void func_0201b044(void *p, void *position);
extern int func_020eaa2c(void *a, void *b);
extern unsigned short data_020c80f8;

void func_ov004_0221d92c(void *self)
{
    int t[3];
    void *o;
    int d;
    unsigned short *p1;
    int *w;
    unsigned short *p2;

    o = func_ov004_0221d4e8();
    if (o != 0) {
        d = func_020ea990((char *) o + 0x5c, (char *) self + 0x5c);
    } else {
        d = data_020ca0ec;
    }
    if (*(unsigned short *) ((char *) self + 0xa4e) != 0) {
        *(unsigned short *) ((char *) self + 0xa4e) = *(unsigned short *) ((char *) self + 0xa4e) - 1;
    }
    if (*((unsigned char *) self + 0x508) != 0 && func_02019e00((char *) self + 0x564) == 1) {
        if (func_02019c6c((char *) self + 0x564, 1, data_020c80f8) != 0) {
            return;
        }
    }
    if (d < 0x3334) {
        if (func_ov004_0221dd24(self, 1) != 0) {
            return;
        }
    }
    if (func_02019e00((char *) self + 0x564) == 0) {
        if (*(unsigned short *) ((char *) self + 0xa52) != 0) {
            *(unsigned short *) ((char *) self + 0xa52) = *(unsigned short *) ((char *) self + 0xa52) - 1;
        }
        if (*(unsigned short *) ((char *) self + 0xa52) == 0) {
            *(short *) ((char *) self + 0xa50) =
                (short) func_ov004_0221e1e0((char *) self + 0xa60, (char *) self + 0x5c, *(short *) ((char *) self + 0x8e));
            *(int *) ((char *) self + 0xa54) = *(int *) ((char *) self + 0xa60);
            *(int *) ((char *) self + 0xa58) = *(int *) ((char *) self + 0xa64);
            *(int *) ((char *) self + 0xa5c) = *(int *) ((char *) self + 0xa68);
            if (o != 0 && d >= 0x6000 && func_020644cc(2) == 0) {
                int *q;
                int *s;
                int v0;
                int a;
                d = func_020e8ed8(*(int *) ((char *) o + 0x5c) - *(int *) ((char *) self + 0x5c),
                                  *(int *) ((char *) o + 0x64) - *(int *) ((char *) self + 0x64));
                a = func_020e8b4c(*(short *) ((char *) self + 0x8e), d);
                s = (int *) ((char *) o + 0x5c);
                v0 = s[0];
                q = (int *) ((char *) self + 0xa60);
                q[0] = v0;
                *(int *) ((char *) self + 0xa64) = s[1];
                *(int *) ((char *) self + 0xa68) = s[2];
                *(int *) ((char *) self + 0xa54) = q[0];
                *(int *) ((char *) self + 0xa58) = q[1];
                *(int *) ((char *) self + 0xa5c) = q[2];
                if (a >= 0x2000) {
                    *(short *) ((char *) self + 0xa50) = (short) d;
                }
            }
            if (*(short *) ((char *) self + 0xa50) != *(short *) ((char *) self + 0x8e)) {
                if (func_02019d0c((char *) self + 0x564, 3, 1, 0, 0, 0, *(short *) ((char *) self + 0xa50), 0, 0,
                                  data_020c80f8, 0) == 0) {
                    return;
                }
                *(short *) ((char *) self + 0xa52) = (short) (func_020644cc(0x46) + 0x14);
            } else {
                if (func_02019d0c((char *) self + 0x564, 1, 1, *(int *) ((char *) self + 0xa60),
                                  *(int *) ((char *) self + 0xa68), 0, 0, 0, 0, data_020c80f8, 0) == 0) {
                    return;
                }
                *(short *) ((char *) self + 0xa52) = (short) (func_020644cc(0x50) + 0x14);
            }
        } else {
            if (func_02019de8((char *) self + 0x564) != 0) {
                func_02019c6c((char *) self + 0x564, 1, data_020c80f8);
            }
        }
    } else if (func_02019e00((char *) self + 0x564) == 3) {
        if (func_02019de8((char *) self + 0x564) != 0) {
            func_02019d0c((char *) self + 0x564, 1, 1, *(int *) ((char *) self + 0xa60), *(int *) ((char *) self + 0xa68), 0,
                          0, 0, 0, data_020c80f8, 0);
        }
    } else if (func_02019e00((char *) self + 0x564) == 1) {
        switch (func_0201c194(self, t)) {
            case 1:
                func_02019c6c((char *) self + 0x564, 1, data_020c80f8);
                break;
            case 2: {
                int first = t[0];
                w = (int *) ((int) self + 0xa54);
                *w = first;
                *(int *) ((char *) self + 0xa58) = t[1];
                *(int *) ((char *) self + 0xa5c) = t[2];
                func_0201b044((char *) self + 0x350, w);
                break;
            }
            default:
                if (func_020eaa2c((char *) self + 0xa54, (char *) self + 0xa60) != 0) {
                    int *r = (int *) ((int) self + 0xa60);
                    *(int *) ((char *) self + 0xa54) = *r;
                    *(int *) ((char *) self + 0xa58) = *(int *) ((char *) self + 0xa64);
                    *(int *) ((char *) self + 0xa5c) = *(int *) ((char *) self + 0xa68);
                    func_0201b044((char *) self + 0x350, r);
                } else if (func_020ea990((char *) self + 0xa60, (char *) self + 0x5c) < 0x200) {
                    func_02019c6c((char *) self + 0x564, 1, data_020c80f8);
                }
                break;
        }
    }
}
