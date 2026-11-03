/* item_traits: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204bff4 @ 0x0204bff4, 0x54 bytes, Thumb
 * func_0204bfa0 @ 0x0204bfa0, 0x54 bytes, Thumb
 * func_0204bf38 @ 0x0204bf38, 0x68 bytes, Thumb
 */

extern int func_0204be38(void *);
extern unsigned int func_0206213c(void);
extern int func_0204b42c(void *);
extern void func_020051b0(void *);
extern int func_0204bd84(void *);
extern unsigned int func_02062130(void);
extern void func_0204beb0(void *, unsigned int);
extern void *func_0204bdd0(int i);
extern void func_0204b3cc(void *dest, void *src);
extern void func_0204bf18(void *obj, void *p);

void func_0204bf38(void *obj, unsigned int idx);

int func_0204bff4(void *arg0)
{
    unsigned int i;
    int local;
    if (func_0204be38(arg0) != 0) {
        for (i = 0; i < func_0206213c(); i++) {
            func_0204bf38((void *) (&local), i);
            if (func_0204b42c(arg0) == func_0204b42c(&local)) {
                func_020051b0(&local);
                return i;
            } else {
                func_020051b0(&local);
            }
        }
    }
    return -1;
}

int func_0204bfa0(void *arg0)
{
    int local;
    unsigned int i;
    if (func_0204bd84(arg0) == 0) {
        goto fail;
    }
    for (i = 0; i < func_02062130(); i++) {
        func_0204beb0(&local, i);
        if (func_0204b42c(arg0) == func_0204b42c(&local)) {
            func_020051b0(&local);
            return i;
        }
        func_020051b0(&local);
    }
fail:
    return -1;
}

void func_0204bf38(void *obj, unsigned int idx)
{
    unsigned int i, count;
    unsigned int tmp;

    if (idx >= func_0206213c()) {
        idx = 0;
    }
    count = 0;
    i = count;
    while (i < 33) {
        func_0204b3cc(&tmp, func_0204bdd0(i));
        if (func_0204be38(&tmp) != 0) {
            if (idx == count) {
                func_0204bf18(obj, &tmp);
                func_020051b0(&tmp);
                return;
            } else {
                count++;
            }
        }
        func_020051b0(&tmp);
        i++;
    }
    func_0204b3cc(obj, func_0204bdd0(0));
}
