/* func_ov002_0220a620 @ 0x0220a620, 0x1a bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a674(char *self, int i);
extern void func_ov002_0220b12c(char *p);

void func_ov002_0220a620(char *self, int i)
{
    func_ov002_0220b12c(self + 4 + func_ov002_0220a674(self, i) * 0x7c);
}
