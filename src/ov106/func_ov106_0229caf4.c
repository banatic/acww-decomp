/* func_ov106_0229caf4 @ 0x0229caf4, 0x64 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022090e4(void *ptr, int val);
extern int func_ov002_02208ae4(void *ptr);
extern int func_ov002_02208ad8(void *ptr, unsigned char val);
extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern void func_0208e4c0(void *ptr, int val);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

int func_ov106_0229caf4(char *self)
{
    int a, b;
    self[0xBC] = 4;
    self[0xBD] = func_ov002_022090e4(self + 0x2304, 1);
    a = func_ov002_02208ae4(self + 0x2304);
    b = func_ov002_02208ad8(self + 0x2304, self[0xBD]);
    func_ov002_0220a0b4(self + 0x22A0, a, b);
    func_0208e4c0(self + 0x22A0, 8);
    return (int) func_ov002_02208098((void *) (self), 0x17);
}
