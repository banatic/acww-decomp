/* func_ov100_0229c940 @ 0x0229c940, 0x30 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov100_0229ca9c(void *);
extern void func_ov002_022096d8(void *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov100_0229c940(void *self)
{
    ((unsigned char *) self)[0x2925] = 1;
    func_ov100_0229ca9c(self);
    func_ov002_022096d8((char *) self + 0x22d8, 0);
    func_ov002_02208098((void *) (self), 0x13);
}
