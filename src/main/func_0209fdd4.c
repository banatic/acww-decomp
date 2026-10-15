/* func_0209fdd4 @ 0x0209fdd4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02073100(void);
extern int func_020eb070(void);
extern unsigned char data_021f3c18;

int func_0209fdd4(void)
{
    if ((func_02073100(), func_020eb070()) != 0) {
        data_021f3c18 = 1;
        return 1;
    }
    return 0;
}
