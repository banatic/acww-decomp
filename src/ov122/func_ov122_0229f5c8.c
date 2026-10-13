/* func_ov122_0229f5c8 @ 0x0229f5c8, 0x2e bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

int func_ov122_0229f5c8(void *param)
{
    unsigned char v = *(unsigned char *) ((char *) param + 0xaa);
    switch (v) {
        case 0:
        case 1:
            return 10;
        case 2:
            return 0x40;
        case 3:
            return 0x10;
    }
    return 0;
}
