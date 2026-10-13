/* func_0203ed78 @ 0x0203ed78, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

// placeholder, not used

int func_0203ed78(unsigned short *param0, unsigned short param1)
{
    unsigned short value;
    value = *(unsigned short *) ((unsigned char *) param0 + 0xe8);
    if (value & param1) {
        return 1;
    }
    return 0;
}
