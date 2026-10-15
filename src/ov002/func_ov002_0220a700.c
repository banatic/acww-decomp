/* func_ov002_0220a700 @ 0x0220a700, 0x1e bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a674(char *self, int i);
extern int func_ov002_0220b168(char *p);

int func_ov002_0220a700(char *self)
{
    return func_ov002_0220b168(self + 4 + func_ov002_0220a674(self, -1) * 0x7c);
}
