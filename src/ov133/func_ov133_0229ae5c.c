/* func_ov133_0229ae5c @ 0x0229ae5c, 0x30 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

int func_ov133_0229ae5c(unsigned char *p)
{
    if (p[0x9D] == 0) {
        goto ret0;
    }
    p[0x9D]--;
    if (p[0x9D] != 0) {
        goto ret0;
    }
    p[0x9D] = 2;
    return 1;
ret0:
    return 0;
}
