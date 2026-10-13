/* func_02095d84 @ 0x02095d84, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern void *func_02096718(int);
extern int func_0200f290(void *, int);
extern int func_0200e828(void *);

int func_02095d84(void)
{
    void *p;
    p = func_02096718(4);
    if (p == 0) {
        goto ret0_late;
    }
    if (func_0200f290(p, 0xb) != 0) {
        if (*(int *) ((char *) p + 0x7f0) == 0x28 || *(int *) ((char *) p + 0x7f0) == 0x7c) {
            return 1;
        }
    }
    if (func_0200f290(p, 0x13) != 0) {
        return 0;
    }
    {
        int lim = 5;
        if (lim <= func_0200e828(p)) {
            return 0;
        }
        return 1;
    }
ret0_late:
    return 0;
}
