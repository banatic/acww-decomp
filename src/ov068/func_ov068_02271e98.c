/* func_ov068_02271e98 @ 0x02271e98, 0x36 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *p);
extern void func_0200e90c(void *p, unsigned int size, unsigned int b, unsigned int c);
extern unsigned int func_0200e894(unsigned int a, void *p);
extern void func_0200e91c(void *p);

unsigned int func_ov068_02271e98(unsigned int a, unsigned int b, unsigned int c)
{
    unsigned char local[0x20];
    unsigned int result;

    func_0200e92c(local);
    func_0200e90c(local, 0x88, b, c);
    result = func_0200e894(a, local);
    func_0200e91c(local);
    return result;
}
