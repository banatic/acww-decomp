/* func_ov110_0229c8f4 @ 0x0229c8f4, 0x2c bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov110_0229ca48(void *);
extern void func_ov002_022096d8(void *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov110_0229c8f4(void *self)
{
    char *p = (char *) self + 0xf9;
    *p = 1;
    func_ov110_0229ca48(self);
    func_ov002_022096d8((char *) self + 0x2344, 0);
    func_ov002_02208098((void *) (self), 0x13);
}
