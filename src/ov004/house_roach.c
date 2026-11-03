/* house_roach: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223d634 @ 0x0223d634, 0x8 bytes, Thumb
 * func_ov004_0223d618 @ 0x0223d618, 0x1c bytes, Thumb
 * func_ov004_0223d610 @ 0x0223d610, 0x8 bytes, Thumb
 * func_ov004_0223d608 @ 0x0223d608, 0x8 bytes, Thumb
 */

extern int func_ov004_0223dd04(char *parameter0);
extern int func_020b67d4(void);
extern int func_ov004_0223e2f0(char *self);
extern int func_ov004_0223de70(void *parameter0);
extern int func_ov004_0223dccc(char *parameter0);

void func_ov004_0223d634(char *arg0)
{
    func_ov004_0223dd04((char *) arg0);
}

int func_ov004_0223d618(char *self)
{
    if (func_020b67d4() != 0) {
        return func_ov004_0223e2f0(self);
    }
    return 1;
}

void func_ov004_0223d610(void *arg0)
{
    func_ov004_0223de70((void *) arg0);
}

void func_ov004_0223d608(char *arg0)
{
    func_ov004_0223dccc((char *) arg0);
}
