/* func_ov003_02223870 @ 0x02223870, 0xb8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov003_02223870(void *base, unsigned short *key, int idx, int idx2)
{
    int first;
    unsigned short c;

    first = 0;
    c = *key;
    if (c >= 0x2f && c <= 0x56) {
        first = 1;
    }
    if (first) {
        return (char *) base + 0xa60 + idx * 0x14c;
    } else if (c >= 0x57 && c <= 0x5b) {
        return (char *) base + idx2 * 0x530 + idx * 0x14c;
    } else if (c == 0x69) {
        return (char *) base + 0xa60 + idx * 0x14c;
    } else if (c >= 0x6a && c <= 0x6c) {
        return (char *) base + 0xf90 + idx * 0x14c;
    } else if (c == 0x6d) {
        return (char *) base + 0xf90 + idx * 0x14c;
    } else if (c >= 0x5d && c <= 0x61) {
        return (char *) base + 0xf90 + idx * 0x14c;
    } else if (c >= 0xc8 && c <= 0xcf) {
        return (char *) base + 0x18a4 + idx * 0x14c;
    } else {
        return (char *) base + idx2 * 0x530 + idx * 0x14c;
    }
}
