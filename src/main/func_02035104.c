/* func_02035104 @ 0x02035104, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020350a4(void *);
extern void func_02035040(void *);
extern void func_02034fec(void *);
extern void func_020364c0(void *);
extern void func_02035f6c(void *);
extern void func_02035800(void *);
extern void func_02034fac(void *);

void func_02035104(void *p)
{
    func_020350a4(p);
    func_02035040(p);
    func_02034fec(p);
    func_020364c0((char *) p + 0x1c4);
    func_02035f6c((char *) p + 0x2b4);
    func_02035800((char *) p + 0x2f0);
    func_02034fac(p);
}
