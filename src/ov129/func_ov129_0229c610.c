/* func_ov129_0229c610 @ 0x0229c610, 0x34 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220b9b8(char *dst, char *src, int size, int mode);
extern void func_ov002_02208098(char *self, int num);
extern void func_0208e5c4(char *ptr);

void func_ov129_0229c610(char *self, char value)
{
    char local = value;
    func_ov002_0220b9b8(self + 0xb8, &local, 1, 0);
    func_ov002_02208098(self, 14);
    func_0208e5c4(self + 0x3a0);
}
