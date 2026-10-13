/* func_0206e73c @ 0x0206e73c, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206e890(char *dst, int a, int b, int c);
extern void func_0206e854(char *dst);

int func_0206e73c(char *p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7)
{
    func_0206e890(p0, p1, p2, p7);
    func_0206e890(p0 + 0x1c, p3, p4, p7);
    func_0206e890(p0 + 0x38, p5, p6, p7);
    func_0206e854(p0);
    return 1;
}
