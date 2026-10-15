/* func_02035344 @ 0x02035344, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035a60(void *);
extern void func_02035db8(void *);
extern void func_02037430(void *);
extern void func_02036940(void *);
extern void func_0203680c(void *);
extern void func_02035104(void *);
extern void func_02034dcc(void *);
extern void func_02034dc8(void);

void func_02035344(void *p)
{
    func_02035a60((char *) p + 0x2e4);
    func_02035db8((char *) p + 0x2d0);
    func_02037430((char *) p + 0x24c);
    func_02036940((char *) p + 0x264);
    func_0203680c((char *) p + 0x2a0);
    func_02035104(p);
    func_02034dcc(p);
    asm { add r0, p, #0 }
    func_02034dc8();
}
