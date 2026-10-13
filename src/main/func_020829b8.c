/* func_020829b8 @ 0x020829b8, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02082afc(void *base, unsigned short *tag);

void *func_020829b8(void *base, unsigned short *tag)
{
    unsigned short val;
    int idx;
    void *result = 0;

    val = *tag;
    if (((val & 0xF000) >> 12) == 0xE) {
        idx = func_02082afc(base, tag);
        if (idx >= 0 && idx < 8) {
            result = *(void **) ((char *) base + (idx << 3));
        }
    }
    return result;
}
