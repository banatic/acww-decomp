/* func_0206f5b0 @ 0x0206f5b0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206fee0(int);

extern unsigned char data_021cfc54[];

void func_0206f5b0(void)
{
    unsigned char *ptr;

    func_0206fee0(0x80);
    ptr = (unsigned char *) data_021cfc54;
    *ptr = 0x37;
}
