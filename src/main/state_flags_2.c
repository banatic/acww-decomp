/* state_flags_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206f5cc @ 0x0206f5cc, 0xc bytes, Thumb
 * func_0206f5b0 @ 0x0206f5b0, 0x1c bytes, Thumb
 */

extern void func_0206fef0(int);
extern void func_0206fee0(int);
extern unsigned char data_021cfc54[];

void func_0206f5cc(void)
{
    func_0206fef0(0x80);
}

void func_0206f5b0(void)
{
    unsigned char *ptr;

    func_0206fee0(0x80);
    ptr = (unsigned char *) data_021cfc54;
    *ptr = 0x37;
}
