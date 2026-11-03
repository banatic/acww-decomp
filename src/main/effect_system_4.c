/* effect_system_4: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020913b0 @ 0x020913b0, 0x18 bytes, Thumb
 * func_02091358 @ 0x02091358, 0x58 bytes, Thumb
 * func_0209132c @ 0x0209132c, 0x2c bytes, Thumb
 * func_02091310 @ 0x02091310, 0x1c bytes, Thumb
 * func_02091300 @ 0x02091300, 0x10 bytes, Thumb
 * func_020912d4 @ 0x020912d4, 0x2c bytes, Thumb
 * func_020912ac @ 0x020912ac, 0x28 bytes, Thumb
 * func_0209129c @ 0x0209129c, 0x10 bytes, Thumb
 * func_02091278 @ 0x02091278, 0x24 bytes, Thumb
 * func_02091254 @ 0x02091254, 0x24 bytes, Thumb
 * func_02091230 @ 0x02091230, 0x24 bytes, Thumb
 * func_0209120c @ 0x0209120c, 0x24 bytes, Thumb
 */

typedef struct {
    int (*func)(int, int, int, int, int);
    int pad_04;
} Entry;

struct UnkStruct_02091358 {
    unsigned char pad_00[0x39c];
    unsigned short counter;
};

typedef struct {
    void (*handler)(int);
    int pad_04;
} Handler;

extern void func_02091468(void *);
extern Entry data_020e2c1c[];
extern Handler data_020e2c20[];
extern void *func_02091444(void *a, int b, void *c, int d);
extern unsigned char data_021d52d8[];
extern void func_020913f0(void *a, void *b, void *c, void *d, void *e);

unsigned short func_02091310(void *a, int b);

void func_020913b0(unsigned char *arg0)
{
    unsigned int val;

    func_02091468(arg0);
    val = 0;
    *(unsigned short *) (arg0 + 0x39c) = (unsigned short) val;
}

int func_02091358(struct UnkStruct_02091358 *obj, unsigned int idx, int a, int b, int c, int d)
{
    int result = -1;
    if (idx < 0x66) {
        int (*fn)(int, int, int, int, int) = data_020e2c1c[idx].func;
        if (fn != 0) {
            int r = fn(idx, a, b, c, d);
            if (r == 0) {
                unsigned short old = obj->counter;
                obj->counter = old + 1;
                result = old;
            } else if (r == 2) {
                obj->counter++;
            }
        }
    }
    return result;
}

void func_0209132c(int a, int b)
{
    unsigned int idx;
    void (*handler)(int);

    if (b == -1) {
        return;
    }
    idx = (unsigned int) func_02091310((void *) a, b);
    if (idx >= 0x66) {
        return;
    }
    handler = data_020e2c20[idx].handler;
    if (handler == 0) {
        return;
    }
    handler(b);
}

unsigned short func_02091310(void *a, int b)
{
    void *result;
    unsigned short ret;
    result = func_02091444(a, b, a, 0x20);
    ret = 0x66;
    if (result != 0) {
        ret = *(unsigned short *) ((char *) result + 0x18);
    }
    return ret;
}

void func_02091300(void)
{
    func_020913b0((unsigned char *) ((int) ((int *) data_021d52d8)));
}

int func_020912d4(int a, int b, int c, int d)
{
    return func_02091358((struct UnkStruct_02091358 *) ((unsigned int) data_021d52d8), a, b, c, d, -1);
}

int func_020912ac(int p0, short p1, int p2, int p3)
{
    short local = p1;
    return func_02091358((struct UnkStruct_02091358 *) (((int *) data_021d52d8)), p0, p2, p3, (int) (&local), -1);
}

void func_0209129c(void *arg0)
{
    func_0209132c((int) ((void *) data_021d52d8), (int) arg0);
}

void func_02091278(void *a, void *b, void *c, void *d)
{
    void *sp[2];
    sp[0] = d;
    func_020913f0((void *) data_021d52d8, a, b, c, sp[0]);
}

int func_02091254(int a, int b, int c, int d)
{
    return func_02091358((struct UnkStruct_02091358 *) (((int *) data_021d52d8)), 100, b, c, d, a);
}

int func_02091230(int p0, int p1, int p2, int p3)
{
    return func_02091358((struct UnkStruct_02091358 *) (((int *) data_021d52d8)), 100, p1, p2, p3, p0);
}

int func_0209120c(int a, int b, int c, int d)
{
    return func_02091358((struct UnkStruct_02091358 *) ((unsigned int) data_021d52d8), 0x65, b, c, d, a);
}
