/* func_020afb90 @ 0x020afb90, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209e474(unsigned int *local);

int func_020afb90(void *p)
{
    unsigned int local[2];
    unsigned int v;
    unsigned int r;
    unsigned char b;
    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    v = *(unsigned short *) ((char *) p + 0x5a);
    r = v << 0x1b;
    r = r >> 0x1b;
    if (r == 0) {
        goto L0;
    }
    b = ((unsigned char *) local)[2];
    if ((int) b < (int) r) {
        goto L1;
    }
    if (b >= 0x17u) {
        goto L1;
    }
    return 1;
L1:
    return 0;
L0:
    return 0;
}
