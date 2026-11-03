/* villager_impression_tests: 28 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207ec68 @ 0x0207ec68, 0x1c bytes, Thumb
 * func_0207ec50 @ 0x0207ec50, 0x18 bytes, Thumb
 * func_0207ec44 @ 0x0207ec44, 0xc bytes, Thumb
 * func_0207ec34 @ 0x0207ec34, 0x10 bytes, Thumb
 * func_0207ebf8 @ 0x0207ebf8, 0x3c bytes, Thumb
 * func_0207ebb8 @ 0x0207ebb8, 0x40 bytes, Thumb
 * func_0207eb7c @ 0x0207eb7c, 0x3c bytes, Thumb
 * func_0207eb40 @ 0x0207eb40, 0x3c bytes, Thumb
 * func_0207eaf4 @ 0x0207eaf4, 0x4c bytes, Thumb
 * func_0207eaa8 @ 0x0207eaa8, 0x4c bytes, Thumb
 * func_0207ea5c @ 0x0207ea5c, 0x4c bytes, Thumb
 * func_0207ea10 @ 0x0207ea10, 0x4c bytes, Thumb
 * func_0207e9c4 @ 0x0207e9c4, 0x4c bytes, Thumb
 * func_0207e978 @ 0x0207e978, 0x4c bytes, Thumb
 * func_0207e92c @ 0x0207e92c, 0x4c bytes, Thumb
 * func_0207e8e0 @ 0x0207e8e0, 0x4c bytes, Thumb
 * func_0207e894 @ 0x0207e894, 0x4c bytes, Thumb
 * func_0207e848 @ 0x0207e848, 0x4c bytes, Thumb
 * func_0207e7fc @ 0x0207e7fc, 0x4c bytes, Thumb
 * func_0207e780 @ 0x0207e780, 0x7c bytes, Thumb
 * func_0207e738 @ 0x0207e738, 0x48 bytes, Thumb
 * func_0207e720 @ 0x0207e720, 0x18 bytes, Thumb
 * func_0207e708 @ 0x0207e708, 0x18 bytes, Thumb
 * func_0207e6d4 @ 0x0207e6d4, 0x34 bytes, Thumb
 * func_0207e6bc @ 0x0207e6bc, 0x18 bytes, Thumb
 * func_0207e6a4 @ 0x0207e6a4, 0x18 bytes, Thumb
 * func_0207e684 @ 0x0207e684, 0x1e bytes, Thumb
 * func_0207e674 @ 0x0207e674, 0x10 bytes, Thumb
 */

struct UnkStruct_0207e978 {
    unsigned short first;
    unsigned short pad_02;
    unsigned int other;
};

typedef struct UnkStruct_0207e780 {
    unsigned short v;
} UnkStruct_0207e780;

extern int func_0207cad4(void *ptr);
extern int data_021e5a2c;
extern int func_0207af30(void);
extern unsigned short *func_02099728(unsigned int);
extern unsigned short *func_020996f8(int);
extern int func_0204bcdc(void *);
extern int func_0204bc64(unsigned short *p);
extern UnkStruct_0207e780 *func_020996e0(void *self);
extern int func_020ba4e4(void);
extern unsigned short *func_02099710(unsigned int);
extern int func_0209dcac(void);
extern int func_02099734(int);
extern int func_02098eb8(int);

int func_0207ec68(void)
{
    int ret = 0;
    if (func_0207cad4(&data_021e5a2c) <= 4) {
        ret = 1;
    }
    return ret;
}

int func_0207ec50(void)
{
    int result;
    if (func_0207af30() == 0xb) {
        result = 0;
    } else {
        result = 1;
    }
    return result;
}

int func_0207ec44(int r0, int r1, int r2)
{
    if (r2 == 1) {
        return 1;
    } else {
        return 0;
    }
}

int func_0207ec34(int r0, int r1, int r2)
{
    if (r2 == 2 || r2 == 4) {
        return 1;
    }
    return 0;
}

int func_0207ebf8(unsigned int argument0)
{
    unsigned short *p = func_02099728((unsigned int) argument0);
    int flag = 1;
    int cond = 0;
    unsigned short v = *p;
    if (v >= 0x1376 && v <= 0x1376) {
        cond = flag;
    }
    if (cond == 0) {
        if (v < 0x1377 || v > 0x1377) {
            flag = 0;
        }
    }
    return flag;
}

int func_0207ebb8(unsigned int argument0)
{
    unsigned short *p = func_02099728((unsigned int) argument0);
    int flag = 1;
    int cond = 0;
    unsigned short v = *p;
    if (v >= 0x136b && v <= 0x1372) {
        cond = flag;
    }
    if (cond == 0) {
        if (v < 0x1373 || v > 0x1373) {
            flag = 0;
        }
    }
    return flag;
}

int func_0207eb7c(unsigned int argument0)
{
    unsigned short *p = func_02099728((unsigned int) argument0);
    int flag = 1;
    int cond = 0;
    unsigned short v = *p;
    if (v >= 0x1374 && v <= 0x1374) {
        cond = flag;
    }
    if (cond == 0) {
        if (v < 0x1375 || v > 0x1375) {
            flag = 0;
        }
    }
    return flag;
}

int func_0207eb40(unsigned int argument0)
{
    unsigned short *p = func_02099728((unsigned int) argument0);
    int flag = 1;
    int cond = 0;
    unsigned short v = *p;
    if (v >= 0x1378 && v <= 0x1378) {
        cond = flag;
    }
    if (cond == 0) {
        if (v < 0x1379 || v > 0x1379) {
            flag = 0;
        }
    }
    return flag;
}

int func_0207eaf4(int argument0)
{
    unsigned short *ptr = func_020996f8((int) argument0);
    if (func_0204bcdc(ptr)) {
        unsigned short local = 0x13c1;
        void *a = (void *) func_0204bc64((unsigned short *) ptr);
        void *b = (void *) func_0204bc64((unsigned short *) (&local));
        if (a != b) {
            return 0;
        }
        return 1;
    } else {
        if (*ptr == 0x13c1) {
            return 1;
        }
        return 0;
    }
}

int func_0207eaa8(const unsigned short *str)
{
    const unsigned short *p = (const unsigned short *) func_020996f8((int) str);
    if (func_0204bcdc((void *) p)) {
        unsigned short tmp[4];
        int a, b;
        tmp[0] = 0x13b2;
        a = func_0204bc64((unsigned short *) p);
        b = func_0204bc64((unsigned short *) tmp);
        if (a == b) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (p[0] == 0x13b2) {
            return 1;
        } else {
            return 0;
        }
    }
}

int func_0207ea5c(int object)
{
    int r4;
    int r0;
    unsigned short local;

    r4 = (int) func_020996f8(object);
    if (func_0204bcdc((void *) r4) != 0) {
        local = 0x13a8;
        r4 = func_0204bc64((unsigned short *) r4);
        r0 = func_0204bc64((unsigned short *) ((int) &local));
        if (r4 == r0) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (*(unsigned short *) r4 == 0x13a8) {
            return 1;
        } else {
            return 0;
        }
    }
}

int func_0207ea10(int argument0)
{
    unsigned short val;
    unsigned short *p = func_020996f8((int) argument0);
    if (func_0204bcdc((void *) p)) {
        val = 0x13bc;
        if (func_0204bc64(p) == func_0204bc64(&val)) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (*p == 0x13bc) {
            return 1;
        } else {
            return 0;
        }
    }
}

int func_0207e9c4(int argument0)
{
    unsigned short local;
    unsigned short *p = func_020996f8((int) argument0);

    if (func_0204bcdc(p) != 0) {
        local = 0x1405;
        if (func_0204bc64((unsigned short *) p) == func_0204bc64((unsigned short *) (&local))) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (p[0] == 0x1405) {
            return 1;
        } else {
            return 0;
        }
    }
}

int func_0207e978(int argument0)
{
    struct UnkStruct_0207e978 *p;

    p = (struct UnkStruct_0207e978 *) func_020996f8((int) argument0);
    if (func_0204bcdc((void *) p) != 0) {
        struct UnkStruct_0207e978 local;
        local.first = 0x13e6;
        if (func_0204bc64((unsigned short *) p) != func_0204bc64((unsigned short *) (&local))) {
            return 0;
        } else {
            return 1;
        }
    } else {
        if (p->first == 0x13e6) {
            return 1;
        } else {
            return 0;
        }
    }
}

int func_0207e92c(int argument0)
{
    unsigned short *p = func_020996f8((int) argument0);
    if (func_0204bcdc(p)) {
        unsigned short temp = 0x13ea;
        int a = func_0204bc64(p);
        int b = func_0204bc64(&temp);
        if (a == b) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (*p == 0x13ea) {
            return 1;
        } else {
            return 0;
        }
    }
}

int func_0207e8e0(int argument0)
{
    unsigned short *p;
    unsigned short local;

    p = func_020996f8((int) argument0);
    if (func_0204bcdc(p) != 0) {
        local = 0x13f5;
        if (func_0204bc64(p) == func_0204bc64(&local)) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (*p == 0x13f5) {
            return 1;
        } else {
            return 0;
        }
    }
}

int func_0207e894(int v)
{
    unsigned short local;
    void *p;
    int w;

    p = (void *) func_020996f8(v);
    if (func_0204bcdc(p) != 0) {
        local = 0x13E3;
        v = func_0204bc64((unsigned short *) p);
        w = func_0204bc64((unsigned short *) (&local));
        if (v == w) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (*(unsigned short *) p == 0x13E3) {
            return 1;
        } else {
            return 0;
        }
    }
}

int func_0207e848(int argument0)
{
    unsigned short *p = func_020996f8((int) argument0);
    if (func_0204bcdc((void *) p)) {
        unsigned short local[4];
        int a, b;
        local[0] = 0x13e4;
        a = func_0204bc64(p);
        b = func_0204bc64(local);
        if (a == b) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (*p == 0x13e4) {
            return 1;
        } else {
            return 0;
        }
    }
}

int func_0207e7fc(int object)
{
    int a = (int) func_020996f8(object);
    if (func_0204bcdc((void *) a)) {
        unsigned short local = 0x1406;
        if (func_0204bc64((unsigned short *) a) == func_0204bc64((unsigned short *) ((int) &local))) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (*(unsigned short *) a == 0x1406) {
            return 1;
        } else {
            return 0;
        }
    }
}

static __inline unsigned int chk(UnkStruct_0207e780 *q, unsigned short lo, unsigned short hi)
{
    unsigned int r = 0;
    if (q->v >= lo && q->v <= hi) {
        r = 1;
    }
    return r;
}

int func_0207e780(void *self)
{
    unsigned int res = 1;
    unsigned int ok = 1;

    if (chk((UnkStruct_0207e780 *) func_02099728((unsigned int) self), 0x137c, 0x137c) == 0) {
        if (chk((UnkStruct_0207e780 *) func_020996f8((int) self), 0x1408, 0x1428) == 0) {
            ok = 0;
        }
    }
    if (ok == 0) {
        if (chk(func_020996e0(self), 0x1471, 0x1491) == 0) {
            res = 0;
        }
    }
    return res;
}

int func_0207e738(unsigned int object)
{
    int r3;
    int r2;
    unsigned short r1;
    int r0;

    r0 = (int) func_02099728(object);
    r3 = 1;
    r2 = 0;
    r1 = *(unsigned short *) r0;
    if (r1 >= 0x1380 && r1 <= 0x139f) {
        r2 = r3;
    }
    if (r2 == 0) {
        if (r1 < 0x13a0 || r1 > 0x13a7) {
            r3 = 0;
        }
    }
    return r3;
}

int func_0207e720(void)
{
    if (func_020ba4e4() == 1) {
        return 1;
    } else {
        return 0;
    }
}

int func_0207e708(void)
{
    if (func_020ba4e4() == 2) {
        return 1;
    } else {
        return 0;
    }
}

int func_0207e6d4(unsigned int argument0)
{
    unsigned short *p = func_02099710((unsigned int) argument0);
    int flag = (*p >= 0x12a8 && *p <= 0x12af);
    if (flag) {
        return 1;
    } else {
        return 0;
    }
}

int func_0207e6bc(void)
{
    if (func_0209dcac() == 0) {
        return 1;
    } else {
        return 0;
    }
}

int func_0207e6a4(void)
{
    int result;
    result = func_0209dcac();
    if (result == 3) {
        return 1;
    } else {
        return 0;
    }
}

int func_0207e684(int object)
{
    int r0;
    int r2;
    int r1;

    r0 = func_02099734(object);
    r0 = func_02098eb8(r0);
    r2 = 0;
    r1 = ~r2;
    if (r0 != r1) {
        r2 = 0;
    } else {
        r2 = 1;
    }
    r0 = r2;
    return r0;
}

int func_0207e674(int a, int b)
{
    if (b > ~0x4F) {
        return 0;
    } else {
        return 1;
    }
}
