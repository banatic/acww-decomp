/* func_020a72d0 @ 0x020a72d0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f4320[];
extern void func_020a7738(const unsigned char *, unsigned char *, unsigned char *, unsigned char *);

int func_020a72d0(int param)
{
    unsigned char tmp[3];
    int result;
    if (param < 4) {
        func_020a7738(&data_021f4320[param * 3], tmp, tmp + 1, tmp + 2);
        result = tmp[2];
    } else {
        result = 0;
    }
    return result;
}
