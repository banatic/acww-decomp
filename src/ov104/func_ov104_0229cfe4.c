/* func_ov104_0229cfe4 @ 0x0229cfe4, 0x2c bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov104_0229d1b8(void *);
extern void func_ov002_022096d8(void *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov104_0229cfe4(void *self)
{
    unsigned char *p;
    p = (unsigned char *) self + 0xbc;
    *p = 4;
    func_ov104_0229d1b8(self);
    func_ov002_022096d8((char *) self + 0x2504, 0);
    func_ov002_02208098((void *) (self), 0x18);
}
