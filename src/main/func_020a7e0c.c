/* func_020a7e0c @ 0x020a7e0c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208ffac(void);
extern unsigned char data_021f43f4;

void func_020a7e0c(void)
{
    if (func_0208ffac()) {
        data_021f43f4 = 1;
    } else {
        data_021f43f4 = 0;
    }
}
