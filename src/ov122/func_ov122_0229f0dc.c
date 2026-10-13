/* func_ov122_0229f0dc @ 0x0229f0dc, 0x28 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02209740(char *a, unsigned char b, int c);
extern void func_ov002_02208098(char *a, int b);

void func_ov122_0229f0dc(char *self, int second)
{
    func_ov002_02209740(self + 0x42b0, *(unsigned char *) (self + 0xb7), second);
    func_ov002_02208098(self, 22);
}
