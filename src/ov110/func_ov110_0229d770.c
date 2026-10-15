/* func_ov110_0229d770 @ 0x0229d770, 0x48 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207d24(unsigned char *ptr, int flag);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov110_0229cd14(unsigned char *self, int val);
extern void func_ov110_0229cde0(unsigned char *self);
extern void func_ov094_022999c0(void);

void func_ov110_0229d770(unsigned char *self, int val)
{
    self[0xf4] = (unsigned char) val;
    func_ov002_02207d24(self + 0x21f8, 1);
    func_ov110_0229cd14(self, val);
    if (self[0xf1] == 1) {
        func_ov002_02208098((void *) (self), 3);
    }
    func_ov110_0229cde0(self);
    func_ov094_022999c0();
}
