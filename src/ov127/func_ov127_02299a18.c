/* func_ov127_02299a18 @ 0x02299a18, 0x38 bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov127_02299a50(void *base, int x, int y, int arg4, int arg5);

int func_ov127_02299a18(void *base, int x, int y, int arg4, int arg5)
{
    int offset = ((x >> 3) + ((y >> 3) << 5)) * 2;
    int val = *(unsigned short *) ((char *) base + offset + 0x2024);
    if ((val & 0x3ff) == 0x20) {
        return func_ov127_02299a50(base, x, y, arg4, arg5);
    }
    return 0;
}
