/* state_flags_4: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206fd54 @ 0x0206fd54, 0xc bytes, Thumb
 * func_0206fd34 @ 0x0206fd34, 0x20 bytes, Thumb
 * func_0206fd10 @ 0x0206fd10, 0x24 bytes, Thumb
 * func_0206fd04 @ 0x0206fd04, 0xc bytes, Thumb
 * func_0206fcf8 @ 0x0206fcf8, 0xc bytes, Thumb
 * func_0206fcec @ 0x0206fcec, 0xc bytes, Thumb
 * func_0206fce0 @ 0x0206fce0, 0xc bytes, Thumb
 * func_0206fcd4 @ 0x0206fcd4, 0xc bytes, Thumb
 * func_0206fcc8 @ 0x0206fcc8, 0xc bytes, Thumb
 */

// 0x021cfc7c

extern unsigned char data_021cfc7c[];
extern int func_0206fec8(int param);
extern void func_0206fef0(int);
extern void func_0206fee0(int arg);

int func_0206fd04(void);

void func_0206fd54(unsigned int r0)
{
    (*(unsigned int * *) data_021cfc7c) = (unsigned int *) r0;
}

int func_0206fd34(void)
{
    int result;
    int *ptr;

    if (func_0206fd04() != 0) {
        ptr = (int *) data_021cfc7c;
        result = *ptr;
    } else {
        result = 0;
    }
    return result;
}

int func_0206fd10(void)
{
    if (func_0206fd04() != 0) {
        return (*(int *) data_021cfc7c);
    } else {
        return 0x1000;
    }
}

int func_0206fd04(void)
{
    return func_0206fec8(4);
}

void func_0206fcf8(void)
{
    func_0206fef0(4);
}

void func_0206fcec(void)
{
    func_0206fee0(4);
}

int func_0206fce0(void)
{
    return func_0206fec8(0x10);
}

void func_0206fcd4(void)
{
    func_0206fef0(0x10);
}

void func_0206fcc8(void)
{
    func_0206fee0(0x10);
}
