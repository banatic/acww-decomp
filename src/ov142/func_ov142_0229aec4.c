/* func_ov142_0229aec4 @ 0x0229aec4, 0x24 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a164(void *p);
extern void func_ov002_02208098(void *p, int n);

void func_ov142_0229aec4(unsigned char *self)
{
    func_ov002_0220a164(self + 0xe8);
    self[0xba] = self[0x8d];
    func_ov002_02208098(self, 0xa);
}
