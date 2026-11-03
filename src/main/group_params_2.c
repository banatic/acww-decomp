/* group_params_2: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206f728 @ 0x0206f728, 0x24 bytes, Thumb
 * func_0206f6f8 @ 0x0206f6f8, 0x30 bytes, Thumb
 * func_0206f6d4 @ 0x0206f6d4, 0x24 bytes, Thumb
 * func_0206f6b0 @ 0x0206f6b0, 0x24 bytes, Thumb
 * func_0206f6a4 @ 0x0206f6a4, 0xc bytes, Thumb
 * func_0206f698 @ 0x0206f698, 0xc bytes, Thumb
 * func_0206f68c @ 0x0206f68c, 0xc bytes, Thumb
 * func_0206f680 @ 0x0206f680, 0xc bytes, Thumb
 * func_0206f674 @ 0x0206f674, 0xc bytes, Thumb
 * func_0206f668 @ 0x0206f668, 0xc bytes, Thumb
 * func_0206f640 @ 0x0206f640, 0x26 bytes, Thumb
 * func_0206f614 @ 0x0206f614, 0x2c bytes, Thumb
 * func_0206f608 @ 0x0206f608, 0xc bytes, Thumb
 * func_0206f5fc @ 0x0206f5fc, 0xc bytes, Thumb
 * func_0206f5e4 @ 0x0206f5e4, 0x18 bytes, Thumb
 * func_0206f5d8 @ 0x0206f5d8, 0xc bytes, Thumb
 */

extern int func_0206fbf8(int);
extern int data_021cfc80;   // 0x021cfc80
extern unsigned short data_021cfc70;
extern void func_0206fc1c(int, int);
extern void func_0206f4e4(void);
extern unsigned char data_021cfc60;
extern unsigned char data_021cfc90[5];

int func_0206f728(int param)
{
    if (func_0206fbf8(0x2b)) {
        (*(volatile unsigned short *) &data_021cfc70) = (unsigned short) param;
        return 1;
    }
    return 0;
}

int func_0206f6f8(int a, int b)
{
    if (func_0206fbf8(0x2c) != 0) {
        data_021cfc80 = b;
        (*(short *) &data_021cfc70) = a;
        return 1;
    } else {
        return 0;
    }
}

int func_0206f6d4(int arg0)
{
    int result;
    int r4 = arg0;
    if (func_0206fbf8(0x29) != 0) {
        data_021cfc70 = (unsigned short) r4;
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_0206f6b0(unsigned short param)
{
    if (func_0206fbf8(42)) {
        data_021cfc70 = param;
        return 1;
    }
    return 0;
}

unsigned short func_0206f6a4(void)
{
    return data_021cfc70;
}

void func_0206f698(unsigned short value)
{
    data_021cfc70 = value;
}

void func_0206f68c(unsigned short param)
{
    data_021cfc70 = param;
}

unsigned short func_0206f680(void)
{
    return data_021cfc70;
}

void func_0206f674(unsigned short value)
{
    data_021cfc70 = value;
}

unsigned short func_0206f668(void)
{
    return data_021cfc70;
}

int func_0206f640(int p0, int p1, int p2)
{
    if (func_0206fbf8(p0)) {
        func_0206fc1c(p1, p2);
        return 1;
    } else {
        return 0;
    }
}

void func_0206f614(void)
{
    data_021cfc60 = 4;
    data_021cfc90[0] = 0;
    data_021cfc90[1] = 2;
    data_021cfc90[2] = 6;
    data_021cfc90[3] = 7;
    data_021cfc90[4] = 8;
    func_0206f4e4();
}

unsigned char func_0206f608(void)
{
    return data_021cfc60;
}

void func_0206f5fc(unsigned char a)
{
    data_021cfc60 = a;
}

unsigned char func_0206f5e4(unsigned char input)
{
    if (input == 0xFF) {
        input = data_021cfc60;
    }
    return data_021cfc90[input];
}

void func_0206f5d8(int index, unsigned char value)
{
    data_021cfc90[index] = value;
}
