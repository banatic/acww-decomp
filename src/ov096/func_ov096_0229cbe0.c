/* func_ov096_0229cbe0 @ 0x0229cbe0, 0x30 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov096_0229ddd8(void *a, void *b);
extern void func_ov002_02209740(void *dst, unsigned char c, void *d);
extern void func_ov002_02208098(void *a, int n);

void func_ov096_0229cbe0(void *a, void *b)
{
    func_ov096_0229ddd8(a, b);
    func_ov002_02209740((char *) a + 0x2564, *(unsigned char *) ((char *) a + 0xbd), b);
    func_ov002_02208098(a, 0x22);
}
