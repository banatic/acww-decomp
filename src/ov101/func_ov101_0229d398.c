/* func_ov101_0229d398 @ 0x0229d398, 0x78 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void);
extern int func_ov002_02208008(void *self);
extern int func_ov002_02209044(void *a, int b, void *c, int d);
extern void func_ov002_0220a1dc(void *a);
extern unsigned char *func_ov002_02208098(void *a, unsigned char value);
extern void func_ov101_0229c51c(void *self);
extern void func_ov101_0229c780(void *self);
extern void func_ov101_0229c720(void *self);

extern struct {
    unsigned short unk0;
    unsigned short unk2;
} data_021fbe40;

void func_ov101_0229d398(void *self)
{
    if (func_ov002_02208014() != 0) {
        func_ov101_0229c51c(self);
        return;
    }
    {
        int res = func_ov002_02208008(self);
        if (func_ov002_02209044((char *) self + 0x2300, res, (char *) self + 0xb8, 0) != 0) {
            func_ov101_0229c780(self);
            return;
        }
    }
    {
        unsigned short flags = data_021fbe40.unk2;
        if (flags & 1) {
            func_ov002_0220a1dc((char *) self + 0x229c);
            func_ov002_02208098(self, 9);
            return;
        }
        if (flags & 2) {
            func_ov101_0229c720(self);
        }
    }
}
