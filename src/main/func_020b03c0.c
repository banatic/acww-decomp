/* func_020b03c0 @ 0x020b03c0, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern int func_ov003_022361bc(int a, int b, int c, int d, int e);

int func_020b03c0(int a, int b, int c, int d, short e)
{
    unsigned int flag = (data_020e54a8 == 0) ? 1 : 0;
    if (flag > 0 && d > 0) {
        return func_ov003_022361bc(a, b, c, d, e);
    }
    return 0;
}
