/* event_winner: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020865d8 @ 0x020865d8, 0xe0 bytes, Thumb
 * func_02086564 @ 0x02086564, 0x74 bytes, Thumb
 * func_020864f4 @ 0x020864f4, 0x70 bytes, Thumb
 * func_020864cc @ 0x020864cc, 0x26 bytes, Thumb
 * func_0208642c @ 0x0208642c, 0xa0 bytes, Thumb
 * func_020863dc @ 0x020863dc, 0x50 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x44];
    unsigned char unk_44;
    unsigned char pad_45;
    unsigned char unk_46;
} UnkStruct_020865d8;

typedef struct {
    u16 unk_00;
} Entry;

typedef struct {
    int dx;
    int dz;
} Off;

struct Arg {
    int x;
    int y;
};

struct Pair {
    int x;
    int y;
};

extern void func_0209df64(void *);
extern int func_0203fdc4(int);
extern int func_0209dcdc(void *, void *);
extern void *func_02098844(void *, int);
extern int func_02099a28(unsigned int);
extern int func_02099670(void *);
extern void func_02088ac0(unsigned char *);
extern void func_02088aa0(void *);
extern void func_02098fd0(void *, int);
extern void func_0209f100(void *, int);
extern void func_0208683c(void *);
extern unsigned char data_021dc7a8[];
extern unsigned char data_021dc7bc[];
extern int func_020644b4(int);
extern int func_0204c380(unsigned short *);
extern int func_0204c308(unsigned short *);
extern int FX_MulFunc(int, int);
extern void *func_0208150c(void *a);
extern int func_02003704(void *a);
extern u8 *func_020800d0(void *a);
extern Entry *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern const Off data_021d2820[];
extern struct Pair data_021d27e0[8];
extern int func_02034240(void *out, int a, int b, int c, int d);
extern void func_0203423c(void *buf);

void func_020865d8(UnkStruct_020865d8 *obj, int selector)
{
    unsigned char tmp[4];
    int val;
    int ret;
    int i;

    func_0209df64(tmp);

    val = 0;
    switch (selector) {
        case 0:
            val = func_0203fdc4(0xe);
            break;
        case 1:
            val = func_0203fdc4(0x11);
            break;
        case 2:
            val = func_0203fdc4(0x10);
            break;
    }

    ret = func_0209dcdc(tmp, &obj->unk_44);

    if (tmp[2] != obj->unk_46) {
        goto FAIL;
    }
    if (val == -1) {
        goto FAIL;
    }
    if (ret > 7) {
        goto FAIL;
    }
    if (ret < 0) {
        goto FAIL;
    }
    if ((tmp[0] - val) <= obj->unk_44) {
        return;
    }

FAIL:
    switch (selector) {
        case 1:
            func_0209f100((void *) data_021dc7a8, 0x11);
            break;
        case 0:
        case 2:
            i = 0;
            do {
                void *p = func_02098844((void *) data_021dc7bc, i);
                if (p != 0 && func_02099a28((unsigned int) p) != 0) {
                    if (selector == 2) {
                        func_02088ac0((unsigned char *) func_02099670(p));
                        func_02098fd0(p, 0xf);
                    } else {
                        func_02088aa0((void *) func_02099670(p));
                    }
                }
                i++;
            } while (i < 4);
            break;
        default:
            break;
    }

    func_0208683c(obj);
}

int func_02086564(unsigned short *ptr)
{
    int result = 0;
    int base = func_020644b4(0x666) + 0xccd;
    int inFirst = 0;
    unsigned short val = *ptr;

    if (val >= 0x12e8 && val <= 0x131f) {
        inFirst = 1;
    }

    if (inFirst) {
        result = FX_MulFunc((func_0204c380(ptr) << 12), base);
    } else if (val >= 0x12b0 && val <= 0x12e7) {
        result = FX_MulFunc((func_0204c308(ptr) << 12), base);
    }

    return result;
}

int func_020864f4(int *out, unsigned short *in)
{
    int r6 = 1;
    int r5 = r6;
    int r4 = r6;
    int r3 = 0;
    unsigned short v = *in;

    if (v <= 5) {
        r3 = 1;
    }
    if (!r3) {
        if (v < 6 || v > 11) {
            r4 = 0;
        }
    }
    if (!r4) {
        if (v < 12 || v > 17) {
            r5 = 0;
        }
    }
    if (!r5) {
        if ((v < 18 || v > 25) && v != 28) {
            r6 = 0;
        }
    }

    if (r6 || v == 26 || (unsigned short) (v + 0xFFE3) <= 1) {
        if (v > 27) {
            *out = v - 1;
        } else {
            *out = v;
        }
        return 1;
    } else {
        return 0;
    }
}

int func_020864cc(unsigned int x)
{
    int count;
    int i;

    count = 0;
    if (x != 0) {
        i = count;
        do {
            if ((x >> i) & 1) {
                count++;
            }
            i++;
        } while (i < 32);
    }
    return count;
}

int func_0208642c(void *a, void *ctx)
{
    int result;
    void *tmp;
    const Off *t;
    int i;
    int count;
    unsigned int mask;
    int x, z, cx, cz;
    Entry *e;
    unsigned int out;
    u8 *p;

    tmp = func_0208150c(a);
    result = 0;
    if (func_02003704(tmp) != 0) {
        mask = 0;
        p = func_020800d0(a);
        x = p[0];
        z = p[1];
        t = data_021d2820;
        count = 0;
        out = 0;
        for (i = 0; i < 14; i++) {
            int wx = x + t->dx;
            int wz = z + t->dz;
            cx = wx >> 4;
            cz = wz >> 4;
            e = func_0204f5e0(ctx, cx, cz, wx - (cx << 4), wz - (cz << 4), 0);
            out = 0;
            if (e != 0) {
                if (func_020864f4((int *) (&out), (unsigned short *) e) != 0) {
                    if (out < 0x20) {
                        mask |= 1 << out;
                    }
                    count++;
                }
            }
            t++;
        }
        result = func_020864cc(mask);
        result = count * result;
    }
    return result;
}

int func_020863dc(struct Arg *arg)
{
    struct Pair *p;
    int i;
    char buf[64];

    p = data_021d27e0;
    i = 0;
    while (i < 8) {
        func_02034240(buf, arg->x + p->x, arg->y + p->y, 0, 0);
        if (*(int *) (buf + 52) == 4) {
            func_0203423c(buf);
            return 1;
        }
        p++;
        func_0203423c(buf);
        i++;
    }
    return 0;
}
