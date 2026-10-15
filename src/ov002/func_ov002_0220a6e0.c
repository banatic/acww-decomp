/* func_ov002_0220a6e0 @ 0x0220a6e0, 0x1e bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a674(char *self, int i);
extern int func_ov002_0220b280(char *p);

int func_ov002_0220a6e0(char *self)
{
    return func_ov002_0220b280(self + 4 + func_ov002_0220a674(self, -1) * 0x7c);
}
