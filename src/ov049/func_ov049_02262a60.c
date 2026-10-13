/* func_ov049_02262a60 @ 0x02262a60, 0x34 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ea80(int, int);
extern void func_ov049_0226208c(void *, int);

int func_ov049_02262a60(void *arg)
{
    int result;
    void *ptr;

    result = func_0202ea80(0xf, 1);
    if (result != 0) {
        ptr = (char *) arg + 0x658;
        func_ov049_0226208c(ptr, 1);
    } else {
        ptr = (char *) arg + 0x658;
        func_ov049_0226208c(ptr, 0);
    }
    return 1;
}
