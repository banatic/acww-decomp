/* func_02021d78 @ 0x02021d78, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02021dcc(int unused, const void *arg);

extern int func_02021ea8(void *self, int *arr, int count, void *predicate);
extern int func_02081d64(int);
extern void *func_02015e70(int, int, int);
extern int func_02021e68(int);
extern void func_02015fb0(int, int, int, int, int, int);

int func_02021d78(int a, int b, int c)
{
    int r5;
    r5 = func_02021ea8((void *) (*(int *) ((char *) *(int **) ((char *) a + 0x100) + 0x830)), (int *) (b), (int) (c),
                       (((void *) func_02021dcc)));
    if (r5 != 0) {
        int t1;
        int t2;
        t1 = func_02081d64(r5);
        func_02015e70(a, t1, 9);
        t2 = func_02021e68(r5);
        func_02015fb0(a, t2, 0, 10, 0, 0);
    }
    return r5;
}
