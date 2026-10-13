/* func_0208012c @ 0x0208012c, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020807a8(unsigned a, unsigned c);
extern int func_020951bc(unsigned c);
extern int func_02081b54(void *r);
extern void func_02081b24(void *r, unsigned b);

int func_0208012c(unsigned a, unsigned b, unsigned c)
{
    void *r;
    int flag;
    r = func_020807a8(a, c);
    flag = 0;
    if (r != 0 && func_020951bc(c) != 0 && func_02081b54(r) != 0) {
        func_02081b24(r, b);
        flag = 1;
    }
    return flag;
}
