/* func_02081710 @ 0x02081710, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020642f8(void *);
extern void func_02081f9c(void *);
extern int func_02003750(void *);
extern void *func_0209b61c(void *);
extern void func_02066688(void *);
extern void *func_02072da4(void *);
extern void func_020051b0(void *);
extern void *func_02081f18(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

void *func_02081710(void *obj)
{
    func_020642f8((char *) obj + 0x7dc);
    func_02081f9c((char *) obj + 0x7ce);
    func_020642f8((char *) obj + 0x7b8);
    __cxa_vec_cleanup((void *) ((char *) obj + 0x7b0), 4, 2, (void (*)(void *)) func_020051b0);
    func_02003750((char *) obj + 0x7a0);
    __cxa_vec_cleanup((void *) ((char *) obj + 0x78c), 0xa, 2, (void (*)(void *)) func_020051b0);
    func_0209b61c((char *) obj + 0x734);
    func_02066688((char *) obj + 0x634);
    func_02072da4((char *) obj + 0x400);
    __cxa_vec_cleanup((void *) (obj), 8, 0x80, (((void (*)(void *)) func_02081f18)));
    return obj;
}
