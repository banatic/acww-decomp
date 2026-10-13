/* func_020435fc @ 0x020435fc, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02043634(int a, int b, int c);

void func_020435fc(int p0, unsigned short p1)
{
    volatile unsigned short s;
    unsigned short a, b;
    int flag;
    s = 0xfff1;
    s = p1;
    flag = 0;
    b = s;
    a = s;
    if (a >= 0xa7 && b <= 0xc6) {
        flag = 1;
    }
    func_02043634(p0, flag ? 0x1a : 0x10, p1);
}
