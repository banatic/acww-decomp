/* func_ov104_0229cec4 @ 0x0229cec4, 0x50 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov104_0229c354(void *arg0, int arg1);
extern void func_ov002_02208d30(void *arg0, int arg1);
extern void func_ov002_02208d4c(void *arg0, int arg1, int arg2);
extern void func_ov104_0229d010(void *arg0, int arg1);

void func_ov104_0229cec4(unsigned char *self)
{
    func_ov104_0229c354(self, 0x8000);
    func_ov002_02208d30(self + 0x28ec, 4);
    func_ov002_02208d4c(self + 0x28ec, 0x1a, 4);
    func_ov002_02208d4c(self + 0x28ec, 0x15, 2);
    func_ov002_02208d4c(self + 0x28ec, 0x19, 4);
    func_ov104_0229d010(self, 0);
}
