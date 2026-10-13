/* func_ov110_0229da98 @ 0x0229da98, 0x54 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f9c(const unsigned char *p);
extern void func_ov110_0229d4a8(unsigned char *self);
extern void func_ov110_0229ce44(unsigned char *self);
extern void func_ov002_02208098(unsigned char *self, int n);
extern void func_ov094_022999d8(void);
extern void func_ov110_0229d6c4(unsigned char *self, unsigned char b, int n);
extern void func_ov110_0229cdb4(unsigned char *self);

void func_ov110_0229da98(unsigned char *self)
{
    unsigned char b;
    if (func_ov002_02209f9c(self + 0x22e0) == 0) {
        b = self[0xf7];
        if (self[0xf5] == b) {
            func_ov110_0229d4a8(self);
            func_ov110_0229ce44(self);
            func_ov002_02208098(self, 4);
            func_ov094_022999d8();
        } else {
            func_ov110_0229d6c4(self, b, 4);
        }
    } else {
        func_ov110_0229cdb4(self);
    }
}
