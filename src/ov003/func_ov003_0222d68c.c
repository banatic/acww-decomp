/* func_ov003_0222d68c @ 0x0222d68c, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

void func_ov003_0222d68c(unsigned char *p)
{
    p += 0x24f;
    *p = *p + 1;
    if (*p > 0x50) {
        *p = 0;
    }
}
