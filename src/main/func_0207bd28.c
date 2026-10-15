/* func_0207bd28 @ 0x0207bd28, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02081f9c(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

extern unsigned char data_021d13a8[];

void func_0207bd28(void)
{
    __cxa_vec_cleanup((void *) ((void *) data_021d13a8), 0x1e, 2, (void (*)(void *)) func_02081f9c);
}
