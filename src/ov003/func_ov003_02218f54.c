/* func_ov003_02218f54 @ 0x02218f54, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(int argument0);
extern int func_02056f94(void *);
extern void func_020109fc(void *, int, int, int);

void func_ov003_02218f54(void *arg)
{
    void *p = arg;
    func_02010f5c((int) arg);
    if (func_02056f94((char *) p + 0x2d0) != 0) {
        func_020109fc(p, 0, 3, 0);
    }
}
