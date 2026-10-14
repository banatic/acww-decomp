/* func_0209b594 @ 0x0209b594, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209bd7c(void *ptr);
extern void __cxa_vec_cleanup(void *ptr, int a, int b, void (*cb)(void));
extern void func_02003750(void);

unsigned char *func_0209b594(unsigned char *ptr)
{
    __cxa_vec_cleanup(ptr + 12, 2, 16, func_02003750);
    func_0209bd7c(ptr);
    return ptr;
}
