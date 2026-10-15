/* func_ov109_0229c6f8 @ 0x0229c6f8, 0x64 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern char func_ov002_022090e4(void *ptr, int arg1);
extern int func_ov002_02208ae4(void *ptr);
extern int func_ov002_02208ad8(void *ptr, unsigned char val);
extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern void func_0208e4c0(void *ptr, int val);
extern unsigned char *func_ov002_02208098(void *ptr, unsigned char value);

int func_ov109_0229c6f8(unsigned char *p)
{
    p[0x29d7] = 1;
    p[0x29d8] = func_ov002_022090e4(p + 0x22d8, 1);
    func_ov002_0220a0b4(p + 0x2274, func_ov002_02208ae4(p + 0x22d8), func_ov002_02208ad8(p + 0x22d8, p[0x29d8]));
    func_0208e4c0(p + 0x2274, 8);
    return (int) func_ov002_02208098(p, 0xc);
}
