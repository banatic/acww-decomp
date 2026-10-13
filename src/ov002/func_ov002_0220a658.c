/* func_ov002_0220a658 @ 0x0220a658, 0x1a bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a674(char *self, int i);
extern void func_ov002_0220b144(char *p);

void func_ov002_0220a658(char *self, int i)
{
    func_ov002_0220b144(self + 4 + func_ov002_0220a674(self, i) * 0x7c);
}
