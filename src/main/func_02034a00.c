/* func_02034a00 @ 0x02034a00, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021c519c[];

int func_02034a00(unsigned int idx, unsigned short *src)
{
    if (idx >= 0x33) {
        goto fail;
    }
    data_021c519c[idx] = *src;
    return 1;
fail:
    return 0;
}
