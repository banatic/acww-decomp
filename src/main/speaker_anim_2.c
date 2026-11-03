/* speaker_anim_2: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02016638 @ 0x02016638, 0x12c bytes, Thumb
 * func_02016618 @ 0x02016618, 0x20 bytes, Thumb
 * func_020165f4 @ 0x020165f4, 0x24 bytes, Thumb
 * func_020165bc @ 0x020165bc, 0x36 bytes, Thumb
 * func_02016530 @ 0x02016530, 0x8c bytes, Thumb
 * func_02016520 @ 0x02016520, 0x10 bytes, Thumb
 * func_0201651c @ 0x0201651c, 0x4 bytes, Thumb
 */

extern void func_02054768(char *a, int b, int c);
extern void func_020547b0(char *a, int b, unsigned short c, int d, int e, int f, int g, int h);
extern void func_02054188(char *a, int b, int c);
extern int func_0204c4e8(unsigned short *a);
extern int func_0205ceb0(int a);
extern int func_020168e4(int a, int b, int c);
extern int func_0205f670(unsigned short *a);
extern int func_0205cebc(int a);
extern unsigned int func_0205cf10(unsigned int);
extern int func_0205ceec(int a, unsigned int b);
extern int func_0205cec8(int a, unsigned int b);
extern int func_020164a0(int a, int b);
extern int func_02082fec(int a, int b);
extern void func_0205cc1c(int a, int b, int c, int d);
extern int func_0205cb94(void *object);
extern int NNS_G3dGetJntAnmSet(int arg);
extern int func_02107b44(int arg1, int arg2);
extern void func_02054240(int a, int b, int c, int d, int e, int f, int g, int h);
extern void func_020541b8(int a, int b, int c);
extern void func_020541e8(int, int, int);

void func_02016520(int a, int b);

void func_02016638(int param1, char *param2, unsigned short *param3, int param4, unsigned short param5)
{
    int cond;
    int ret;
    int x;
    int val;
    unsigned int count;
    unsigned int i;
    int tmp;
    int r2;

    if (func_0204c4e8(param3) == 0) {
        goto err_4;
    }
    if (func_0205ceb0(param4) == 3) {
        goto err_3;
    }

    cond = (*param3 >= 0x1369 && *param3 <= 0x1369);
    if (cond) {
        ret = func_020168e4(param1, 0x13f, 1);
        if (ret == 0) {
            return;
        }
        func_020547b0(param2 + 0xec, ret, param5, 0, 0x1000, 0, 0, 0);
        param2 += 0xec;
        func_02054188(param2, 0xc, 0xe);
    } else {
        x = func_0205f670(param3);
        if (x == 0x144) {
            goto err_2;
        }
        ret = func_020168e4(param1, x, 1);
        if (ret == 0) {
            return;
        }
        func_020547b0(param2 + 0xec, ret, param5, 0, 0x1000, 0, 0, 0);
        val = func_0205cebc(x);
        if (val >= 4) {
            goto err_1;
        }
        count = func_0205cf10(val);
        for (i = 0; i < count; i++) {
            tmp = func_0205ceec(val, i);
            r2 = func_0205cec8(val, i);
            func_02054188(param2 + 0xec, tmp, r2);
        }
    }
    return;

err_1:
    param2 += 0xec;
    func_02054768(param2, 0, 0);
    return;
err_2:
    param2 += 0xec;
    func_02054768(param2, 0, 0);
    return;
err_3:
    param2 += 0xec;
    func_02054768(param2, 0, 0);
    return;
err_4:
    param2 += 0xec;
    func_02054768(param2, 0, 0);
    return;
}

int func_02016618(int param)
{
    if (func_020164a0(param, 2) == 0x143) {
        return 1;
    } else {
        return 0;
    }
}

void func_020165f4(int a)
{
    int result = func_02082fec(a, 2);
    if (result) {
        func_0205cc1c(result, 0x143, 0, 0);
    }
}

int func_020165bc(int param)
{
    int forwarded_value;

    int result = 0;
    if (func_02016618(param) != 0) {
        if ((forwarded_value = (int) func_02082fec(param, 2)) != 0) {
            result = func_02107b44(NNS_G3dGetJntAnmSet(func_0205cb94((void *) forwarded_value)), 0);
        }
    }
    return result;
}

void func_02016530(int param1, int param2, int param3, int param4)
{
    int result;
    int r7;
    int count;
    unsigned int i;
    int tmp;
    int tmp2;

    result = func_020165bc(param1);
    if (result != 0) {
        func_02054240(param2 + 0xec, result, 0, 1, 0x1000, param3, param4, 0);
        r7 = func_0205cebc(0x143);
        if (r7 < 4) {
            count = (int) func_0205cf10(r7);
            for (i = 0; i < (unsigned int) count; i++) {
                tmp = func_0205ceec(r7, i);
                tmp2 = func_0205cec8(r7, i);
                func_020541b8(param2 + 0xec, tmp, tmp2);
            }
        } else {
            func_02016520(param1, param2);
        }
    } else {
        func_02016520(param1, param2);
    }
}

void func_02016520(int a, int b)
{
    func_020541e8(b + 0xec, 0, 0);
}

void func_0201651c(unsigned char *p0, int p1)
{
    p0[24] = p1;
}
