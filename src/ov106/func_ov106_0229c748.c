/* func_ov106_0229c748 @ 0x0229c748, 0x50 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov106_0229c354(unsigned int self, int mask);
extern void func_ov106_0229c894(unsigned int self, int value);
extern void func_ov002_02208d30(void *addr, int value);
extern void func_ov002_02208d4c(void *addr, int idx, int size);

static __inline void *base(unsigned int self)
{
    return (void *) (self + 0x26ec);
}

void func_ov106_0229c748(unsigned int self)
{
    func_ov106_0229c354(self, 0x00010000);
    func_ov002_02208d30(base(self), 4);
    func_ov002_02208d4c(base(self), 0x1a, 4);
    func_ov002_02208d4c(base(self), 0x15, 2);
    func_ov002_02208d4c(base(self), 0x19, 4);
    func_ov106_0229c894(self, 0);
}
