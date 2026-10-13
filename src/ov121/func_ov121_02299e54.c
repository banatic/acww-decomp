/* func_ov121_02299e54 @ 0x02299e54, 0x2c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f00(void *ptr);
extern int func_ov090_02298f84(int val);
extern void func_ov002_0220a254(void *ptr);

void func_ov121_02299e54(char *self)
{
    self[0xb1] = (char) (func_ov090_02298f84(func_ov002_02209f00(self + 0x3a8)) + 0x10);
    func_ov002_0220a254(self + 0x3a8);
}
