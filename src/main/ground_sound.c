/* ground_sound: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b1d88 @ 0x020b1d88, 0xcc bytes, Thumb
 * func_020b1d54 @ 0x020b1d54, 0x34 bytes, Thumb
 * func_020b1d2c @ 0x020b1d2c, 0x28 bytes, Thumb
 * func_020b1d18 @ 0x020b1d18, 0x12 bytes, Thumb
 * func_020b1cb0 @ 0x020b1cb0, 0x68 bytes, Thumb
 */

extern int func_020b65c4(void);
extern int func_02031930(int);
extern int func_020b6744(int);
extern int func_020b67e8(int);
extern int func_020b67c0(int);
extern int func_020b66ec(int);
extern int func_020b6598(void);
extern unsigned char data_020e54a8;
extern unsigned short *func_ov004_022320d8(void);
extern unsigned char func_02062300(unsigned short *);
extern int func_02034270(void *p, unsigned int a, int b, int c);
extern void func_0203423c(void *p);
extern int func_02030890(int param);

int func_020b1d18(int argument0);

int func_020b1d88(int index)
{
    int call1;
    int r4;
    unsigned int flag;

    call1 = func_020b65c4();
    r4 = func_02031930(index);
    if (r4 == 0xffff) {
        flag = data_020e54a8 == 0;
        if (flag > 0) {
            r4 = 0xc8;
        } else if (func_020b6744(call1)) {
            r4 = func_020b1d18(5);
        } else if (func_020b67e8(call1) || func_020b67c0(call1)) {
            r4 = func_020b1d18(6);
        } else if (func_020b66ec(call1)) {
            r4 = func_020b1d18(5);
        } else {
            r4 = 0x4a6;
        }
    }
    if (r4 == 0xc0) {
        if (func_020b6598()) {
            unsigned int flag2 = data_020e54a8 == 0;
            if (flag2 != 0) {
                goto set877;
            }
            {
                int cond = 1;
                unsigned char x = (unsigned char) (call1 + 0xf5);
                if (x > 3 && call1 != 0x2f) {
                    cond = 0;
                }
                if (!cond) {
                    goto done;
                }
            }
        set877:
            r4 = 0x877;
        done:;
        }
    }
    return r4;
}

int func_020b1d54(int p0)
{
    unsigned int flag;
    unsigned short value;
    if (p0 == 0x1a) {
        flag = (data_020e54a8 == 1) ? 1u : 0u;
        if (flag == 0) {
            return p0;
        }
        value = *func_ov004_022320d8();
        return func_02062300(&value);
    }
    return p0;
}

int func_020b1d2c(unsigned int arg)
{
    char buffer[0x40];
    int result;
    func_02034270(buffer, arg, 0, 0);
    result = func_020b1d54(*(int *) (buffer + 0x34));
    func_0203423c(buffer);
    return result;
}

int func_020b1d18(int argument0)
{
    return func_020b1d88(func_020b1d54(argument0));
}

int func_020b1cb0(int param)
{
    if (func_02030890(param) == -1) {
        goto tail;
    }
    {
        int a = func_020b65c4();
        if (func_020b6744((unsigned int) a) != 0) {
            return func_020b1d18(5);
        }
        if (func_020b67e8(a) != 0 || func_020b67c0(a) != 0) {
            return func_020b1d18(6);
        }
        if (func_020b66ec(a) != 0) {
            return func_020b1d18(5);
        }
    }
tail:
    return func_020b1d18(func_020b1d2c(param));
}
