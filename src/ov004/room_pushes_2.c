/* room_pushes_2: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223c964 @ 0x0223c964, 0x10 bytes, Thumb
 * func_ov004_0223c954 @ 0x0223c954, 0x10 bytes, Thumb
 */

#define g_x0 (*(int *) 0x00004000)

extern int func_ov004_0223c9b4(int, int);
extern int func_ov004_0223c994(int, int);

int func_ov004_0223c964(int p0)
{
    return func_ov004_0223c9b4(p0, (int) &g_x0);
}

void func_ov004_0223c954(int p0)
{
    func_ov004_0223c994(p0, (int) &g_x0);
}
