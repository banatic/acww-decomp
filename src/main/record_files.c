/* record_files: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206e73c @ 0x0206e73c, 0x3a bytes, Thumb
 * func_0206e71c @ 0x0206e71c, 0x1e bytes, Thumb
 * func_0206e704 @ 0x0206e704, 0x16 bytes, Thumb
 * func_0206e6f0 @ 0x0206e6f0, 0x12 bytes, Thumb
 * func_0206e6ec @ 0x0206e6ec, 0x2 bytes, Thumb
 * func_0206e6e8 @ 0x0206e6e8, 0x4 bytes, Thumb
 * func_0206e6e4 @ 0x0206e6e4, 0x4 bytes, Thumb
 */

extern int func_0206e890(char *dst, int a, int b, int c);
extern void func_0206e854(char *dst);
extern void func_0206e808(void *ptr);
extern void func_0206e83c(void *);

int func_0206e73c(char *p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7)
{
    func_0206e890(p0, p1, p2, p7);
    func_0206e890(p0 + 0x1c, p3, p4, p7);
    func_0206e890(p0 + 0x38, p5, p6, p7);
    func_0206e854(p0);
    return 1;
}

void func_0206e71c(void *ptr)
{
    func_0206e808(ptr);
    func_0206e808((char *) ptr + 0x1c);
    func_0206e808((char *) ptr + 0x38);
}

int func_0206e704(void *ptr, int flag)
{
    if (flag == 0) {
        func_0206e854((char *) ((char *) ptr + 0x1c));
    }
    return 1;
}

int func_0206e6f0(void *arg)
{
    func_0206e83c((char *) arg + 0x1c);
    return 1;
}

void *func_0206e6ec(void *object)
{
    return object;
}

int func_0206e6e8(int p0)
{
    return ((int) (p0) + (28));
}

int func_0206e6e4(int p0)
{
    return ((int) (p0) + (56));
}
