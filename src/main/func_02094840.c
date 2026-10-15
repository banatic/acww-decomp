/* func_02094840 @ 0x02094840, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021d5658;
extern void func_02091494(char *p, int a, int b, int c, int d, int e, int f);
extern void func_02090aa4(int x, void (*cb)(void *));
extern void func_02094884(void *);

int func_02094840(int a0, int a1, int a2, int a3, int a4, void (*a5)(void *))
{
    void (*cb)(void *) = a5;
    if (cb == 0) {
        cb = &func_02094884;
    }
    func_02091494(&data_021d5658, -1, a1, a2, a3, a4, -1);
    func_02090aa4(a0, cb);
    return 1;
}
