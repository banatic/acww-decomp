/* func_020415a8 @ 0x020415a8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203e37c(void);
extern unsigned char data_021c75a0[3];

int func_020415a8(void)
{
    int ret = 0;

    if (func_0203e37c() == 0) {
        data_021c75a0[0] = 0;
        data_021c75a0[2] = 0;
    } else {
        ret = 1;
        data_021c75a0[2] = 1;
    }
    return ret;
}
