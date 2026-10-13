/* func_02099020 @ 0x02099020, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02099020(unsigned char *base, unsigned int index)
{
    int high = (int) (index >> 5);
    int low = index & 0x1f;
    int result;
    if (high >= 2) {
        goto zero;
    }
    result = 1;
    if ((1 << low) & *(unsigned int *) (base + high * 4 + 0x23f8)) {
        goto end;
    }
zero:
    result = 0;
end:
    return result;
}
