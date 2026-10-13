/* func_0206223c @ 0x0206223c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020de368[][2];

int func_0206223c(int a, int b)
{
    if (a < 0x49) {
        unsigned char flag = (b == 0);
        return data_020de368[a][flag];
    } else {
        return func_0206223c(0, b);
    }
}
