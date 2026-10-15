/* func_020959ac @ 0x020959ac, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern int func_0203e21c(void);
extern void *func_02096718(int);
extern int func_0200f290(void *, int);
extern int func_0200e7f8(void *);
extern void *func_ov003_02215624(void *, int, int, int);
extern int func_02008c40(void *, int, int);

int func_020959ac(void)
{
    void *ptr;
    int lim;

    if (func_0203e21c() != 0) {
        return 0;
    }

    ptr = func_02096718(4);
    if (ptr == 0) {
        goto l_fail2;
    }

    if (func_0200f290(ptr, 11) != 0) {
        return 0;
    }

    lim = 5;
    if (lim > func_0200e7f8(ptr)) {
        goto l_call;
    }

    if (*(int *) ((char *) ptr + 0x7f0) != 0x4f) {
        goto l_fail1;
    }
    if (*(int *) ((char *) ptr + 0x5cc) == 5) {
        goto l_fail1;
    }

    func_ov003_02215624(ptr, 1, 6, -1);
    return 1;

l_fail1:
    return 0;
l_call:
    return func_02008c40(ptr, 5, -1);
l_fail2:
    return 0;
}
