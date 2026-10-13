/* func_02095d2c @ 0x02095d2c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int);
extern int func_0203e31c(int);
extern int func_0200f290(void *, int);

int func_02095d2c(void)
{
    void *p;
    int v;

    p = func_02096718(4);
    if (p == 0) {
        goto ret0_late;
    }
    v = *(int *) ((char *) p + 0x7f0);
    if (func_0203e31c(0x7f0) != 0 || func_0200f290(p, 0x13) != 0) {
        return 0;
    }
    if (func_0200f290(p, 0xb) == 0) {
        goto ret0_late;
    }
    if (v == 0x28 || v == 2 || v == 8) {
        return 1;
    }
ret0_late:
    return 0;
}
