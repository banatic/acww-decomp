/* func_ov004_0223f9c8 @ 0x0223f9c8, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d180(void *object, unsigned int count, int a, int b, int c, int (*allocate)(int, int),
                         void (*cleanup)(void), void *context);
extern void func_ov004_0223ef1c(void *);
extern void func_0205c978(void);
extern int func_0205c994(int size, int heapword);

int func_ov004_0223f9c8(char *self)
{
    func_0209d180(self + 0x180, 0x20, 0x400, 0x40, 0x9c4, func_0205c994, func_0205c978, 0);
    func_ov004_0223ef1c(self);
    return 0x1;
}
