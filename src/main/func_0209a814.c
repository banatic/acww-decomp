/* func_0209a814 @ 0x0209a814, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209bd80(void *);
extern void func_02003780(void *);
extern void func_0209526c(void);
extern void func_0209529c(void);
#pragma arm
extern void func_02138d6c(void *, int, int, void (*)(void), void (*)(void));
#pragma thumb
extern void func_0209a77c(void *);

void *func_0209a814(void *p)
{
    func_0209bd80(p);
    func_02003780((char *) p + 0xc);
    func_02138d6c((char *) p + 0x1c, 5, 0x1e, func_0209529c, func_0209526c);
    func_0209a77c(p);
    return p;
}
