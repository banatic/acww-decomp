/* cafe_guest: 5 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_022739f4 @ 0x022739f4, 0x68 bytes, Thumb
 * func_ov068_02273980 @ 0x02273980, 0x74 bytes, Thumb
 * func_ov068_02273974 @ 0x02273974, 0xc bytes, Thumb
 * func_ov068_02273948 @ 0x02273948, 0x2c bytes, Thumb
 * func_ov068_02273920 @ 0x02273920, 0x28 bytes, Thumb
 */

struct UnkStruct_022739f4 {
    unsigned int x, y, z;
};

struct UnkStruct_022739f4_2 {
    char pad_00[0x74a];
    unsigned char unk_74A;
};

extern int func_020984e8(void);
extern struct UnkStruct_022739f4 *func_02095794(int);
extern void func_0204f818(int *, int *, struct UnkStruct_022739f4 *);
extern int func_020960f8(int, int);
extern int func_0203e070(struct UnkStruct_022739f4_2 *, int);
extern void func_02063414(void *, int, int, int, int, int, int, int, int, int);
extern char data_ov068_02277e50;
extern void *func_ov068_022746fc(void *arg);
extern void *func_0202ee5c(void *arg);
extern void func_020edf54(void *arg);

int func_ov068_022739f4(struct UnkStruct_022739f4_2 *p)
{
    int a, b;
    struct UnkStruct_022739f4 s;
    struct UnkStruct_022739f4 *ps;

    if (p->unk_74A == 0) {
        return 0;
    }

    func_020984e8();
    ps = func_02095794(4);
    s.x = ps->x;
    s.y = ps->y;
    s.z = ps->z;

    a = 0;
    b = 0;
    func_0204f818(&a, &b, &s);

    if (func_020960f8(37, 4) != 0) {
        if (a == 9 && b == 13) {
            func_0203e070(p, 0);
        }
    }

    return 1;
}

unsigned short func_ov068_02273980(void)
{
    volatile unsigned short out[2];
    int x;
    unsigned int ok;
    unsigned short a, b;

    x = func_020984e8();
    func_02063414((void *) out, 0x1323, 0x46, 0, 0, x, 0, 0xa, 0, 1);
    ok = 0;
    b = out[0];
    a = out[0];
    if (a >= 0x1323 && b <= 0x1368) {
        ok = 1;
    }
    if (ok == 0) {
        func_02063414((void *) &out[1], 0x1323, 0x46, 0, 0, 0, 1, 0xa, 0, 1);
        out[0] = out[1];
    }
    return out[0];
}

int func_ov068_02273974(int *p)
{
    return p[0x1cc];
}

void *func_ov068_02273948(void *arg)
{
    char *p = (char *) arg;
    *(void **) p = (void *) &data_ov068_02277e50;
    func_ov068_022746fc((void *) (p + 0x65c));
    func_0202ee5c(arg);
    func_020edf54(arg);
    return arg;
}

void *func_ov068_02273920(void *arg0)
{
    *((void **) arg0) = (void *) &data_ov068_02277e50;
    func_ov068_022746fc((char *) arg0 + 0x65c);
    func_0202ee5c(arg0);
    return arg0;
}
