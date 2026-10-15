/* func_ov096_0229cbe0 @ 0x0229cbe0, 0x30 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov096_0229ddd8(void *a);
extern void func_ov002_02209740(void *dst, unsigned char c, void *d);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

unsigned char *func_ov096_0229cbe0(void *a, void *b)
{
    func_ov096_0229ddd8(a);
    func_ov002_02209740((char *) a + 0x2564, *(unsigned char *) ((char *) a + 0xbd), b);
    return func_ov002_02208098((void *) (a), 0x22);
}
