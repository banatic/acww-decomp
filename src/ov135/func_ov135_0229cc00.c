/* func_ov135_0229cc00 @ 0x0229cc00, 0x48 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_02299a60(char *addr);
extern void func_ov002_02208098(char *ptr, int val);
extern void func_ov135_0229c630(char *ptr);
extern int func_ov135_0229c7a8(char *ptr);
extern int func_ov135_0229c754(char *ptr);
extern void func_ov002_0220a0b4(char *ptr, int a, int b);

void func_ov135_0229cc00(char *ptr)
{
    if (func_ov134_02299a60(ptr + 0x2c8) != 0) {
        func_ov002_02208098(ptr, 7);
        func_ov135_0229c630(ptr);
    }
    {
        int val1 = func_ov135_0229c7a8(ptr);
        int val2 = func_ov135_0229c754(ptr);
        func_ov002_0220a0b4(ptr + 0x98, val1, val2);
    }
}
