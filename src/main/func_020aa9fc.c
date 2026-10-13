/* func_020aa9fc @ 0x020aa9fc, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a80c4(int, int, int, int);

int func_020aa9fc(void)
{
    int r4;
    int result;

    r4 = 0;
    result = func_020a80c4(0xb8, 0x100, 0xa0, 0xb0);
    if (result != 0) {
        r4 = 1;
    }
    return r4;
}
