/* func_ov048_02263174 @ 0x02263174, 0x58 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8840(void *);
extern void *func_0200338c(int, int);
extern void func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern unsigned short data_020c80f8;

int func_ov048_02263174(void *arg)
{
    void *p;

    if (func_020e8840((char *) arg + 0xe6e) == 0) {
        p = func_0200338c(0x73, 0);
        func_02019d0c((char *) p + 0x564, 3, 1, 0, 0, 0, 0x4000, 0, 0, data_020c80f8, 0);
        return 1;
    }
    return 0;
}
