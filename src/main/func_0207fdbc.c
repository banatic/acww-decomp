/* func_0207fdbc @ 0x0207fdbc, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207ffa0(void *, int);
extern int func_0204c878(unsigned short *);

int func_0207fdbc(void *a, int i, int n)
{
    unsigned short *p;
    int best;
    int result;
    int t;
    if (func_0207ffa0(a, i) == 0) {
        goto fail;
    }
    p = (unsigned short *) ((char *) a + 0x78c) + i;
    best = 0x1869f;
    result = -1;
    for (; i < n; p++, i++) {
        if (func_0207ffa0(a, i) != 0) {
            if (*p != 0xfff1) {
                t = func_0204c878(p);
                if (t <= best) {
                    result = i;
                    best = t;
                }
            }
        }
    }
    return result;
fail:
    return -1;
}
