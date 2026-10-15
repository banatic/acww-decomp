/* func_020b1d2c @ 0x020b1d2c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02034270(void *p, unsigned int a, int b, int c);
extern int func_020b1d54(int x);
extern void func_0203423c(void *p);

int func_020b1d2c(unsigned int arg)
{
    char buffer[0x40];
    int result;
    func_02034270(buffer, arg, 0, 0);
    result = func_020b1d54(*(int *) (buffer + 0x34));
    func_0203423c(buffer);
    return result;
}
