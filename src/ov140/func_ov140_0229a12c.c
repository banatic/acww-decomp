/* func_ov140_0229a12c @ 0x0229a12c, 0x30 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

unsigned char *func_ov140_0229a12c(unsigned char *base)
{
    if (base[0x8e6] < 3) {
        goto then_path;
    }
    return base + 0x1b94;
then_path:
    base[0x8e6]++;
    return base + 0x1abc + (base[0x8e6] - 1) * 0x6c;
}
