/* func_020530d4 @ 0x020530d4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void (*)(void), void (*)(void));
extern void func_02053304(void *);
extern void func_02053088(void *);
extern void func_02053370(void);
extern void func_0205336c(void);

char *func_020530d4(char *arg)
{
    __cxa_vec_ctor(arg, 2, 32, func_02053370, func_0205336c);
    func_02053304(arg + 0x40);
    func_02053088(arg);
    return arg;
}
