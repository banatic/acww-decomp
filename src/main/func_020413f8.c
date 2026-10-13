/* func_020413f8 @ 0x020413f8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020415a8(void);
extern unsigned char data_021c75a0;

void func_020413f8(int param)
{
    int cond;
    if (param == 3) {
        cond = func_020415a8();
    } else {
        cond = 1;
    }
    if (cond) {
        data_021c75a0 = (unsigned char) param;
    }
}
