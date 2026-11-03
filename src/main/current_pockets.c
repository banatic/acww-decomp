/* current_pockets: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209a1e8 @ 0x0209a1e8, 0x16 bytes, Thumb
 * func_0209a1d0 @ 0x0209a1d0, 0x16 bytes, Thumb
 * func_0209a19c @ 0x0209a19c, 0x32 bytes, Thumb
 * func_0209a14c @ 0x0209a14c, 0x50 bytes, Thumb
 * func_0209a110 @ 0x0209a110, 0x3c bytes, Thumb
 * func_0209a088 @ 0x0209a088, 0x88 bytes, Thumb
 * func_0209a050 @ 0x0209a050, 0x38 bytes, Thumb
 * func_0209a034 @ 0x0209a034, 0x1a bytes, Thumb
 * func_0209a000 @ 0x0209a000, 0x32 bytes, Thumb
 * func_02099fe8 @ 0x02099fe8, 0x16 bytes, Thumb
 * func_02099fe0 @ 0x02099fe0, 0x8 bytes, Thumb
 * func_02099f7c @ 0x02099f7c, 0x62 bytes, Thumb
 */

typedef struct {
    short unk_00;
    unsigned char unk_02;
} UnkStruct_02099fe0;

extern int func_020984e8(void);
extern int func_02099734(int);
extern int func_02098e10(int);
extern int func_02098de8(int);
extern void func_02063ccc(void *, int, int);
extern void func_020638d4(void *, void *, int, int, int, int, int);
extern void func_02063cc8(void *);
extern void func_02061e2c(unsigned short *, unsigned short *);
extern int func_02098f70(int);
extern int func_020996ac(int);
extern int func_02098f0c(int, unsigned short *, int, int);
extern int func_0203cd2c(int, void *, int, int);
extern unsigned short *func_02098f48(void *, unsigned int);
extern int func_02098eb8(int);
extern int func_02098e74(int a, int b);
extern int func_0204c520(unsigned short *a);

void func_0209a088(unsigned short *p, int flag, int arg2);
int func_02099fe8(void);

int func_0209a1e8(void)
{
    return func_02098e10((int) func_02099734((int) func_020984e8()));
}

int func_0209a1d0(void)
{
    return func_02098de8((int) func_02099734((int) func_020984e8()));
}

unsigned short func_0209a19c(void)
{
    unsigned short result;
    int obj[3];

    func_02063ccc(obj, 0, 3);
    func_020638d4(&result, obj, 0, 0, 1, 1, 0);
    func_02063cc8(obj);
    return result;
}

void func_0209a14c(unsigned short *a, unsigned int b)
{
    unsigned short x, y;
    int flag = 0;

    x = 0xfff1;
    if (*a == 0x156b) {
        x = func_0209a19c();
        flag = 1;
    } else {
        func_02061e2c(&y, a);
        x = y;
    }
    func_0209a088(&x, flag, b);
}

int func_0209a110(void *p)
{
    unsigned short v;
    int r = func_02099fe8();
    if (r == -1) {
        return 0;
    }
    v = *(unsigned short *) p;
    if (v == 0xfff1) {
        return 1;
    }
    if (v >= 0xa7 && v <= 0xc6) {
        return 1;
    }
    func_0209a14c((unsigned short *) p, r);
    return 1;
}

void func_0209a088(unsigned short *p, int flag, int arg2)
{
    int h;
    int ret;
    int ok;
    unsigned short local;

    h = func_020984e8();
    if (func_02098f70(arg2) == 0) {
        return;
    }
    if (*p != 0xfff1 && flag == 0) {
        ret = func_020996ac(h);
        func_0203cd2c(ret, p, 0, 1);
    }
    if (flag == 0) {
        ok = 0;
        if (*p >= 0x151f && *p <= 0x151f) {
            ok = 1;
        }
        if (ok != 0) {
            local = 0x1033;
            ret = func_020996ac(h);
            func_0203cd2c(ret, &local, 0, 1);
        }
    }
    ret = func_02099734(h);
    func_02098f0c(ret, p, arg2, flag);
}

void func_0209a050(int index)
{
    int a;
    unsigned short b;

    a = func_020984e8();
    if (func_02098f70(index)) {
        b = 0xfff1;
        func_02098f0c(func_02099734(a), (unsigned short *) (&b), index, 0);
    }
}

unsigned short func_0209a034(unsigned int arg)
{
    return *func_02098f48((void *) func_02099734((int) ((void *) func_020984e8())), arg);
}

int func_0209a000(int a, int b)
{
    int local[2];
    int result;

    result = func_02099fe8();
    if (result != -1) {
        func_02061e2c((unsigned short *) local, (unsigned short *) a);
        func_0209a088((unsigned short *) local, b, result);
        return 1;
    }
    return 0;
}

int func_02099fe8(void)
{
    return func_02098eb8(func_02099734(func_020984e8()));
}

void func_02099fe0(UnkStruct_02099fe0 *p)
{
    p->unk_02 = 0;
    p->unk_00 = 0;
}

unsigned char func_02099f7c(unsigned short *a, int b)
{
    int x;
    unsigned short *p;
    int i;

    x = func_020984e8();
    func_02099fe0((UnkStruct_02099fe0 *) a);
    p = func_02098f48((void *) (func_02099734(x)), 0);

    for (i = 0; i < 15; i++) {
        if (func_02098e74(func_02099734(x), i) != 0) {
            if (func_0204c520(p + i) == b) {
                *a |= (1 << i);
                ((unsigned char *) a)[2]++;
            }
        }
    }
    return ((unsigned char *) a)[2];
}
