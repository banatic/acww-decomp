/* state_flags: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206f56c @ 0x0206f56c, 0x20 bytes, Thumb
 * func_0206f55c @ 0x0206f55c, 0x10 bytes, Thumb
 * func_0206f54c @ 0x0206f54c, 0x10 bytes, Thumb
 * func_0206f53c @ 0x0206f53c, 0x10 bytes, Thumb
 * func_0206f52c @ 0x0206f52c, 0x10 bytes, Thumb
 * func_0206f51c @ 0x0206f51c, 0x10 bytes, Thumb
 * func_0206f50c @ 0x0206f50c, 0x10 bytes, Thumb
 */

extern unsigned char data_021cfc54;
extern int func_0206fec8(int param);
extern void func_0206fef0(int param);
extern void func_0206fee0(int param);

int func_0206f56c(void)
{
    int result;

    if (data_021cfc54 != 0) {
        result = 0;
    } else {
        result = func_0206fec8(0x80);
    }

    return result;
}

void func_0206f55c(void)
{
    func_0206fef0(0x100);
}

void func_0206f54c(void)
{
    func_0206fee0(0x100);
}

int func_0206f53c(void)
{
    return func_0206fec8(0x100);
}

int func_0206f52c(void)
{
    return func_0206fec8(0x200);
}

void func_0206f51c(void)
{
    func_0206fef0(0x200);
}

void func_0206f50c(void)
{
    func_0206fee0((unsigned short) 0x200);
}
