/* motion_slots: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203fa98 @ 0x0203fa98, 0x4 bytes, Thumb
 * func_0203fa94 @ 0x0203fa94, 0x4 bytes, Thumb
 * func_0203fa84 @ 0x0203fa84, 0xe bytes, Thumb
 * func_0203fa58 @ 0x0203fa58, 0x2c bytes, Thumb
 * func_0203fa4c @ 0x0203fa4c, 0xc bytes, Thumb
 * func_0203fa2c @ 0x0203fa2c, 0x20 bytes, Thumb
 * func_0203fa14 @ 0x0203fa14, 0x18 bytes, Thumb
 * func_0203f9e0 @ 0x0203f9e0, 0x32 bytes, Thumb
 */

extern int func_020984e8(void);
extern int func_020992f0(unsigned int);

int func_0203f9e0(int arg0);

int func_0203fa98(int p0, int p1)
{
    return *(unsigned char *) ((char *) (p0) + (p1));
}

void func_0203fa94(int p0, int p1, int p2)
{
    *(unsigned char *) ((char *) (p0) + (p1)) = p2;
}

void func_0203fa84(unsigned char *r0)
{
    int r2;
    unsigned char r1;

    r2 = 0;
    r1 = 0xff;
    do {
        r0[r2] = r1;
        r2++;
    } while (r2 < 4);
}

int func_0203fa58(void)
{
    int i;
    int count;
    int a;

    a = func_020992f0((unsigned int) func_020984e8());
    count = 0;
    i = count;
    do {
        if (func_0203fa98(a, i) != 0xff) {
            count++;
        }
        i++;
    } while (i < 4);
    return count;
}

int func_0203fa4c(void)
{
    return func_0203f9e0(0xff);
}

void func_0203fa2c(int a, int b)
{
    func_0203fa94(func_020992f0((unsigned int) func_020984e8()), a, b);
}

int func_0203fa14(int arg)
{
    return func_0203fa98(func_020992f0(func_020984e8()), arg);
}

int func_0203f9e0(int arg0)
{
    int i;
    int result;
    int local_1;

    local_1 = func_020992f0((unsigned int) func_020984e8());
    i = 0;
    while (i < 4) {
        result = func_0203fa98(local_1, i);
        if (arg0 == result) {
            return i;
        }
        i++;
    }
    return -1;
}
