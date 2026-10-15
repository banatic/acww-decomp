/* func_ov140_0229a244 @ 0x0229a244, 0x3c bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_ov140_0229a15c(void *receiver);
extern int func_ov140_0229a1a4(void *p, char *entry);

int func_ov140_0229a244(void *p)
{
    char *base;
    int i, count;

    base = (char *) func_ov140_0229a15c(p);
    count = 0;
    i = count;
    for (; i < 0x20; i++) {
        if (func_ov140_0229a1a4(p, base + 0x180 + i * 0x23)) {
            count++;
        }
    }
    return count;
}
