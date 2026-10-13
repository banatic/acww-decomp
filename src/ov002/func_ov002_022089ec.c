/* func_ov002_022089ec @ 0x022089ec, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b4980(const char *s, char *dst, int mode);

void func_ov002_022089ec(int unused, const char *src, char c)
{
    char temp = c;
    func_020b4980(src, &temp, 0);
}
