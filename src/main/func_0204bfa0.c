/* func_0204bfa0 @ 0x0204bfa0, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bd84(void *);
extern unsigned int func_02062130(void);
extern void func_0204beb0(void *, unsigned int);
extern int func_0204b42c(void *);
extern void func_020051b0(void *);

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
