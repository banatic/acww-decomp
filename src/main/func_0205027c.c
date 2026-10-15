/* func_0205027c @ 0x0205027c, 0x118 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 unk_00[0x40];
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4C;
    u8 unk_50[0x98 - 0x50];
    int unk_98;
    u8 unk_9C[0x168 - 0x9c];
    u8 unk_168;
} UnkStruct_0205027c;

extern const char data_020dce90[];
extern const char data_020dcea8[];
extern const char data_020dcec0[];
extern const char data_020dced8[];

extern void *func_0209d238(void *, int *);
extern int func_02064328(char *, const char *, ...);
extern int func_0209d0ac(void *, void *, char *);
extern void *func_0209d088(void *);
extern int func_02055f2c(void *, void *, int);
extern void *func_0209d324(void *);
extern void *func_02064b2c(char *, void *, int, int);
extern int NNS_G3dGetJntAnmSet(int resource);
extern int func_02107b44(int, int);
extern int func_02055140(void *, void *);
extern void func_02055060(void *, int, int, int, int, int);
extern void func_02055050(void *);
extern void func_02050394(void *, UnkStruct_0205027c *);

int func_0205027c(void *p0, void *p1, UnkStruct_0205027c *s)
{
    int ret;
    void *a;
    void *c;
    void *q;
    char buf[0x18];
    int n;
    int t;
    void *r;
    int flags;

    ret = 0;
    if (p1 == 0 || s == 0) {
        return 0;
    }
    n = s->unk_40;
    a = func_0209d238(p1, &s->unk_48);
    q = &s->unk_4C;
    t = n / 0x10;
    if (n < 10) {
        func_02064328(buf, data_020dce90, t, n);
    } else {
        func_02064328(buf, data_020dcea8, t, n);
    }
    if (func_0209d0ac(q, a, buf)) {
        r = &s->unk_98;
        func_02055f2c(r, func_0209d088(q), 0);
        c = func_0209d324(a);
        if (n < 10) {
            func_02064328(buf, data_020dcec0, t, n);
        } else {
            func_02064328(buf, data_020dced8, t, n);
        }
        t = func_02107b44(NNS_G3dGetJntAnmSet((int) func_02064b2c(buf, c, 4, 0)), 0);
        flags = 0x1000;
        if (!s->unk_168) {
            flags = 0;
        }
        if (func_02055140(r, c)) {
            func_02055060(r, t, 0, flags, 1, 0);
            func_02055050(r);
            s->unk_44 = 3;
            func_02050394(p0, s);
            ret = 1;
        }
    }
    return ret;
}
