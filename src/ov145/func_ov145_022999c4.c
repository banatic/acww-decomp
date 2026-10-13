/* func_ov145_022999c4 @ 0x022999c4, 0x60 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

void *func_ov145_022999c4(void *self, int off)
{
    static int inited = 0;
    static void *table[4];
    unsigned char sel;
    void *base;

    if (!(inited & 1)) {
        table[0] = (char *) self + 0xc8c;
        table[1] = (char *) self + 0xbac;
        table[2] = (char *) self + 0xc1c;
        table[3] = (char *) self + 0xb44;
        inited |= 1;
    }
    if (off < 0) {
        off = 0;
    }
    sel = *((unsigned char *) self + 0xc0);
    base = table[sel];
    return (char *) base + off * 2;
}
