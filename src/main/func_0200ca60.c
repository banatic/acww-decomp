/* func_0200ca60 @ 0x0200ca60, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020113e0(void *a, short b);
extern int func_0201138c(void *a, int b);
extern void func_0201107c(void *self, int *r);
extern int func_020912d4(int a, void *b, void *c, int d);

void func_0200ca60(void *self)
{
    char *base714;
    int ret;

    base714 = (char *) self + 0x7d4;
    func_020113e0((char *) self + 0x8e, *(short *) ((char *) self + 0x7d4));
    {
        void *p = *(void **) ((char *) self + 0x98);
        ret = func_0201138c(p, 0);
        func_0201107c(self, &ret);
        if (ret != 0) {
            return;
        }
        if (p == 0) {
            return;
        }
        func_020912d4(0x29, (char *) self + 0x5c, base714 + 2, 0);
    }
}
