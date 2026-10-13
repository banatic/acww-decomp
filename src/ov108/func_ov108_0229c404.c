/* func_ov108_0229c404 @ 0x0229c404, 0x64 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov108_0229cc5c(void *p, int a);
extern void func_ov108_0229c794(void *p);
extern void func_ov108_0229c498(void *p, int a);
extern void func_ov002_02208d30(void *p, int a);
extern void func_ov002_02208d4c(void *p, int a, int b);
extern void func_ov002_02207d24(void *p, int a);

void func_ov108_0229c404(void *self, int a, int b)
{
    char *base = (char *) self;
    base[0x2b1] = (char) a;
    func_ov002_02208d30(base + 0x28e4, 1);
    func_ov108_0229cc5c(self, a);
    func_ov002_02208d4c(base + 0x28e4, 0xd, 0);
    func_ov002_02208d4c(base + 0x28e4, 2, 1);
    func_ov108_0229c794(self);
    if (b == 0) {
        func_ov002_02207d24(base + 0x23b0, 1);
    }
    func_ov108_0229c498(self, b);
}
