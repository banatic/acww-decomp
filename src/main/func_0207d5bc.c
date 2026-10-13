/* func_0207d5bc @ 0x0207d5bc, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020819d0(void *);

void func_0207d5bc(void *arg0)
{
    void *p;
    int i;

    p = arg0;
    for (i = 0; i < 8; i++) {
        func_020819d0(p);
        p = (char *) p + 0x80;
    }
}
