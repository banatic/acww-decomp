/* func_ov110_0229db18 @ 0x0229db18, 0x30 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f9c(void *ptr);
extern void func_ov110_0229d728(void *ptr, unsigned char byte);
extern void func_ov002_02208098(void *ptr, int value);

void func_ov110_0229db18(char *s)
{
    if (func_ov002_02209f9c(s + 0x22e0) == 0) {
        return;
    }
    func_ov110_0229d728(s, *(unsigned char *) (s + 0xf5));
    func_ov002_02208098(s, 0xc);
}
