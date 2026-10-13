/* func_ov103_0229d0b8 @ 0x0229d0b8, 0x20 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208e18(char *ptr);
extern void func_ov103_0229c588(char *ptr);

void func_ov103_0229d0b8(char *ptr)
{
    if (func_ov002_02208e18(ptr + 0x22d8) != 0) {
        func_ov103_0229c588(ptr);
    }
}
