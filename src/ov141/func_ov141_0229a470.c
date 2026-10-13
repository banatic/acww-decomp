/* func_ov141_0229a470 @ 0x0229a470, 0x20 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

int func_ov141_0229a470(unsigned char *p)
{
    unsigned char b;
    b = p[0x1a8c];
    if ((unsigned char) (b + 0xfa) > 1) {
        goto compute;
    }
    return 0xae;
compute:
    return (b << 4) + 0x46;
}
