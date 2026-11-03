/* shop_answers: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b024c @ 0x020b024c, 0x10 bytes, Thumb
 * func_020b023c @ 0x020b023c, 0x10 bytes, Thumb
 * func_020b0234 @ 0x020b0234, 0x8 bytes, Thumb
 * func_020b0200 @ 0x020b0200, 0x34 bytes, Thumb
 * func_020b01f0 @ 0x020b01f0, 0x10 bytes, Thumb
 * func_020b01dc @ 0x020b01dc, 0x14 bytes, Thumb
 */

extern int func_02073d90(void *ptr);
extern unsigned char *data_020ccf94;

void func_020b0234(unsigned char *p0);

void *func_020b024c(void *arg)
{
    func_020b0234((unsigned char *) arg);
    return arg;
}

int func_020b023c(int arg)
{
    func_020b0234((unsigned char *) arg);
    return arg;
}

void func_020b0234(unsigned char *p0)
{
    p0[0] = 0;
    p0[1] = 0;
}

void func_020b0200(unsigned char *param)
{
    unsigned char *base;

    param[1] = 0;
    base = data_020ccf94;
    if (func_02073d90(base)) {
        base += 0x6c;
        param[0] = *base - 1;
    } else {
        param[0] = 0;
    }
}

int func_020b01f0(void *param)
{
    unsigned char r1;
    unsigned char r0;
    r1 = *(unsigned char *) ((char *) param + 1);
    r0 = *(unsigned char *) param;
    if (r1 < r0) {
        return 0;
    }
    return 1;
}

int func_020b01dc(unsigned char *r0)
{
    unsigned char r2;
    unsigned char r1;

    r2 = r0[1];
    r1 = r0[0];
    if (r2 < r1) {
        r1 = r2 + 1;
        r0[1] = r1;
    }
    return func_020b01f0(r0);
}
