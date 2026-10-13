/* func_ov003_0220f4f0 @ 0x0220f4f0, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02077928(int a, char *b, char *c, char *d, char *e);

int func_ov003_0220f4f0(int a, char *b)
{
    char buf[8];
    return func_02077928(a, b, b + 4, b + 8, buf);
}
