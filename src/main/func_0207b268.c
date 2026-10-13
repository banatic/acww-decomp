/* func_0207b268 @ 0x0207b268, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209a67c(void *sub);
extern void *func_0209a6fc(void *sub, unsigned char level);
extern void func_02095238(void *p);

void func_0207b268(unsigned char *arg)
{
    int level;
    void *res;

    level = arg[0x404a];
    res = 0;

    if (func_0209a67c(arg + 0x3f90) != 0 || arg[0x4045] != 0) {
        if (level == 0) {
            level = 5;
        } else if ((unsigned char) level < 5) {
            level--;
        }
        arg[0x404a] = level;
        res = func_0209a6fc(arg + 0x3f90, arg[0x404a]);
    } else {
        if ((unsigned char) (level + 1) < 5) {
            arg[0x404a] = (unsigned char) (level + 1);
            res = func_0209a6fc(arg + 0x3f90, arg[0x404a]);
        } else if ((unsigned char) level < 5) {
            res = func_0209a6fc(arg + 0x3f90, (unsigned char) level);
        }
    }

    if (res != 0) {
        func_02095238(res);
    }
}
