/* func_ov003_0220f128 @ 0x0220f128, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void);
extern int func_020912d4(int, void *, int, int);
extern int func_02091278(int, void *, int, int);

void func_ov003_0220f128(char *s)
{
    int *pid;
    func_02010f5c();
    pid = (int *) (s + 0x7d4);
    if (*pid == -1) {
        *pid = func_020912d4(0x34, s + 0x6e0, 0, 0);
    } else {
        func_02091278(*pid, s + 0x6e0, 0, 0);
    }
}
