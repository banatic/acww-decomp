/* func_ov140_0229a544 @ 0x0229a544, 0x2c bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a164(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov140_0229a544(void *self)
{
    func_ov002_0220a164((char *) self + 0x128c);
    *((unsigned char *) ((char *) self + 0x8ae)) = *((unsigned char *) ((char *) self + 0x8d));
    func_ov002_02208098((void *) (self), 4);
}
