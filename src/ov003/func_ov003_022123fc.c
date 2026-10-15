/* func_ov003_022123fc @ 0x022123fc, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *p);
extern int func_02008258(void *p, int value);
extern int func_0200d4e8(void *p, int a, int b, int c);

void func_ov003_022123fc(char *p)
{
    if (func_02056f94(p + 0x2d0)) {
        *(int *) (p + 0x7fc) = func_02008258(p, *(int *) (p + 0x7f0));
        func_0200d4e8(p, 3, 1, -1);
    }
}
