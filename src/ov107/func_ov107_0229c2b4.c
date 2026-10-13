/* func_ov107_0229c2b4 @ 0x0229c2b4, 0x12 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_ov107_0229c2b4(void *self, unsigned int mask);

unsigned int func_ov107_0229c2b4(void *self, unsigned int mask)
{
    unsigned int *p = (unsigned int *) ((char *) self + 0x94);
    if (*p & mask) {
        return 1;
    }
    return 0;
}
