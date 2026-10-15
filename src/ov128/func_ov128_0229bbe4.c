/* func_ov128_0229bbe4 @ 0x0229bbe4, 0x2c bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a164(void *ptr);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov128_0229bbe4(char *self)
{
    unsigned char *p;
    unsigned char val;

    func_ov002_0220a164((void *) (self + 0x110));
    p = (unsigned char *) self;
    p += 0x8d;
    val = *p;
    self[0x2d6a] = val;
    func_ov002_02208098((void *) (self), 9);
}
