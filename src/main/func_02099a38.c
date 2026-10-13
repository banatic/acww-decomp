/* func_02099a38 @ 0x02099a38, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02099ac0(void *);
extern void func_02095238(void *);
extern void func_02098f80(void *);
extern void func_0203cf40(void *);
extern void func_0209adb0(void *);
extern void func_020adf5c(void *);
extern void func_02099e18(void *);
extern void MI_CpuFill8(void *, int, int);

void func_02099a38(void *p)
{
    func_02099ac0(p);
    func_02095238((char *) p + 0x247e);
    func_02098f80((char *) p + 0x11a8);
    func_0203cf40((char *) p + 0x1c18);
    func_0209adb0((char *) p + 0x1e40);
    *(unsigned short *) ((char *) p + 0x2406) = 0xfff1;
    func_020adf5c((char *) p + 0x2404);
    *(unsigned short *) ((char *) p + 0x240e) = 0xfff1;
    *(unsigned char *) ((char *) p + 0x2453) = 0xff;
    MI_CpuFill8((char *) p + 0x2454, 0xff, 8);
    func_02099e18((char *) p + 0x245c);
}
