/* func_020739d0 @ 0x020739d0, 0x1b4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the empty if on len keeps the copy end a + sz + 5 in its register across the func_02073574 call setup */

#include "types.h"

typedef struct UnkStruct_020739d0 {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_020739d0;

extern void *data_020ccf94;

extern int func_02073918(UnkStruct_020739d0 *, int);
extern unsigned int func_02073950(UnkStruct_020739d0 *, int);
extern unsigned int func_02073bcc(UnkStruct_020739d0 *, int, unsigned int);
extern unsigned int func_02073c04(UnkStruct_020739d0 *, int, unsigned int);
extern void MI_CpuCopy8(unsigned int, int, int);
extern int func_0207762c(void);
extern void *func_020738bc(UnkStruct_020739d0 *, int);
extern void func_02077a34(u8 *, u8 *, u8 *);
extern int func_020b65c4(void);
extern int func_02077868(u8 *);
extern int func_020a72d0(int);
extern int func_0207356c(UnkStruct_020739d0 *);
extern int func_02073590(UnkStruct_020739d0 *);
extern void func_02073574(UnkStruct_020739d0 *, int);
extern int func_020a7278(void);
extern void func_02076168(int, unsigned int, int, int, int, int);
extern void func_020750fc(void);
extern void func_020750f4(void);
extern void func_02073b9c(void *, int, unsigned int);
extern void func_02073970(void *, int);
extern void func_02073c58(void *, int);

void func_020739d0(UnkStruct_020739d0 *self)
{
    int pass;
    unsigned int len;
    unsigned int n;
    int c;
    unsigned int q;
    int u;
    int w;
    unsigned int sz;
    void *g;
    unsigned int lim;
    int m;
    u8 buf[8];
    unsigned int i;
    unsigned int p;
    u16 k;
    int t;
    int a;
    int b;
    int d;

    pass = 2;
    g = data_020ccf94;
    do {
        for (i = 0; i < 4; i++) {
            if (func_02073918(self, i) != 0) {
                continue;
            }
            len = func_02073950(self, i);
            if (len >= 3) {
                continue;
            }
            n = func_02073bcc(self, i, len) - 1;
            p = func_02073c04(self, i, len) + 1;
            k = 0;
            do {
                MI_CpuCopy8(p, (int) &buf[0], 1);
                p = p + 1;
                k = (u16) (k + 1);
                c = buf[0];
                if (c >= 0x46) {
                    break;
                }
                m = func_0207762c();
                MI_CpuCopy8(p, (int) func_020738bc(self, c), m);
                p = p + m;
                k = (u16) (k + m);
            } while (k < n);
            q = 0;
            lim = (u16) (n - k);
            while (q < lim) {
                MI_CpuCopy8(p, (int) &buf[3], 5);
                p = p + 5;
                q = q + 5;
                t = buf[6];
                func_02077a34(&buf[7], &buf[1], &buf[2]);
                u = buf[2];
                w = func_020b65c4();
                sz = func_02077868(&buf[3]);
                if (func_020a72d0(self->unk_64) != 0 && t == 7 && buf[1] != w) {
                    a = func_0207356c(self);
                    b = func_02073590(self);
                    b += a;
                    MI_CpuCopy8(p - 5, b, sz + 5);
                    d = a + (sz + 5);
                    if (!len && !len) {
                    }
                    func_02073574(self, d);
                } else {
                    if (func_020a7278() == 0 && t == 6) {
                        goto skip;
                    }
                    if (t == 6 && buf[1] != w) {
                        goto skip;
                    }
                    if (t == 7 && buf[1] != w) {
                        goto skip;
                    }
                    func_02076168(buf[5], p, sz, t, buf[1], u);
                }
            skip:
                p = p + sz;
                q = q + sz;
            }
            func_020750fc();
            func_02073b9c(g, i, len);
            func_02073970(g, i);
            func_02073c58(g, i);
            func_020750f4();
        }
        pass = pass - 1;
    } while (pass >= 0);
}
