/* func_0207b3dc @ 0x0207b3dc, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0207b410(unsigned int address);
extern void *func_0209a778(void *record);
extern int func_0209bd44(void *);
extern int func_0209a774(int address);
extern int func_0207cf14(void *, void *);

int func_0207b3dc(void *base)
{
    if (func_0209bd44(func_0209a778((void *) func_0207b410((unsigned int) base))) != 0) {
        return func_0207cf14(base, (void *) func_0209a774((int) func_0207b410((unsigned int) base)));
    }
    return -1;
}
