/* func_0205a41c @ 0x0205a41c, 0x138 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209f150(int *arg1, int arg2);
extern void func_0209f128(int *arg1, int arg2);
extern int func_02098844(int *arg1, int arg2);
extern int func_02099a28(unsigned int);
extern int func_02099020(int arg1, int arg2);
extern int func_02097ad0(int arg1);
extern void func_02066694(void *arg1);
extern int func_02099870(int arg1);
extern void func_02066024(void *arg1, void *arg2, void *arg3, void *arg4, void *arg5, int arg6);
extern unsigned short func_02065ed0(void *arg1, int arg2, int arg3);
extern int func_02097a54(void *arg1);
extern int func_020979f0(void *arg1, int arg2);
extern void func_02066688(void *arg1);

extern int data_021dc7a8;
extern int data_021dc7bc;
extern int data_020dd394;
extern int data_020dd3d8;
extern int data_020dd38c;

void func_0205a41c(int arg1, int arg2)
{
    int v5 = -1;
    int v6 = 1;
    int v7 = 0xfff1;
    unsigned char local2[4];
    unsigned char local1[0x100];
    int zero = 0;
    int i;

    if (func_0209f150(&data_021dc7a8, v6) == 0) {
        if (arg2 >= 0x11170) {
            v5 = 0x18;
            v6 = 1;
            v7 = 0x3854;
        }
    } else if (func_0209f150(&data_021dc7a8, 2) == 0) {
        if (arg2 >= 0x186a0) {
            v5 = 0x19;
            v6 = 2;
            v7 = 0x3858;
        }
    } else if (func_0209f150(&data_021dc7a8, 11) == 0) {
        if (arg2 >= 0x249f0) {
            v5 = 0x1a;
            v6 = 11;
            v7 = 0x385c;
        }
    }

    if (v5 == -1) {
        return;
    }

    for (i = 0; i < 4; i++) {
        int temp;
        int result;
        temp = func_02098844(&data_021dc7bc, i);
        if (temp == 0) {
            continue;
        }
        if (func_02099a28(temp) == 0) {
            continue;
        }
        if (func_02099020(temp, 0xe) == 0) {
            continue;
        }
        if (func_02097ad0(i) != 0) {
            continue;
        }
        func_02066694(local1);
        local2[0] = (unsigned char) v5;
        result = func_02099870(temp);
        func_02066024(local1, local2, &data_020dd3d8, &data_020dd38c, &data_020dd394, result);
        func_02065ed0(local1, v7, 1);
        if (func_02097a54(local1) != 0) {
            func_0209f128(&data_021dc7a8, v6);
            func_02066688(local1);
            return;
        } else if (func_020979f0(local1, zero) != 0) {
            func_0209f128(&data_021dc7a8, v6);
            func_02066688(local1);
            return;
        } else {
            func_02066688(local1);
        }
    }
}
