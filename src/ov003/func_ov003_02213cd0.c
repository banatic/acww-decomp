/* func_ov003_02213cd0 @ 0x02213cd0, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_020113a4(int a, int b, int c);
extern void func_0201107c(void *a, int *b);
extern int func_020912d4(int a, void *b, void *c, int d);

void func_ov003_02213cd0(void *ptr)
{
    int local;
    if (*(int *) ((char *) ptr + 0x98) == 0) {
        return;
    }
    local = func_020113a4(*(int *) ((char *) ptr + 0x98), 0, 0x171);
    func_0201107c(ptr, &local);
    if (*(int *) ((char *) ptr + 0x98) != 0) {
        return;
    }
    func_020912d4(0x2b, (char *) ptr + 0x5c, (char *) ptr + 0x8e, 0);
}
