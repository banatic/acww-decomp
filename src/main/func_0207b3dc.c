/* func_0207b3dc @ 0x0207b3dc, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0207b410(void *);
extern void *func_0209a778(void *);
extern int func_0209bd44(void *);
extern void *func_0209a774(void *);
extern int func_0207cf14(void *, void *);

int func_0207b3dc(void *a)
{
    if (func_0209bd44(func_0209a778(func_0207b410(a))) != 0) {
        return func_0207cf14(a, func_0209a774(func_0207b410(a)));
    } else {
        return -1;
    }
}
