/* state_flags_6: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206fef0 @ 0x0206fef0, 0x10 bytes, Thumb
 * func_0206fee0 @ 0x0206fee0, 0x10 bytes, Thumb
 * func_0206fec8 @ 0x0206fec8, 0x18 bytes, Thumb
 * func_0206febc @ 0x0206febc, 0xc bytes, Thumb
 * func_0206feb0 @ 0x0206feb0, 0xc bytes, Thumb
 * func_0206fea4 @ 0x0206fea4, 0xc bytes, Thumb
 */

extern unsigned short data_021cfc6c;

void func_0206fef0(unsigned short param)
{
    data_021cfc6c |= param;
}

void func_0206fee0(unsigned short r0)
{
    unsigned short r2;
    r2 = data_021cfc6c;
    r2 &= ~r0;
    data_021cfc6c = r2;
}

int func_0206fec8(unsigned int param)
{
    if ((param & data_021cfc6c) == param) {
        return 1;
    } else {
        return 0;
    }
}

void func_0206febc(void)
{
    func_0206fee0(1);
}

void func_0206feb0(void)
{
    func_0206fef0(1);
}

int func_0206fea4(void)
{
    return func_0206fec8(1);
}
