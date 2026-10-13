/* func_ov054_022625e0 @ 0x022625e0, 0x40 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec14(void);
extern int func_02035638(int);
extern int func_ov054_02260474(void *);

int func_ov054_022625e0(void *p)
{
    int r;
    if (!func_0202ec14()) {
        return 0;
    }
    r = *(int *) ((char *) p + 0x808);
    if (r == 0) {
        func_02035638(0x55);
    } else if (r == 1) {
        if (!func_ov054_02260474(p)) {
            func_02035638(0x56);
        }
    }
    return 1;
}
