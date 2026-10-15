/* func_0200c158 @ 0x0200c158, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(char *p);
extern int func_02008258(char *p, int val);
extern int func_0200c9a8(char *p, int a, int b, int c);

void func_0200c158(char *p)
{
    if (func_02056f94(p + 0x2D0) != 0) {
        *(int *) (p + 0x7FC) = func_02008258(p, *(int *) (p + 0x7F0));
        func_0200c9a8(p, 7, 5, -1);
    }
}
