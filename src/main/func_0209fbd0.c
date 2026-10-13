/* func_0209fbd0 @ 0x0209fbd0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f3c20[];

int func_0209fbd0(void)
{
    int i;
    for (i = 2; i >= 0; i--) {
        if (data_021f3c20[i] != 0xff) {
            return data_021f3c20[i];
        }
    }
    return 4;
}
