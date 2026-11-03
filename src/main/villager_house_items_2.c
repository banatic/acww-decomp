/* villager_house_items_2: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207fbb4 @ 0x0207fbb4, 0x80 bytes, Thumb
 * func_0207fb98 @ 0x0207fb98, 0x1a bytes, Thumb
 * func_0207fb70 @ 0x0207fb70, 0x28 bytes, Thumb
 * func_0207fad0 @ 0x0207fad0, 0xa0 bytes, Thumb
 * func_0207fa3c @ 0x0207fa3c, 0x94 bytes, Thumb
 * func_0207f8a0 @ 0x0207f8a0, 0x19c bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x78c];
    unsigned short arr[1];
} UnkStruct_0207fbb4;

struct UnkStruct_0207fad0 {
    char pad_00[0x78c];
    unsigned short table[1];
};

extern int func_0207ffa0(UnkStruct_0207fbb4 *, int);
extern int func_0207fc34(UnkStruct_0207fbb4 *, unsigned short *, int);
extern int func_0207cc54(int, int, int);
extern unsigned short func_0203a6ec(unsigned short);
extern int func_020644cc(int);
extern int func_0207fe94(void *self, int *outx, int *outy, int arg1, int arg2, int arg3);
extern int func_0207fe28(void *self, int x, int y);
extern int func_0207fdbc(void *self, int x, int y);
extern unsigned int func_020535f0(unsigned short *p);
extern unsigned int func_0207f1c8(void *self);
extern void *func_0209b5e8(int);
extern void *func_0209b91c(void *);
extern int func_0204c878(u16 *p);
extern int func_0209bd44(void *h);
extern int func_0209bc40(void *h);
extern unsigned int func_0209b914(void *h);
extern unsigned int func_0209b8bc(void *h);

int func_0207fbb4(UnkStruct_0207fbb4 *arg0, int b, int c, int d)
{
    if (func_0207ffa0(arg0, c) != 0) {
        unsigned short *p = &arg0->arr[c];
        unsigned short mask = 0;
        int count = 0;
        while (c < d) {
            if (func_0207ffa0(arg0, c) != 0) {
                if (*p != 0xfff1) {
                    if (func_0207fc34(arg0, p, b) == 0) {
                        mask |= 1 << c;
                        count++;
                    }
                }
            }
            p++;
            c++;
        }
        return func_0207cc54(mask, count, 10);
    } else {
        return -1;
    }
}

int func_0207fb98(unsigned short *p)
{
    int r;
    r = func_0203a6ec(*p);
    if (r != 0) {
        return 1;
    } else {
        return 0;
    }
}

int func_0207fb70(unsigned short *arg)
{
    if (func_020644cc(2) == 0) {
        if ((int) func_0203a6ec(*arg) == 0) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return 1;
    }
}

int func_0207fad0(struct UnkStruct_0207fad0 *self, int arg1, int arg2, int arg3, unsigned char arg5)
{
    int x = 0, y = 0;

    if (func_0207fe94(self, &x, &y, arg1, arg2, arg3)) {
        int idx = func_0207fe28(self, x, y);
        if (idx == -1) {
            idx = func_0207fbb4((UnkStruct_0207fbb4 *) self, arg2, x, y);
            if (idx == -1) {
                if (arg5) {
                    idx = func_0207fdbc(self, x, y);
                }
            }
            if (idx != -1) {
                func_0207fb70((unsigned short *) (&self->table[idx]));
            }
        }
        if (idx != -1) {
            self->table[idx] = 0xfff1;
        }

        return idx;
    }

    return -1;
}

int func_0207fa3c(int unused, unsigned short *p)
{
    unsigned int i;
    unsigned short local;
    int flag;

    flag = (*p >= 0x450c && *p <= 0x45db);
    if (flag) {
        unsigned int ret = func_020535f0(p);
        if (ret < 24) {
            local = 0xfff1;
            for (i = 0; i < 52; i++) {
                local = (i < 52) ? 0x450c + i * 4 : 0x450c;
                if (func_020535f0(&local) == ret) {
                    flag = (*p >= 0x450c && *p <= 0x45db);
                    return (flag ? ((*p - 0x450c) >> 2) : -1) - (int) i;
                }
            }
        }
    }
    return -1;
}

int func_0207f8a0(void *self, u16 *p, int a2, int a3, u8 a5, u8 a6)
{
    int d;
    int z;
    void *h1;
    void *h2;
    int lo;
    int hi;
    unsigned int ok;
    unsigned int v;
    int n;
    int t;
    u16 *e;
    u16 *base;
    int m;

    ok = 0;
    v = *p;
    if (v >= 0x450c && v <= 0x45db) {
        ok = 1;
    }
    if (ok == 0) {
        goto fail;
    }
    if (a2 != 2) {
        goto fail;
    }
    lo = 0;
    hi = 0;
    if (func_0207fe94(self, &lo, &hi, a2, a3, a5) == 0) {
        goto fail;
    }
    d = hi - lo;
    t = func_0207fa3c((int) self, (unsigned short *) p);
    n = 0;
    if (t >= 0) {
        n = lo + (t % d);
    }
    if (func_0207ffa0((UnkStruct_0207fbb4 *) self, n) == 0) {
        goto fail;
    }
    base = (u16 *) ((char *) self + 0x78c);
    e = &base[n];
    if (base[n] == 0xfff1) {
        *e = *p;
        return 1;
    }
    z = func_0207fc34((UnkStruct_0207fbb4 *) self, (unsigned short *) e, a3);
    if (a6 != 0) {
        h1 = func_0209b5e8((int) func_0207f1c8(self));
        h2 = func_0209b91c((void *) h1);
        func_0204c878(p);
        func_0204c878(e);
        if (a3 == 2) {
            m = 0x18;
            if (func_0209bd44(h2) != 0 && func_0209bc40(h2) == 2 && func_0209b914(h1) >= 2 && func_0209b8bc(h1) < 0x18) {
                m = func_0209b8bc(h1);
            }
            if (m < 0x18) {
                if (m == (int) func_020535f0((unsigned short *) p)) {
                    func_0207fb70((unsigned short *) e);
                    *e = *p;
                    return 1;
                }
                if (z != 0) {
                    if (m == (int) func_020535f0((unsigned short *) e)) {
                        func_0207fb70((unsigned short *) p);
                        goto fail;
                    }
                    func_0207fb70((unsigned short *) e);
                    *e = *p;
                    return 1;
                }
                func_0207fb70((unsigned short *) e);
                *e = *p;
                return 1;
            }
            func_0207fb70((unsigned short *) e);
            *e = *p;
            return 1;
        }
        func_0207fb70((unsigned short *) e);
        *e = *p;
        return 1;
    }
    if (z != 0) {
        func_0207fb70((unsigned short *) p);
        goto fail;
    }
    func_0207fb70((unsigned short *) e);
    *e = *p;
    return 1;
fail:
    return 0;
}
