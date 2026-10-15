/* func_02017674 @ 0x02017674, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057d34(void *);
extern void func_02016764(int, int, int, int, int, int, int, int);
extern unsigned short data_020c80f8;

void func_02017674(void *arg0, void *arg1)
{
    if (func_02057d34(arg1) != 0) {
        return;
    } else {
        func_02016764((int) arg1 + 0x334, (int) arg1, 0, data_020c80f8, 0, 0x1000, 0, 0);
        ((char *) arg0)[0x98] = 2;
    }
}
