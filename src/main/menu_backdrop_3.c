/* menu_backdrop_3: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206eec4 @ 0x0206eec4, 0x4 bytes, Thumb
 * func_0206eec0 @ 0x0206eec0, 0x4 bytes, Thumb
 * func_0206ee7c @ 0x0206ee7c, 0x44 bytes, Thumb
 * func_0206ee4c @ 0x0206ee4c, 0x30 bytes, Thumb
 * func_0206ee08 @ 0x0206ee08, 0x44 bytes, Thumb
 * func_0206eda0 @ 0x0206eda0, 0x68 bytes, Thumb
 * func_0206ed2c @ 0x0206ed2c, 0x74 bytes, Thumb
 * func_0206ed04 @ 0x0206ed04, 0x28 bytes, Thumb
 * func_0206ec98 @ 0x0206ec98, 0x6c bytes, Thumb
 */

extern int func_0206efd4(int);
extern void func_02002708(int);
extern void func_02001bb4(int);
extern void func_02001d88(int);
extern void func_02001d1c(int);
extern void func_0206f2f0(void);
extern int func_0206f278(void);
extern void func_02001ca0(int, int, int, int);
extern void func_0206f150(void);
extern unsigned short data_021cfc20;
extern int func_0203b130(void);
extern void func_0206fcf8(void);
extern void func_0206fd54(int);
extern unsigned int data_021cfc28;
extern unsigned int data_021cfc24;
extern void func_02001ba4(int);
extern void func_02001afc(int);
extern void func_0206fcc8(void);
extern void func_0206feb0(void);
extern void func_020027f0(int);
extern int func_020ba540(int);
extern int data_021c8c9c;
extern unsigned char data_020e54a8;
int FX_MulFunc(int a, int b);
void func_020ba518(void);
void func_02001c30(int x);
extern void func_02001b34(int);
extern int func_0203ac5c(void);
extern int func_0203ac2c(void);
extern void func_0203de6c(int screen);
extern void func_0206eb0c(int);

int func_0206ee4c(void);

int func_0206eec4(void)
{
    return 0;
}

int func_0206eec0(void)
{
    return 1;
}

int func_0206ee7c(void)
{
    if (func_0206efd4(1)) {
        (*(short *) &data_021cfc20) = 2;
        func_02002708(1);
        func_02001bb4(2);
        func_02001d88(0x1f);
        func_02001d1c(0x1b);
        func_0206f2f0();
        return func_0206ee4c();
    } else {
        return 1;
    }
}

int func_0206ee4c(void)
{
    if (func_0206f278() == 0) {
        func_02001ca0(1, 0, 255, 192);
        data_021cfc20 = 3;
        func_0206f150();
    }
    return 1;
}

int func_0206ee08(void)
{
    if (func_0203b130()) {
        func_0206fcf8();
        func_0206fd54(0);
        data_021cfc28 = 0x1000;
        data_021cfc24 = 0x200;
        data_021cfc20 = 4;
    }
    return 1;
}

int func_0206eda0(void)
{
    int flag;

    if (func_0206efd4(5) != 0) {
        func_02001ba4(2);
        func_02001afc(0xf);
        func_02002708(5);
        data_021c8c9c = 1;
        func_0206fcc8();
        func_0206feb0();
        func_020027f0(1);
        data_021cfc20 = 5;
        flag = data_020e54a8 ? 0 : 1;
        if (flag != 0) {
            func_020ba540(1);
        }
    }

    return 1;
}

int func_0206ed2c(void)
{
    int val;
    unsigned int flag;
    int ret;

    val = (*(int *) &data_021cfc28);
    if (val == 0) {
        data_021cfc20 = 6;
        flag = (data_020e54a8 == 0) ? 1 : 0;
        if (flag > 0) {
            func_020ba518();
        }
        func_02001c30(0);
        return 1;
    } else {
        if (val > (*(int *) &data_021cfc24)) {
            (*(int *) &data_021cfc28) = val - (*(int *) &data_021cfc24);
        } else {
            (*(int *) &data_021cfc28) = 0;
        }
        ret = FX_MulFunc((*(int *) &data_021cfc28), (*(int *) &data_021cfc28));
        func_0206fd54(0x1000 - ret);
        return 1;
    }
}

int func_0206ed04(void)
{
    func_02001ba4(1);
    func_02001ba4(2);
    func_02001b34(0xe);
    data_021cfc20 = 7;
    return 1;
}

int func_0206ec98(void)
{
    unsigned int flag2;

    if (func_0203ac5c()) {
        func_0203ac2c();
    }
    flag2 = (data_020e54a8 == 0) ? 1 : 0;
    if (flag2 > 0) {
        func_0203de6c(0);
        func_020ba540(1);
        func_02001b34(8);
    }
    data_021cfc20 = 9;
    data_021cfc28 = 0x1000;
    data_021cfc24 = 0x200;
    func_0206eb0c(1);
    return 1;
}
