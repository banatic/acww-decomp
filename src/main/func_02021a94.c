/* func_02021a94 @ 0x02021a94, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02021ae4(int a, int b);

extern int func_02021ea8(void *self, int *arr, int count, void *predicate);
extern unsigned int func_02081d64(unsigned int);
extern void *func_02015e70(unsigned int, unsigned int, unsigned int);
extern unsigned int func_02081abc(unsigned int);
extern void func_02015de4(unsigned int, unsigned int, unsigned int, unsigned int);

unsigned int func_02021a94(unsigned int a, unsigned int arg1, unsigned int arg2)
{
    unsigned int val;
    unsigned int ret;
    unsigned int tmp;
    unsigned int tmp2;

    val = *(unsigned int *) ((char *) *(unsigned int *) ((char *) a + 0x100) + 0x830);
    ret = func_02021ea8((void *) (val), (int *) (arg1), (int) (arg2), (((void *) func_02021ae4)));
    if (ret) {
        tmp = func_02081d64(ret);
        func_02015e70(a, tmp, 9);
        tmp2 = func_02081abc(ret);
        func_02015de4(a, tmp2, 1, 7);
    }
    return ret;
}
