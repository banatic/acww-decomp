/* func_02095f28 @ 0x02095f28, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int);
extern int func_0200f05c(int, int);

int func_02095f28(void)
{
    void *ptr = func_02096718(4);
    if (ptr) {
        return func_0200f05c((int) ptr, *(int *) ((char *) ptr + 0x7f0));
    }
    return 0;
}
