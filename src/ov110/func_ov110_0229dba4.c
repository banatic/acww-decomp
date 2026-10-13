/* func_ov110_0229dba4 @ 0x0229dba4, 0x50 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(void *p);
extern void func_ov002_02208098(void *p, unsigned char b);
extern void func_ov110_0229cff8(void *p, unsigned char b);
extern void func_ov110_0229e7cc(void *p);
extern void func_ov110_0229cdb4(void *p);

void func_ov110_0229dba4(char *self)
{
    if (func_ov002_02209f64(self + 0x22e0) == 0) {
        func_ov002_02208098(self, *(unsigned char *) (self + 0xf8));
        if (((unsigned char) (*(unsigned char *) (self + 0xf8) + 0xfc)) <= 1) {
            func_ov110_0229cff8(self, *(unsigned char *) (self + 0xf5));
        }
        func_ov110_0229e7cc(self);
    }
    func_ov110_0229cdb4(self);
}
