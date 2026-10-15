/* func_0209a814 @ 0x0209a814, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209bd80(void *);
extern int func_02003780(void *);
extern int func_0209526c(void *);
extern void *func_0209529c(void *);
#pragma arm
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
#pragma thumb
extern void func_0209a77c(void *);

void *func_0209a814(void *p)
{
    func_0209bd80(p);
    func_02003780((char *) p + 0xc);
    __cxa_vec_ctor((void *) ((char *) p + 0x1c), 5, 0x1e, (((void (*)(void *)) func_0209529c)),
                   (((void (*)(void *)) func_0209526c)));
    func_0209a77c(p);
    return p;
}
