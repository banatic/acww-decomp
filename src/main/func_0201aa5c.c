/* func_0201aa5c @ 0x0201aa5c, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e8870(void *param1, int param2, int param3);

void func_0201aa5c(void *param0)
{
    short *ptr;
    short value;

    ptr = (short *) param0;
    value = ptr[0x11];
    if (value != 0) {
        func_020e8870((char *) param0 + 0x22, 0, ptr[0x12]);
    }
    value = ptr[0x0D];
    if (value != 0) {
        func_020e8870((char *) param0 + 0x1A, 0, ptr[0x0E]);
    }
}
