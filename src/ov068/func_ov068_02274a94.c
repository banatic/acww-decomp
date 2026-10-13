/* func_ov068_02274a94 @ 0x02274a94, 0x28 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec14(void *);
extern void func_ov004_02246988(void);

int func_ov068_02274a94(void *arg)
{
    if (func_0202ec14(arg) == 0) {
        return 0;
    }
    if (*(unsigned int *) ((char *) arg + 0x730) == 7) {
        func_ov004_02246988();
    }
    return 1;
}
