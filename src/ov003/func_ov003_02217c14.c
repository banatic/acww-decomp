/* func_ov003_02217c14 @ 0x02217c14, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020779b8(char *ptr, int a, int b);
extern void func_02077910(char *ptr, short val);

void func_ov003_02217c14(char *ptr, char byte, int a, int b, short c)
{
    ptr[7] = byte;
    func_020779b8(ptr, a, b);
    func_02077910(ptr + 5, c);
}
