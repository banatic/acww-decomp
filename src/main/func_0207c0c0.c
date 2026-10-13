/* func_0207c0c0 @ 0x0207c0c0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207f0c0(void *);

int func_0207c0c0(void *param)
{
    int i;
    void *p = param;
    int result = 0;

    for (i = 0; i < 8; i++) {
        if (func_0207f0c0(p)) {
            return i;
        }
        p = (char *) p + 0x7ec;
    }
    return -1;
}
