/* func_0204bff4 @ 0x0204bff4, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204be38(void *);
extern unsigned int func_0206213c(void);
extern void func_0204bf38(int *, unsigned int);
extern int func_0204b42c(void *);
extern void func_020051b0(void *);

int func_0204bff4(void *arg0)
{
    unsigned int i;
    int local;
    if (func_0204be38(arg0) != 0) {
        for (i = 0; i < func_0206213c(); i++) {
            func_0204bf38(&local, i);
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
