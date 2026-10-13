/* func_020bbbc0 @ 0x020bbbc0, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bbbf0(void *p0, void *p1, void *p2, void *p3);

void func_020bbbc0(void *p0, void *p1, void *p2, void *p3)
{
    int i;
    void *a = p0;
    void *b = p1;
    void *c = p2;
    void *d = p3;

    for (i = 0; i < 6; i++) {
        func_020bbbf0(a, b, c, d);
        a = (char *) a + 2;
        b = (char *) b + 2;
        c = (char *) c + 2;
    }
}
