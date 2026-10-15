/* func_ov096_0229dd44 @ 0x0229dd44, 0x50 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208ae4(unsigned char *ptr);
extern int func_ov002_02208ad8(unsigned char *ptr, unsigned char c);
extern int func_ov002_0220a08c(unsigned char *ptr, int a, int b, int c);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov096_0229dd44(unsigned char *self)
{
    int res1;
    int res2;

    res1 = func_ov002_02208ae4(self + 0x2564);
    res2 = func_ov002_02208ad8(self + 0x2564, self[0xbc]);
    func_ov002_0220a08c(self + 0x2500, res1, res2, 2);
    self[0xba] = self[0x8d];
    func_ov002_02208098((void *) (self), 0xf);
}
