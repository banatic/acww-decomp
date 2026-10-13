/* func_ov002_0220af74 @ 0x0220af74, 0x1e bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220b290(void *p);

void func_ov002_0220af74(void *self)
{
    int i;
    char *base;
    for (i = 0, base = (char *) self + 4; i < 2; i++) {
        func_ov002_0220b290(base + i * 0x7c);
    }
}
