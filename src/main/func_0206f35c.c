/* func_0206f35c @ 0x0206f35c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021cfc14;
extern char data_021cfc2c[];
extern int func_0205bfdc(char *ptr);

void func_0206f35c(void)
{
    if (data_021cfc14 & 1) {
        func_0205bfdc(data_021cfc2c);
        data_021cfc14 &= ~1;
    }
}
