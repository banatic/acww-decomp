/* menu_input: 23 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a806c @ 0x020a806c, 0x58 bytes, Thumb
 * func_020a8028 @ 0x020a8028, 0x44 bytes, Thumb
 * func_020a7ffc @ 0x020a7ffc, 0x2c bytes, Thumb
 * func_020a7fd4 @ 0x020a7fd4, 0x28 bytes, Thumb
 * func_020a7fac @ 0x020a7fac, 0x28 bytes, Thumb
 * func_020a7f84 @ 0x020a7f84, 0x28 bytes, Thumb
 * func_020a7f5c @ 0x020a7f5c, 0x28 bytes, Thumb
 * func_020a7f34 @ 0x020a7f34, 0x28 bytes, Thumb
 * func_020a7f0c @ 0x020a7f0c, 0x28 bytes, Thumb
 * func_020a7ee4 @ 0x020a7ee4, 0x28 bytes, Thumb
 * func_020a7ebc @ 0x020a7ebc, 0x28 bytes, Thumb
 * func_020a7e94 @ 0x020a7e94, 0x28 bytes, Thumb
 * func_020a7e88 @ 0x020a7e88, 0xc bytes, Thumb
 * func_020a7e7c @ 0x020a7e7c, 0xc bytes, Thumb
 * func_020a7e70 @ 0x020a7e70, 0xc bytes, Thumb
 * func_020a7e64 @ 0x020a7e64, 0xc bytes, Thumb
 * func_020a7e50 @ 0x020a7e50, 0x14 bytes, Thumb
 * func_020a7e44 @ 0x020a7e44, 0xc bytes, Thumb
 * func_020a7e30 @ 0x020a7e30, 0x14 bytes, Thumb
 * func_020a7e0c @ 0x020a7e0c, 0x24 bytes, Thumb
 * func_020a7dec @ 0x020a7dec, 0x20 bytes, Thumb
 * func_020a7dcc @ 0x020a7dcc, 0x20 bytes, Thumb
 * func_020a7dac @ 0x020a7dac, 0x20 bytes, Thumb
 */

struct UnkStruct_020a7f5c {
    unsigned char pad_00[2];
    unsigned short unk_02;
};

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c60;
extern unsigned char data_021f6c5c;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern unsigned short data_021fbe40[];
extern unsigned char data_021f43f0;
extern unsigned char data_021f43f4;
extern int func_0208ffac(void);
extern void func_0208ffcc(void);
extern void func_0208ffc0(void);

int func_020a7dcc(void);
int func_020a7dac(void);

int func_020a806c(int *a, int *b)
{
    int result = 0;
    int flag;

    if (func_020a7dac() == 0) {
        if (data_021fbdd8 != 0 && data_021fbddc != 0) {
            flag = 1;
        } else {
            flag = 0;
        }
        if (flag != 0) {
            int v1 = data_021f6c60;
            int v2 = data_021f6c5c;
            if (a) {
                *a = v1;
            }
            if (b) {
                *b = v2;
            }
            result = 1;
        }
    }
    return result;
}

int func_020a8028(int *param1, int *param2)
{
    int result = 0;
    int r5 = (int) param1;
    int r4 = (int) param2;

    if (func_020a7dac() == 0) {
        if (data_021fbdd8 != 0) {
            unsigned char r1 = data_021f6c58;
            unsigned char r0 = data_021f6c54;
            if (r5 != 0) {
                *(int *) r5 = r1;
            }
            if (r4 != 0) {
                *(int *) r4 = r0;
            }
            result = 1;
        }
    }
    return result;
}

int func_020a7ffc(void)
{
    int result = 0;
    if (func_020a7dcc() == 0) {
        result = (data_021fbe40[1] & 0xfff) != 0;
    }
    return result;
}

int func_020a7fd4(void)
{
    int r4 = 0;
    if (!func_020a7dcc()) {
        if (data_021fbe40[1] & 1) {
            r4 = 1;
        }
    }
    return r4;
}

int func_020a7fac(void)
{
    int result = 0;

    if (func_020a7dcc() != 0) {
        goto out;
    }
    if ((data_021fbe40[1] & 2) == 0) {
        goto out;
    }
    result = 1;

out:
    return result;
}

int func_020a7f84(void)
{
    int result = 0;
    if (func_020a7dcc() == 0) {
        result = (data_021fbe40[1] & 0x40) ? 1 : 0;
    }
    return result;
}

int func_020a7f5c(void)
{
    int ret = 0;
    if (!func_020a7dcc()) {
        if ((*(struct UnkStruct_020a7f5c *) data_021fbe40).unk_02 & 0x80) {
            ret = 1;
        }
    }
    return ret;
}

int func_020a7f34(void)
{
    int result = 0;

    if (func_020a7dcc() != 0) {
        goto out;
    }
    if ((data_021fbe40[1] & 8) == 0) {
        goto out;
    }
    result = 1;

out:
    return result;
}

int func_020a7f0c(void)
{
    int r4 = 0;
    if (!func_020a7dcc()) {
        if ((*(unsigned short *) data_021fbe40) & 1) {
            r4 = 1;
        }
    }
    return r4;
}

int func_020a7ee4(void)
{
    int r = 0;
    if (func_020a7dcc() != 0) {
        goto done;
    }
    if (((*(unsigned short *) data_021fbe40) & 2) == 0) {
        goto done;
    }
    r = 1;
done:
    return r;
}

int func_020a7ebc(void)
{
    int result = 0;
    if (func_020a7dcc() == 0) {
        result = ((*(unsigned short *) data_021fbe40) & 0x40) ? 1 : 0;
    }
    return result;
}

int func_020a7e94(void)
{
    int result = 0;

    if (func_020a7dcc() != 0) {
        goto out;
    }
    if (((*(unsigned short *) data_021fbe40) & 0x80) == 0) {
        goto out;
    }
    result = 1;

out:
    return result;
}

void func_020a7e88(void)
{
    (*(char *) &data_021f43f0) = 1;
}

void func_020a7e7c(void)
{
    data_021f43f0 = 0;
}

void func_020a7e70(void)
{
    data_021f43f4 = 0;
}

void func_020a7e64(void)
{
    data_021f43f4 = 1;
}

int func_020a7e50(void)
{
    if (data_021f43f4 == 0) {
        return 1;
    } else {
        return 0;
    }
}

unsigned char func_020a7e44(void)
{
    return data_021f43f4;
}

void func_020a7e30(void)
{
    data_021f43f0 = 0;
    data_021f43f4 = 0;
}

void func_020a7e0c(void)
{
    if (func_0208ffac()) {
        data_021f43f4 = 1;
    } else {
        data_021f43f4 = 0;
    }
}

void func_020a7dec(void)
{
    if (data_021f43f4 != 0) {
        func_0208ffcc();
    } else {
        func_0208ffc0();
    }
}

int func_020a7dcc(void)
{
    return (data_021f43f0 != 0) && (data_021f43f4 == 0);
}

int func_020a7dac(void)
{
    if (data_021f43f0 != 0 && data_021f43f4 != 0) {
        return 1;
    }
    return 0;
}
