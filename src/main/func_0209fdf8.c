/* func_0209fdf8 @ 0x0209fdf8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02073100(void);
extern int func_020eb070(void);
extern char data_021f3c04;

int func_0209fdf8(void)
{
    if ((func_02073100(), func_020eb070())) {
        data_021f3c04 = 1;
        return 1;
    }
    return 0;
}
