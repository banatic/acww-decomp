/* func_02042324 @ 0x02042324, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204234c(void);
extern int func_020422a0(void);

extern unsigned char data_021c779c[];

int func_02042324(void)
{
    int result = 0;
    int *ptr = (int *) data_021c779c;

    if (*(ptr + 8) != 0) {
        result = func_0204234c();
        if (result == 0) {
            func_020422a0();
        }
    }

    return result;
}
