/* func_020a835c @ 0x020a835c, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020a835c(int *p)
{
    int v = p[1];
    if (v < 15) {
        goto fail;
    }
    if (v > 25) {
        goto fail;
    }
    return 1;
fail:
    return 0;
}
