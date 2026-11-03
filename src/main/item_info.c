/* item_info: 43 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02062d7c @ 0x02062d7c, 0x28 bytes, Thumb
 * func_02062d44 @ 0x02062d44, 0x36 bytes, Thumb
 * func_02062cbc @ 0x02062cbc, 0x88 bytes, Thumb
 * func_02062ca4 @ 0x02062ca4, 0x16 bytes, Thumb
 * func_02062c9c @ 0x02062c9c, 0x8 bytes, Thumb
 * func_02062c94 @ 0x02062c94, 0x8 bytes, Thumb
 * func_02062c0c @ 0x02062c0c, 0x88 bytes, Thumb
 * func_02062b98 @ 0x02062b98, 0x74 bytes, Thumb
 * func_02062b18 @ 0x02062b18, 0x80 bytes, Thumb
 * func_02062b14 @ 0x02062b14, 0x4 bytes, Thumb
 * func_02062b04 @ 0x02062b04, 0x10 bytes, Thumb
 * func_02062af4 @ 0x02062af4, 0x10 bytes, Thumb
 * func_02062ae4 @ 0x02062ae4, 0x10 bytes, Thumb
 * func_02062ad4 @ 0x02062ad4, 0x10 bytes, Thumb
 * func_02062a28 @ 0x02062a28, 0xac bytes, Thumb
 * func_020629ec @ 0x020629ec, 0x3c bytes, Thumb
 * func_020629e4 @ 0x020629e4, 0x6 bytes, Thumb
 * func_020629dc @ 0x020629dc, 0x6 bytes, Thumb
 * func_020629d4 @ 0x020629d4, 0x6 bytes, Thumb
 * func_02062998 @ 0x02062998, 0x3c bytes, Thumb
 * func_020628ac @ 0x020628ac, 0xec bytes, Thumb
 * func_02062870 @ 0x02062870, 0x3c bytes, Thumb
 * func_020627bc @ 0x020627bc, 0xb4 bytes, Thumb
 * func_02062780 @ 0x02062780, 0x3c bytes, Thumb
 * func_02062734 @ 0x02062734, 0x4c bytes, Thumb
 * func_0206266c @ 0x0206266c, 0xc8 bytes, Thumb
 * func_020625a0 @ 0x020625a0, 0xcc bytes, Thumb
 * func_020624d4 @ 0x020624d4, 0xcc bytes, Thumb
 * func_02062408 @ 0x02062408, 0xcc bytes, Thumb
 * func_0206233c @ 0x0206233c, 0xcc bytes, Thumb
 * func_02062300 @ 0x02062300, 0x3c bytes, Thumb
 * func_020622c4 @ 0x020622c4, 0x3c bytes, Thumb
 * func_020622a0 @ 0x020622a0, 0x24 bytes, Thumb
 * func_02062280 @ 0x02062280, 0x20 bytes, Thumb
 * func_0206226c @ 0x0206226c, 0x14 bytes, Thumb
 * func_0206223c @ 0x0206223c, 0x30 bytes, Thumb
 * func_02062230 @ 0x02062230, 0xc bytes, Thumb
 * func_020621d4 @ 0x020621d4, 0x5c bytes, Thumb
 * func_02062148 @ 0x02062148, 0x8c bytes, Thumb
 * func_0206213c @ 0x0206213c, 0xc bytes, Thumb
 * func_02062130 @ 0x02062130, 0xc bytes, Thumb
 * func_02062124 @ 0x02062124, 0xc bytes, Thumb
 * func_02062118 @ 0x02062118, 0xc bytes, Thumb
 */

#include "types.h"

typedef struct {
    char data[0x1c];
} UnkStruct_02062d7c;

extern void func_0206e8c4(void *);
extern void func_0206e71c(void *);
extern void func_0206e808(void *);
extern int func_0206e8b4(void *);
extern int data_021cb5c0;
extern char data_020de5b0;
extern char data_020de5c8;
extern char data_020de5e0;
extern char data_020de5f4;
extern int func_0206e73c(void *, void *, int, void *, int, void *, int, int);
extern int func_0206e890(void *, void *, int, int);
extern void func_0206e854(void *);
extern int func_0206e704(void *, int);
extern int func_0206e6f0(void *);
extern unsigned short data_021cb5b0;
extern int func_0204bcdc(unsigned short *p);
extern int func_0204bc64(unsigned short *p);
extern int func_0204be38(const unsigned short *);
extern int func_0204bd84(const unsigned short *);
extern int data_021cb5b4;
extern int data_021cb5b8;
extern int data_021cb5bc;
extern int data_021cb5c4;
extern unsigned char data_021cb5e0[];
extern int func_0206e6e4(int p0);
extern void *func_0206e7bc(void *a, unsigned int i);
extern void *func_0206e6ec(void *);
extern void *func_0206e6e8(void *ptr);
extern char data_021cb634;
extern unsigned short data_020cca34[];
extern int data_020de368[][2];

void func_02062c0c(void);
void func_02062b98(void);
void func_02062b18(void);
int func_020627bc(unsigned short *ptr);
int func_0206266c(unsigned short *p);

UnkStruct_02062d7c *func_02062d7c(UnkStruct_02062d7c *self)
{
    func_0206e8c4(&self[0]);
    func_0206e8c4(&self[1]);
    func_0206e8c4(&self[2]);
    func_0206e8c4(&self[3]);
    return self;
}

void *func_02062d44(void *p)
{
    func_0206e71c(p);
    func_0206e808((char *) p + 0x54);
    func_0206e8b4((char *) p + 0x54);
    func_0206e8b4((char *) p + 0x38);
    func_0206e8b4((char *) p + 0x1c);
    func_0206e8b4(p);
    return p;
}

int func_02062cbc(void *ptr)
{
    int flag, result;

    data_021cb5c0 = 0;

    result = func_0206e73c(ptr, &data_020de5b0, 12, &data_020de5c8, 4, &data_020de5e0, 0x18, 0x600);

    flag = 1;
    if ((result | flag) == 0) {
        flag = 0;
    }

    if (flag) {
        func_02062c0c();
        func_02062b98();
        func_02062b18();
    }

    result = func_0206e890((char *) ptr + 0x54, &data_020de5f4, 0x18, 0x80);

    flag = (flag | result) ? 1 : 0;

    if (flag) {
        func_0206e854((char *) ptr + 0x54);
    }

    return flag;
}

void func_02062ca4(void *arg0)
{
    void *r4;
    r4 = arg0;
    func_0206e71c(r4);
    r4 = (char *) r4 + 0x54;
    func_0206e808(r4);
}

void func_02062c9c(void *argument0, int argument1)
{
    func_0206e704((void *) argument0, (int) argument1);
}

int func_02062c94(void *argument0)
{
    return func_0206e6f0((void *) argument0);
}

void func_02062c0c(void)
{
    unsigned short i;
    struct {
        unsigned short a;
        unsigned short b;
    } local;
    int flag;

    for (i = 0x1000; i < 0x156e; i++) {
        local.a = i;
        if (func_0206266c((unsigned short *) (&local)) == 0) {
            continue;
        }

        if (func_0204bcdc(&data_021cb5b0) != 0) {
            local.b = 0xfff1;
            if (func_0204bc64(&data_021cb5b0) == func_0204bc64(&local.b)) {
                flag = 1;
            } else {
                flag = 0;
            }
        } else {
            if (data_021cb5b0 == 0xfff1) {
                flag = 1;
            } else {
                flag = 0;
            }
        }

        if (flag != 0) {
            data_021cb5b0 = local.a;
        }
        data_021cb5c0++;
    }
}

void func_02062b98(void)
{
    unsigned short local[2];
    unsigned i = 0;

    for (; i < 0x21; i++) {
        local[0] = (i < 0x21) ? (unsigned short) (i + 0x1408) : (unsigned short) 0x1408;
        local[1] = (i < 0x21) ? (unsigned short) (i + 0x1471) : (unsigned short) 0x1471;

        if (func_0204be38(local)) {
            data_021cb5b4++;
        } else {
            if (func_0204bd84(&local[1])) {
                data_021cb5b8++;
            }
        }
    }
}

void func_02062b18(void)
{
    unsigned short data[2];
    unsigned int i;

    data_021cb5bc = 0;
    data_021cb5c4 = 0;

    for (i = 0; i < 0x40; i++) {
        data[0] = (i < 0x40) ? (unsigned short) (i + 0x13c8) : 0x13c8;
        if ((unsigned int) func_020627bc(data) == 0x1d) {
            data_021cb5c4++;
        }
    }

    for (i = 0; i < 0x20; i++) {
        data[1] = (i < 0x20) ? (unsigned short) (i + 0x13a8) : 0x13a8;
        if ((unsigned int) func_020627bc(&data[1]) == 0x1d) {
            data_021cb5bc++;
        }
    }
}

int func_02062b14(void)
{
    return 0;
}

void func_02062b04(void)
{
    func_02062cbc((void *) ((int) ((int *) data_021cb5e0)));
}

void func_02062af4(void)
{
    func_02062ca4((void *) data_021cb5e0);
}

void func_02062ae4(int p0)
{
    func_02062c9c((void *) ((int) ((int *) data_021cb5e0)), p0);
}

int func_02062ad4(void)
{
    return func_02062c94((void *) ((unsigned int) data_021cb5e0));
}

void *func_02062a28(unsigned short *param)
{
    int flag = 0;
    unsigned short v = *param;
    int t;
    unsigned short w;
    int val;
    unsigned int u;
    void *p;
    void *ret;

    if ((unsigned int) v >= 0x1000 && (unsigned int) v <= 0x10ff) {
        flag = 1;
    }
    if (flag != 0) {
        if ((unsigned int) v >= 0x1000 && (unsigned int) v <= 0x10ff) {
            t = v - 0x1000;
        } else {
            t = -1;
        }
        t |= 3;
        if ((unsigned int) t < 0x100) {
            val = (unsigned short) (t + 0x1000);
        } else {
            val = 0x1000;
        }
        w = val;
        u = *(volatile unsigned short *) &w & 0xfff;
        if (u >= 0x56e) {
            u = 0x56d;
        }
        p = (void *) func_0206e6e4((int) (unsigned int) data_021cb5e0);
        ret = func_0206e7bc(p, u);
        if (ret != 0) {
            return ret;
        }
        return 0;
    } else {
        u = v & 0xfff;
        if (u >= 0x56e) {
            u = 0x56d;
        }
        p = (void *) func_0206e6e4((int) (unsigned int) data_021cb5e0);
        ret = func_0206e7bc(p, u);
        if (ret != 0) {
            return ret;
        }
        return 0;
    }
}

unsigned short func_020629ec(void *param)
{
    void *p;
    void *ret;
    unsigned int val;

    val = *(unsigned short *) param & 0x0fff;
    if (val >= 0x56e) {
        val = 0x56d;
    }
    p = func_0206e6ec((void *) data_021cb5e0);
    ret = func_0206e7bc(p, val);
    if (ret != 0) {
        return *(unsigned short *) ((unsigned char *) ret + 2);
    }
    return 0;
}

int func_020629e4(void *receiver)
{
    return -1;
}

int func_020629dc(void *receiver)
{
    return -1;
}

int func_020629d4(void *receiver)
{
    return -1;
}

unsigned char func_02062998(void *ptr)
{
    unsigned int v;
    void *p;
    void *q;

    v = (*(unsigned short *) ptr) & 0xFFF;
    if (v >= 0x56e) {
        v = 0x56d;
    }
    p = func_0206e6ec((void *) data_021cb5e0);
    q = func_0206e7bc(p, v);
    if (q) {
        return ((unsigned char *) q)[5];
    }
    return 0;
}

int func_020628ac(u16 *p)
{
    u16 v;
    int cond;
    int d;
    volatile u16 t;
    unsigned int idx;
    u16 *e;
    int r;
    u16 w;
    int cond2;
    int d2;

    cond = 0;
    v = *p;
    if (v >= 0x1000 && v <= 0x10ff) {
        cond = 1;
    }
    if (cond != 0) {
        if (v >= 0x1000 && v <= 0x10ff) {
            d = v - 0x1000;
        } else {
            d = -1;
        }
        d |= 3;
        t = ((unsigned int) d < 0x100) ? (u16) (d + 0x1000) : 0x1000;
        idx = t & 0xfff;
        if (idx >= 0x56e) {
            idx = 0x56d;
        }
        e = (u16 *) func_0206e7bc(func_0206e6ec(((int *) data_021cb5e0)), idx);
        if (e != 0) {
            r = *e;
        } else {
            r = 0;
        }
    } else {
        idx = v & 0xfff;
        if (idx >= 0x56e) {
            idx = 0x56d;
        }
        e = (u16 *) func_0206e7bc(func_0206e6ec(((int *) data_021cb5e0)), idx);
        if (e != 0) {
            r = *e;
        } else {
            r = 0;
        }
    }
    cond2 = 0;
    w = *p;
    if (w >= 0x1000 && w <= 0x10ff) {
        cond2 = 1;
    }
    if (cond2 != 0) {
        if (w >= 0x1000 && w <= 0x10ff) {
            d2 = w - 0x1000;
        } else {
            d2 = -1;
        }
        d2 &= 3;
        r = (u16) ((r * (d2 + 1)) >> 2);
    }
    return r;
}

unsigned char func_02062870(unsigned short *param)
{
    unsigned int mask_val;
    unsigned char *result;

    mask_val = *param & 0xfff;
    if (mask_val >= 0x56e) {
        mask_val = 0x56d;
    }

    result = (unsigned char *) func_0206e7bc(func_0206e6ec((void *) data_021cb5e0), mask_val);
    if (result != 0) {
        return result[4];
    } else {
        return 0;
    }
}

int func_020627bc(unsigned short *ptr)
{
    int key = 0;
    unsigned int v = *ptr;
    unsigned int flags;
    int ret;
    void *p;
    void *q;

    if ((unsigned int) v >= 0x1000 && (unsigned int) v <= 0x10ff) {
        key = 1;
    }

    if (key != 0) {
        if ((unsigned int) v >= 0x1000 && (unsigned int) v <= 0x10ff) {
            key = v - 0x1000;
        } else {
            key = -1;
        }
        key |= 3;
        if ((unsigned int) key < 0x100) {
            key = (unsigned short) (key + 0x1000);
        } else {
            key = 0x1000;
        }
        {
            volatile unsigned short temp = (unsigned short) key;
            flags = temp & 0x0fff;
        }
        if (flags >= 0x056e) {
            flags = 0x056d;
        }
        p = func_0206e6ec((void *) data_021cb5e0);
        q = func_0206e7bc(p, flags);
        if (q) {
            ret = ((unsigned char *) q)[6];
        } else {
            ret = 0;
        }
    } else {
        flags = v & 0x0fff;
        if (flags >= 0x056e) {
            flags = 0x056d;
        }
        p = func_0206e6ec((void *) data_021cb5e0);
        q = func_0206e7bc(p, flags);
        if (q) {
            ret = ((unsigned char *) q)[6];
        } else {
            ret = 0;
        }
    }
    return ret;
}

unsigned char func_02062780(unsigned short *src)
{
    unsigned int val;
    void *p;
    unsigned char *q;

    val = *src & 0xFFF;
    if (val >= 0x56E) {
        val = 0x56D;
    }
    p = func_0206e6ec(((unsigned int *) data_021cb5e0));
    q = (unsigned char *) func_0206e7bc(p, val);
    if (q != 0) {
        return q[7];
    }
    return 0;
}

int func_02062734(unsigned short *arg)
{
    unsigned int val;
    void *p, *q;
    if ((int) func_02062870(arg) == 5) {
        val = *arg & 0xfff;
        if (val >= 0x56e) {
            val = 0x56d;
        }
        p = func_0206e6ec((void *) data_021cb5e0);
        q = func_0206e7bc(p, val);
        if (q) {
            return ((unsigned char *) q)[8];
        }
        return 0;
    }
    return -1;
}

int func_0206266c(unsigned short *p)
{
    unsigned short v;
    int cond;
    int d;
    volatile unsigned short t;
    unsigned int idx;
    unsigned char *e;

    cond = 0;
    v = *p;
    if (v >= 0x1000 && v <= 0x10ff) {
        cond = 1;
    }

    if (cond != 0) {
        if (v >= 0x1000 && v <= 0x10ff) {
            d = v - 0x1000;
        } else {
            d = -1;
        }
        d |= 3;
        t = ((unsigned int) d < 0x100) ? (unsigned short) (d + 0x1000) : 0x1000;
        idx = t & 0xfff;
        if (idx >= 0x56e) {
            idx = 0x56d;
        }
        e = (unsigned char *) func_0206e7bc(func_0206e6ec(((int *) data_021cb5e0)), idx);
        if (e != 0) {
            if ((e[9] & 1) != 0) {
                return 1;
            }
            return 0;
        }
        return 0;
    } else {
        idx = v & 0xfff;
        if (idx >= 0x56e) {
            idx = 0x56d;
        }
        e = (unsigned char *) func_0206e7bc(func_0206e6ec(((int *) data_021cb5e0)), idx);
        if (e != 0) {
            if ((e[9] & 1) != 0) {
                return 1;
            }
            return 0;
        }
        return 0;
    }
}

int func_020625a0(unsigned short *p)
{
    unsigned short v;
    int cond;
    int d;
    volatile unsigned short t;
    unsigned int idx;
    unsigned char *e;

    cond = 0;
    v = *p;
    if (v >= 0x1000 && v <= 0x10ff) {
        cond = 1;
    }

    if (cond != 0) {
        if (v >= 0x1000 && v <= 0x10ff) {
            d = v - 0x1000;
        } else {
            d = -1;
        }
        d |= 3;
        t = ((unsigned int) d < 0x100) ? (unsigned short) (d + 0x1000) : 0x1000;
        idx = t & 0xfff;
        if (idx >= 0x56e) {
            idx = 0x56d;
        }
        e = (unsigned char *) func_0206e7bc(func_0206e6ec(((int *) data_021cb5e0)), idx);
        if (e != 0) {
            if (((e[9] >> 1) & 1) != 0) {
                return 1;
            }
            return 0;
        }
        return 0;
    } else {
        idx = v & 0xfff;
        if (idx >= 0x56e) {
            idx = 0x56d;
        }
        e = (unsigned char *) func_0206e7bc(func_0206e6ec(((int *) data_021cb5e0)), idx);
        if (e != 0) {
            if (((e[9] >> 1) & 1) != 0) {
                return 1;
            }
            return 0;
        }
        return 0;
    }
}

int func_020624d4(unsigned short *p)
{
    unsigned short v;
    int cond;
    int d;
    volatile unsigned short t;
    unsigned int idx;
    unsigned char *e;

    cond = 0;
    v = *p;
    if (v >= 0x1000 && v <= 0x10ff) {
        cond = 1;
    }

    if (cond != 0) {
        if (v >= 0x1000 && v <= 0x10ff) {
            d = v - 0x1000;
        } else {
            d = -1;
        }
        d |= 3;
        t = ((unsigned int) d < 0x100) ? (unsigned short) (d + 0x1000) : 0x1000;
        idx = t & 0xfff;
        if (idx >= 0x56e) {
            idx = 0x56d;
        }
        e = (unsigned char *) func_0206e7bc(func_0206e6ec(((int *) data_021cb5e0)), idx);
        if (e != 0) {
            if (((e[9] >> 2) & 1) != 0) {
                return 1;
            }
            return 0;
        }
        return 0;
    } else {
        idx = v & 0xfff;
        if (idx >= 0x56e) {
            idx = 0x56d;
        }
        e = (unsigned char *) func_0206e7bc(func_0206e6ec(((int *) data_021cb5e0)), idx);
        if (e != 0) {
            if (((e[9] >> 2) & 1) != 0) {
                return 1;
            }
            return 0;
        }
        return 0;
    }
}

int func_02062408(unsigned short *p)
{
    unsigned short v;
    int cond;
    int d;
    volatile unsigned short t;
    unsigned int idx;
    unsigned char *e;

    cond = 0;
    v = *p;
    if (v >= 0x1000 && v <= 0x10ff) {
        cond = 1;
    }

    if (cond != 0) {
        if (v >= 0x1000 && v <= 0x10ff) {
            d = v - 0x1000;
        } else {
            d = -1;
        }
        d |= 3;
        t = ((unsigned int) d < 0x100) ? (unsigned short) (d + 0x1000) : 0x1000;
        idx = t & 0xfff;
        if (idx >= 0x56e) {
            idx = 0x56d;
        }
        e = (unsigned char *) func_0206e7bc(func_0206e6ec(((int *) data_021cb5e0)), idx);
        if (e != 0) {
            if (((e[9] >> 3) & 1) != 0) {
                return 1;
            }
            return 0;
        }
        return 0;
    } else {
        idx = v & 0xfff;
        if (idx >= 0x56e) {
            idx = 0x56d;
        }
        e = (unsigned char *) func_0206e7bc(func_0206e6ec(((int *) data_021cb5e0)), idx);
        if (e != 0) {
            if (((e[9] >> 3) & 1) != 0) {
                return 1;
            }
            return 0;
        }
        return 0;
    }
}

int func_0206233c(unsigned short *p)
{
    unsigned short v;
    int cond;
    int d;
    volatile unsigned short t;
    unsigned int idx;
    unsigned char *e;

    cond = 0;
    v = *p;
    if (v >= 0x1000 && v <= 0x10ff) {
        cond = 1;
    }

    if (cond != 0) {
        if (v >= 0x1000 && v <= 0x10ff) {
            d = v - 0x1000;
        } else {
            d = -1;
        }
        d |= 3;
        t = ((unsigned int) d < 0x100) ? (unsigned short) (d + 0x1000) : 0x1000;
        idx = t & 0xfff;
        if (idx >= 0x56e) {
            idx = 0x56d;
        }
        e = (unsigned char *) func_0206e7bc(func_0206e6ec(((int *) data_021cb5e0)), idx);
        if (e != 0) {
            if (((e[9] >> 4) & 1) != 0) {
                return 1;
            }
            return 0;
        }
        return 0;
    } else {
        idx = v & 0xfff;
        if (idx >= 0x56e) {
            idx = 0x56d;
        }
        e = (unsigned char *) func_0206e7bc(func_0206e6ec(((int *) data_021cb5e0)), idx);
        if (e != 0) {
            if (((e[9] >> 4) & 1) != 0) {
                return 1;
            }
            return 0;
        }
        return 0;
    }
}

unsigned char func_02062300(unsigned short *ptr)
{
    unsigned int masked;
    unsigned int index;
    void *tmp;
    void *result;

    masked = *ptr & 0xfff;
    index = (masked < 0x56e) ? masked : 0x56d;
    tmp = func_0206e6e8((void *) data_021cb5e0);
    result = func_0206e7bc(tmp, index);
    if (result != 0) {
        return ((unsigned char *) result)[1];
    } else {
        return 0;
    }
}

unsigned char func_020622c4(unsigned short *param)
{
    unsigned int mask;
    void *tmp;
    unsigned char *res;

    mask = *param & 0x0fff;
    if (mask >= 0x056e) {
        mask = 0x056d;
    }
    tmp = func_0206e6e8(((char *) data_021cb5e0));
    res = (unsigned char *) func_0206e7bc(tmp, mask);
    if (res) {
        return *res;
    }
    return 0;
}

unsigned char func_020622a0(int param)
{
    unsigned char *ptr;

    if (param >= 0x4A) {
        goto ret3;
    }
    ptr = (unsigned char *) func_0206e7bc(&data_021cb634, param);
    if (ptr == 0) {
        goto ret3;
    }
    return ptr[0x16];
ret3:
    return 3;
}

int func_02062280(int arg0)
{
    int ret;

    if (arg0 < 74) {
        ret = (int) func_0206e7bc(((unsigned char *) &data_021cb634), arg0);
        if (ret != 0) {
            return ret;
        }
    }
    return 0;
}

int func_0206226c(int x)
{
    if (x < 46) {
        return data_020cca34[x];
    } else {
        return 0;
    }
}

int func_0206223c(int a, int b)
{
    if (a < 0x49) {
        unsigned char flag = (b == 0);
        return data_020de368[a][flag];
    } else {
        return func_0206223c(0, b);
    }
}

unsigned int func_02062230(void)
{
    return (*(unsigned int *) &data_021cb5c0);
}

void func_020621d4(unsigned short *out, int n)
{
    if (data_021cb5c0 != 0) {
        int i = 0;
        unsigned short cur = data_021cb5b0;
        while (cur < 0x156e) {
            unsigned short tmp = cur;
            if (func_0206266c(&tmp) != 0) {
                if (i == n) {
                    *out = tmp;
                    return;
                }
                i++;
            }
            cur = (unsigned short) (cur + 1);
        }
    }
    *out = data_021cb5b0;
}

unsigned int func_02062148(unsigned short *target)
{
    int count;
    unsigned short cur;
    int falseVal1;
    int falseVal2;

    if (data_021cb5c0 == 0) {
        goto notfound;
    }

    count = 0;
    cur = data_021cb5b0;
    falseVal1 = 0;
    falseVal2 = 0;

    while (cur < 0x156e) {
        unsigned short tmp = cur;
        int matched;

        if (func_0206266c(&tmp) != 0) {
            if (func_0204bcdc(&tmp) != 0) {
                matched = (func_0204bc64(&tmp) == func_0204bc64(target)) ? 1 : falseVal1;
            } else {
                matched = (tmp == *target) ? 1 : falseVal2;
            }

            if (matched != 0) {
                return count;
            }
            count++;
        }

        cur = (unsigned short) (cur + 1);
    }

notfound:
    return 0xFFFFFFFF;
}

int func_0206213c(void)
{
    return data_021cb5b4;
}

unsigned int func_02062130(void)
{
    return (*(unsigned int *) &data_021cb5b8);
}

unsigned int func_02062124(void)
{
    return (*(unsigned int *) &data_021cb5c4);
}

int func_02062118(void)
{
    return data_021cb5bc;
}
