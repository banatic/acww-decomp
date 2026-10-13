/* func_020b660c @ 0x020b660c, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b67c0(int p);

int func_020b660c(int p0)
{
    if (func_020b67c0(p0) != 0) {
        goto fail;
    }
    if (p0 == 0x2c) {
        goto fail;
    }
    if (p0 == 0x2d) {
        goto fail;
    }
    if (p0 == 0x2e) {
        goto fail;
    }
    if (p0 == 0x2f) {
        goto fail;
    }
    if ((unsigned char) (p0 + 0xf4) > 2) {
        goto ok;
    }
fail:
    return 0;
ok:
    return 1;
}
