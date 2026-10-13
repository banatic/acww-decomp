/* func_ov002_0220a374 @ 0x0220a374, 0x28 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e4bc(void *self);
extern void func_0208e508(void *self, int v);

void func_ov002_0220a374(void *self, int v)
{
    if (v != func_0208e4bc(self) || v == 6 || v == 0xc) {
        func_0208e508(self, v);
    }
}
