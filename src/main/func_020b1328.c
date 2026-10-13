/* func_020b1328 @ 0x020b1328, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020b15b0(void);
extern int func_020b1974(void *p, int i);

int func_020b1328(int *out)
{
    void *p;
    int i;
    int flag;

    *out = -1;
    p = func_020b15b0();
    i = 0;
    flag = 0;
    while (i < 16) {
        int mask = 1 << i;
        if (*(unsigned short *) ((char *) p + 0x4A2) & mask) {
            if (func_020b1974(p, i)) {
                if (*out == ~flag) {
                    *out = i;
                } else {
                    return 2;
                }
            } else {
                *(unsigned short *) ((char *) p + 0x4A2) &= ~mask;
            }
        }
        i++;
    }
    if (*out == -1) {
        return 0;
    }
    return 1;
}
