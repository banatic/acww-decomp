/* func_02016638 @ 0x02016638, 0x12c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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
