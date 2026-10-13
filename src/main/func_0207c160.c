/* func_0207c160 @ 0x0207c160, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207f120(void *);

int func_0207c160(void *arg)
{
    int i;
    void *p = arg;
    for (i = 0; i < 8; i++) {
        if (func_0207f120(p)) {
            return i;
        }
        p = (char *) p + 0x7EC;
    }
    return -1;
}
