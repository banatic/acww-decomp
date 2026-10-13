/* func_0209f150 @ 0x0209f150, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0209f150(unsigned int *ptr, unsigned int bit)
{
    unsigned int word;
    unsigned int shift;
    int result;

    word = bit >> 5;
    shift = bit & 0x1f;

    if ((int) word >= 1) {
        goto fail;
    }
    result = 1;
    if ((*(unsigned int *) ((char *) ptr + word * 4 + 0x173f4) & (1 << shift)) != 0) {
        goto done;
    }
fail:
    result = 0;
done:
    return result;
}
