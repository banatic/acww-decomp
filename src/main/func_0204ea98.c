/* func_0204ea98 @ 0x0204ea98, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *param1, int param2, int param3, void (*param4)(void));
extern void func_02037d0c(void);
extern void func_0204e6d8(void);

void *func_0204ea98(void *p)
{
    __cxa_vec_cleanup((char *) p + 0x2024, 0x10, 0x20, func_02037d0c);
    __cxa_vec_cleanup((char *) p + 0x24, 0x10, 0x200, func_0204e6d8);
    return p;
}
