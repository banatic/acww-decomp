/* func_ov003_02215c44 @ 0x02215c44, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *p);
extern int func_02008258(void *p, int val);
extern void func_0200d4e8(void *p, int a, int b, int c);

void func_ov003_02215c44(unsigned char *self)
{
    if (func_02056f94(self + 0x2d0) == 0) {
        return;
    }
    *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
    func_0200d4e8(self, 3, 1, -1);
}
