/* func_020c1ae4 @ 0x020c1ae4, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201b38c(int, int);
extern void func_0201b388(int, int);
extern int func_02016014(void *, void *);

void func_020c1ae4(void *self, void *arg)
{
    int *p = (int *) ((char *) self + 0xb0);
    func_0201b38c(*p + 0x2a0, 0);
    func_0201b388(*p + 0x2a0, 1);
    func_02016014(self, arg);
}
