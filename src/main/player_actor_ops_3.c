/* player_actor_ops_3: 3 functions, module main
 * mwccarm 1.2/base -O1,s
 * func_02095e08 @ 0x02095e08, 0x7c bytes, Thumb
 * func_02095de0 @ 0x02095de0, 0x26 bytes, Thumb
 * func_02095d84 @ 0x02095d84, 0x5c bytes, Thumb
 */

extern void *func_02096718(int);
extern int func_0200f290(void *, int);
extern int func_0203e31c(void);
extern int func_0200e828(void *);

int func_02095e08(void)
{
    void *p;
    p = func_02096718(4);
    if (p == 0) {
        goto ret0_late;
    }
    if (func_0200f290(p, 0xb) != 0) {
        return 0;
    }
    if (func_0203e31c() != 0 || func_0200f290(p, 0x13) != 0) {
        return 0;
    }
    if (*(int *) ((char *) p + 0x7f0) == 0x3d || func_0200f290(p, 7) != 0 || func_0200f290(p, 8) != 0) {
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

int func_02095de0(void)
{
    void *res = func_02096718(4);
    int lim;
    if (res != 0) {
        lim = 6;
        if (lim <= func_0200e828(res)) {
            return 0;
        }
        return 1;
    }
    return 0;
}

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
