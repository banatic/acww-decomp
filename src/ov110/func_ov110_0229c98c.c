/* func_ov110_0229c98c @ 0x0229c98c, 0x3c bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207d24(void *ptr, int value);
extern void func_ov002_0220a374(void *ptr, int value);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov110_0229c98c(void *self, unsigned char value)
{
    func_ov002_02207d24((char *) self + 0x21f8, 1);
    ((char *) self)[0xf7] = value;
    func_ov002_0220a374((char *) self + 0x22e0, 5);
    func_ov002_02208098((void *) (self), 0xd);
}
