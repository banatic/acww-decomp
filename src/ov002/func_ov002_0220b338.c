/* func_ov002_0220b338 @ 0x0220b338, 0x1e bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220b29c(char *self, int a1);
extern void func_ov002_0220b358(void *self, int v);

void func_ov002_0220b338(char *self, int value)
{
    func_ov002_0220b358(self, value);
    self[0x75] = 0;
    func_ov002_0220b29c(self, 1);
}
