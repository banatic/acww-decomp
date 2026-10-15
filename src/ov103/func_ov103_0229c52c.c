/* func_ov103_0229c52c @ 0x0229c52c, 0x5c bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208c58(void *p, void *q, int z);
extern int func_ov103_0229ccb4(void *p, int b);
extern int func_ov103_0229cc80(void *p, int b);
extern void func_ov002_02209910(void *p, int a, int b);
extern void func_ov002_0220970c(void *p, int a);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);

void func_ov103_0229c52c(unsigned char *self)
{
    func_ov002_02208c58(self + 0x22d8, self + 0x26c0, 0);

    {
        int t = func_ov103_0229ccb4(self, self[0x2da5]);
        int v = func_ov103_0229cc80(self, self[0x2da5]);

        func_ov002_02209910(self + 0x22d8, t, v);
    }

    func_ov002_0220970c(self + 0x22d8, 0);
    func_ov002_02208098(self, 0x14);
}
