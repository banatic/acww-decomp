/* date_time: 20 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209e474 @ 0x0209e474, 0x28 bytes, Thumb
 * func_0209e3ac @ 0x0209e3ac, 0xc8 bytes, Thumb
 * func_0209e380 @ 0x0209e380, 0x2c bytes, Thumb
 * func_0209e350 @ 0x0209e350, 0x30 bytes, Thumb
 * func_0209e314 @ 0x0209e314, 0x3a bytes, Thumb
 * func_0209e304 @ 0x0209e304, 0xe bytes, Thumb
 * func_0209e2d0 @ 0x0209e2d0, 0x32 bytes, Thumb
 * func_0209e29c @ 0x0209e29c, 0x34 bytes, Thumb
 * func_0209e268 @ 0x0209e268, 0x32 bytes, Thumb
 * func_0209e234 @ 0x0209e234, 0x32 bytes, Thumb
 * func_0209e200 @ 0x0209e200, 0x32 bytes, Thumb
 * func_0209e1f0 @ 0x0209e1f0, 0xe bytes, Thumb
 * func_0209e1ac @ 0x0209e1ac, 0x42 bytes, Thumb
 * func_0209e140 @ 0x0209e140, 0x6a bytes, Thumb
 * func_0209e100 @ 0x0209e100, 0x40 bytes, Thumb
 * func_0209e0c0 @ 0x0209e0c0, 0x40 bytes, Thumb
 * func_0209e080 @ 0x0209e080, 0x40 bytes, Thumb
 * func_0209e040 @ 0x0209e040, 0x3e bytes, Thumb
 * func_0209dffc @ 0x0209dffc, 0x44 bytes, Thumb
 * func_0209dfd8 @ 0x0209dfd8, 0x24 bytes, Thumb
 */

struct UnkStruct_0209e29c {
    unsigned char pad_00[3];
    unsigned char unk_03;
    unsigned char unk_04;
    unsigned char unk_05;
};

struct UnkStruct_0209e268 {
    unsigned char pad_00[2];
    unsigned char unk_02;
};

typedef struct {
    char unk_00;
    unsigned char unk_01;
} UnkStruct_0209e234;

typedef struct Timer {
    unsigned int unk_00;
    unsigned char value;
} Timer;

typedef struct {
    char pad_00[3];
    unsigned char unk_03;
    unsigned char unk_04;
    unsigned char unk_05;
} Struct0209e140;

struct UnkStruct_0209e0c0 {
    unsigned char pad_00;
    unsigned char b;
};

extern int data_021dc744[3];
extern int data_021dc754[3];
extern int func_0209dcdc(void *a, void *b);
extern int func_0209de88(int year, int month, int day);
extern void MI_CpuCopy8(const void *, void *, unsigned int);
extern int func_0209de24(unsigned char, unsigned char);

void func_0209e140(Struct0209e140 *p, int n);

void func_0209e474(unsigned char *p0)
{
    int *const b = data_021dc754;
    int *a = data_021dc744;
    p0[5] = a[0];
    p0[4] = a[1];
    p0[3] = a[2];
    p0[2] = b[0];
    p0[1] = b[1];
    p0[0] = b[2];
}

int func_0209e3ac(int r0, int r1, int r2)
{
    if (r2 & 0x20) {
        if (*(unsigned char *) (r0 + 5) < *(unsigned char *) (r1 + 5)) {
            return -1;
        }
        if (*(unsigned char *) (r0 + 5) > *(unsigned char *) (r1 + 5)) {
            return 1;
        }
    }
    if (r2 & 0x10) {
        if (*(unsigned char *) (r0 + 4) < *(unsigned char *) (r1 + 4)) {
            return -1;
        }
        if (*(unsigned char *) (r0 + 4) > *(unsigned char *) (r1 + 4)) {
            return 1;
        }
    }
    if (r2 & 0x08) {
        if (*(unsigned char *) (r0 + 3) < *(unsigned char *) (r1 + 3)) {
            return -1;
        }
        if (*(unsigned char *) (r0 + 3) > *(unsigned char *) (r1 + 3)) {
            return 1;
        }
    }
    if (r2 & 0x04) {
        if (*(unsigned char *) (r0 + 2) < *(unsigned char *) (r1 + 2)) {
            return -1;
        }
        if (*(unsigned char *) (r0 + 2) > *(unsigned char *) (r1 + 2)) {
            return 1;
        }
    }
    if (r2 & 0x02) {
        if (*(unsigned char *) (r0 + 1) < *(unsigned char *) (r1 + 1)) {
            return -1;
        }
        if (*(unsigned char *) (r0 + 1) > *(unsigned char *) (r1 + 1)) {
            return 1;
        }
    }
    if (r2 & 0x01) {
        if (*(unsigned char *) (r0) < *(unsigned char *) (r1)) {
            return -1;
        }
        if (*(unsigned char *) (r0) > *(unsigned char *) (r1)) {
            return 1;
        }
    }
    return 0;
}

int func_0209e380(void *r0, void *r1)
{
    unsigned char sp[8];
    unsigned char *p = sp;

    sp[2] = ((unsigned char *) r1)[5];
    sp[1] = ((unsigned char *) r1)[4];
    sp[0] = ((unsigned char *) r1)[3];
    sp[6] = ((unsigned char *) r0)[5];
    sp[5] = ((unsigned char *) r0)[4];
    sp[4] = ((unsigned char *) r0)[3];

    return func_0209dcdc(sp, sp + 4);
}

int func_0209e350(void *param0, void *param1)
{
    int r0;
    int r2;
    int r1;
    unsigned char r5_1;
    unsigned char r5_2;
    unsigned char r4_1;
    unsigned char r4_2;
    int result;

    r0 = func_0209e380(param0, param1);
    r5_2 = *(unsigned char *) ((char *) param0 + 2);
    r4_2 = *(unsigned char *) ((char *) param1 + 2);
    r2 = (r4_2 - r5_2) * 0x3c;
    r5_1 = *(unsigned char *) ((char *) param0 + 1);
    r2 = r2 - r5_1;
    r0 = r0 * 0x5a0;
    r1 = r2 + r0;
    r4_1 = *(unsigned char *) ((char *) param1 + 1);
    result = r1 + r4_1;
    return result;
}

void func_0209e314(unsigned char *a, unsigned char *b)
{
    unsigned int ret;
    if (b == 0) {
        return;
    }
    ret = func_0209de88(a[5], a[4], a[3]);
    if (b != a) {
        MI_CpuCopy8(a, b, 8);
    }
    func_0209e140((Struct0209e140 *) b, ret);
    b[2] = 0;
    b[1] = 0;
    b[0] = 0;
}

void func_0209e304(unsigned char *r0, int r1)
{
    unsigned char r2;
    int r1_local;

    r2 = r0[5];
    r1_local = r2 + r1;
    if (r1_local > 0x63) {
        r1_local -= 0x64;
    }
    r0[5] = (unsigned char) r1_local;
}

void func_0209e2d0(unsigned char *p, int add)
{
    int sum;
    sum = p[4] + add;
    if (sum > 12) {
        func_0209e304((unsigned char *) p, sum / 12);
        sum = sum % 12;
    }
    p[4] = (unsigned char) sum;
}

void func_0209e29c(struct UnkStruct_0209e29c *s, int arg)
{
    int limit = func_0209de24(s->unk_05, s->unk_04);
    int cur = s->unk_03 + arg;
    while (cur > limit) {
        cur -= limit;
        func_0209e2d0((unsigned char *) s, 1);
        limit = func_0209de24(s->unk_05, s->unk_04);
    }
    s->unk_03 = (unsigned char) cur;
}

void func_0209e268(struct UnkStruct_0209e268 *ptr, int add)
{
    int v = ptr->unk_02 + add;
    if (v >= 24) {
        func_0209e29c((struct UnkStruct_0209e29c *) ptr, v / 24);
        v = v % 24;
    }
    ptr->unk_02 = v;
}

void func_0209e234(UnkStruct_0209e234 *p, int n)
{
    int val = p->unk_01 + n;
    if (val >= 60) {
        func_0209e268((struct UnkStruct_0209e268 *) p, val / 60);
        val = val % 60;
    }
    p->unk_01 = (unsigned char) val;
}

void func_0209e200(unsigned char *ptr, int add)
{
    int sum = *ptr + add;
    if (sum >= 60) {
        func_0209e234((UnkStruct_0209e234 *) ptr, sum / 60);
        sum = sum % 60;
    }
    *ptr = (unsigned char) sum;
}

void func_0209e1f0(unsigned char *ptr, int val)
{
    int diff;
    diff = ptr[5] - val;
    if (diff < 0) {
        diff += 100;
    }
    ptr[5] = (unsigned char) diff;
}

void func_0209e1ac(Timer *timer, int delta)
{
    int diff = timer->value - delta;
    if (diff < 1) {
        int r6;
        if (diff == 0) {
            diff = 12;
            r6 = 1;
        } else {
            if (diff < 0) {
                diff = -diff;
            }
            r6 = diff / 12 + 1;
            diff = 12 - diff % 12;
        }
        func_0209e1f0((unsigned char *) timer, r6);
    }
    timer->value = diff;
}

void func_0209e140(Struct0209e140 *p, int n)
{
    int r4;
    int x;

    r4 = p->unk_03;
    if (p->unk_04 == 1) {
        x = func_0209de24(p->unk_05, 12);
    } else {
        x = func_0209de24(p->unk_05, (unsigned char) (p->unk_04 - 1));
    }

    r4 = r4 - n;

    while (r4 <= 0) {
        if (r4 == 0) {
            r4 = x;
        } else {
            r4 = r4 + x;
        }

        func_0209e1ac((Timer *) p, 1);

        if (p->unk_04 == 1) {
            x = func_0209de24(p->unk_05, 12);
        } else {
            x = func_0209de24(p->unk_05, (unsigned char) (p->unk_04 - 1));
        }
    }

    p->unk_03 = (unsigned char) r4;
}

void func_0209e100(unsigned char *p, int a)
{
    int diff = p[2] - a;
    if (diff < 0) {
        int q, rem, s;
        if (diff < 0) {
            diff = -diff;
        }
        q = diff / 24 + 1;
        rem = diff % 24;
        s = 24 - rem;
        if (s == 24) {
            s = 0;
            q--;
        }
        func_0209e140((Struct0209e140 *) p, q);
        diff = s;
    }
    p[2] = diff;
}

void func_0209e0c0(struct UnkStruct_0209e0c0 *p, int v)
{
    int d = p->b - v;
    if (d < 0) {
        int c;
        int r;
        if (d < 0) {
            d = -d;
        }
        c = d / 60 + 1;
        r = d % 60;
        d = 60 - r;
        if (d == 60) {
            d = 0;
            c--;
        }
        func_0209e100((unsigned char *) p, c);
    }
    p->b = d;
}

void func_0209e080(unsigned char *p, int v)
{
    int delta;
    int quotient;
    int remainder;
    int rounded;

    delta = *p - v;
    if (delta < 0) {
        delta = delta < 0 ? -delta : delta;
        quotient = delta / 60;
        rounded = quotient + 1;
        remainder = delta % 60;
        delta = 60 - remainder;
        if (delta == 60) {
            delta = 0;
            rounded--;
        }
        func_0209e0c0((struct UnkStruct_0209e0c0 *) p, rounded);
    }
    *p = delta;
}

void func_0209e040(int param1, unsigned char *param2)
{
    func_0209e080((unsigned char *) param1, (unsigned char) param2[0]);
    func_0209e0c0((struct UnkStruct_0209e0c0 *) param1, (unsigned char) param2[1]);
    func_0209e100((unsigned char *) param1, (unsigned char) param2[2]);
    func_0209e140((Struct0209e140 *) param1, (unsigned char) param2[3]);
    func_0209e1ac((Timer *) param1, (unsigned char) param2[4]);
    func_0209e1f0((unsigned char *) param1, (unsigned char) param2[5]);
}

int func_0209dffc(const unsigned char *p)
{
    int result = 0;
    int good = result;

    if (p[0] < 60 && p[1] < 60 && p[2] < 24 && p[3] >= 1 && p[3] <= 31 && p[4] >= 1 && p[4] <= 12) {
        good = 1;
    }
    if (good != 0 && p[5] <= 99) {
        result = 1;
    }

    if (result != 0) {
        return 0;
    } else {
        return 1;
    }
}

void func_0209dfd8(unsigned char *dest, const unsigned char *src, unsigned char a, unsigned char b, unsigned char c)
{
    dest[5] = src[2];
    dest[4] = src[1];
    dest[3] = src[0];
    dest[2] = a;
    dest[1] = b;
    dest[0] = c;
}
