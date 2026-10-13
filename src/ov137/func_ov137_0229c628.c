/* func_ov137_0229c628 @ 0x0229c628, 0x28 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a164(void *p);
extern void func_ov002_02208098(void *p, int n);

void func_ov137_0229c628(void *self)
{
    func_ov002_0220a164((unsigned char *) self + 0x94);
    *((unsigned char *) self + 0x2b76) = *((unsigned char *) self + 0x8d);
    func_ov002_02208098(self, 10);
}
