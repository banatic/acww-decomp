/* func_0209cfe0 @ 0x0209cfe0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138d6c(void *ptr, int a, int b, void (*c)(void), void (*d)(void));
extern void func_0206e8c4(void *ptr);
extern void func_0209d038(void);
extern void func_0209d03c(void);

void *func_0209cfe0(void *ptr)
{
    func_02138d6c(ptr, 0x24, 8, func_0209d03c, func_0209d038);
    func_0206e8c4((char *) ptr + 0x120);
    return ptr;
}
