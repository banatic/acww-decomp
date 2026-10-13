/* func_ov132_0229ae18 @ 0x0229ae18, 0x34 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a05c(void *a, int b, int c, int d, int e);
extern void func_ov002_02208098(void *a, int b);

void func_ov132_0229ae18(void *self, int p1, int p2)
{
    func_ov002_0220a05c((char *) self + 0x94, p1, p2, 3, 1);
    *((unsigned char *) ((char *) self + 0x1503)) = *((unsigned char *) ((char *) self + 0x8d));
    func_ov002_02208098(self, 2);
}
