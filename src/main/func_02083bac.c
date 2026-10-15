/* func_02083bac @ 0x02083bac, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_02083cb4(void);
extern void func_0205cce4(void *);

int func_02083bac(int param)
{
    __cxa_vec_cleanup((void *) (param + 1), 3, 1, (void (*)(void *)) func_0205cce4);
    asm { add r0, param, #0 }
    func_02083cb4();
    return param;
}
