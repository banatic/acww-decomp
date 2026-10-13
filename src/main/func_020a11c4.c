/* func_020a11c4 @ 0x020a11c4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *data_021f3c3c;

int func_020a11c4(void)
{
    if (data_021f3c3c) {
        return data_021f3c3c[0x100];
    } else {
        return 4;
    }
}
