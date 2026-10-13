/* func_0202f874 @ 0x0202f874, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int, int);

int *func_0202f874(int *p, int arg)
{
    *p = FX_MulFunc(*p, arg);
    *(p + 1) = FX_MulFunc(*(p + 1), arg);
    return p;
}
