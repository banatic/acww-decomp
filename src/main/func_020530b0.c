/* func_020530b0 @ 0x020530b0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02053300(void *p);
extern void __cxa_vec_cleanup(void *p, int a, int b, void (*cb)(void));
extern void func_0205336c(void);

void *func_020530b0(void *param)
{
    func_02053300((char *) param + 0x40);
    __cxa_vec_cleanup(param, 2, 0x20, func_0205336c);
    return param;
}
