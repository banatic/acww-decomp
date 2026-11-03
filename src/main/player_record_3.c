/* player_record_3: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02099bc8 @ 0x02099bc8, 0x140 bytes, Thumb
 * func_02099ad0 @ 0x02099ad0, 0xf8 bytes, Thumb
 * func_02099ac0 @ 0x02099ac0, 0x10 bytes, Thumb
 * func_02099a38 @ 0x02099a38, 0x88 bytes, Thumb
 * func_02099a28 @ 0x02099a28, 0x10 bytes, Thumb
 */

extern void *func_02072d14(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void func_02066688(void *);
extern void func_02066694(void *);
extern void func_020051b0(void *);
extern void func_02034ce0(void *);
extern void func_0203cfa4(void *);
extern void func_0203d38c(void *);
extern void *func_02097e28(void *);
extern void *func_0209ae20(void *);
extern void *func_02077c20(void *);
extern void *func_02077d40(void *);
extern void func_02098400(void *);
extern void func_0208880c(void *);
extern int func_020adf74(void *);
extern void func_02088c10(void *);
extern void func_02088764(void *);
extern int func_02088460(void *);
extern void func_02097dd0(void *);
extern void *func_02099e58(void *);
extern void *func_0209529c(void *);
extern int func_0209526c(unsigned char *);
extern void *func_02099e40(unsigned char *);
extern void func_02097dcc(unsigned char *);
extern void *func_02088450(unsigned char *);
extern void func_02088760(unsigned char *);
extern void func_02088c0c(unsigned char *);
extern unsigned int func_020adf64(unsigned char *);
extern void func_02088808(unsigned char *);
extern void func_020983fc(unsigned char *);
extern int func_02077d24(unsigned char *);
extern void *func_02077c0c(unsigned char *);
extern void *func_0209ade4(unsigned char *);
extern int func_02097e18(unsigned char *);
extern void func_0203d388(unsigned char *);
extern void func_0203cfa0(unsigned char *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void *func_02072ce8(unsigned char *);
extern void MI_CpuFill8(void *dest, int value, unsigned int size);
extern void func_02095238(void *);
extern void func_02098f80(void *);
extern void func_0203cf40(void *);
extern void func_0209adb0(void *);
extern void func_020adf5c(void *);
extern void func_02099e18(void *);
extern int func_020951bc(unsigned int);

void *func_02099bc8(void *p)
{
    void *sub;
    unsigned short val;

    func_02072d14(p);
    sub = (char *) p + 0x11a8;
    __cxa_vec_ctor((void *) (sub), 0xa, 0x100, (void (*)(void *)) func_02066694, (void (*)(void *)) func_02066688);
    __cxa_vec_ctor((void *) ((char *) sub + 0xa4a), 0xf, 2, (void (*)(void *)) func_02034ce0,
                   (void (*)(void *)) func_020051b0);
    func_0203cfa4((char *) p + 0x1c18);
    func_0203d38c((char *) p + 0x1d3b);
    func_02097e28((char *) p + 0x1d3c);
    func_0209ae20((char *) p + 0x1e40);
    func_02077c20((char *) p + 0x1f0c);
    func_02077d40((char *) p + 0x1f5c);
    func_02098400((char *) p + 0x23e0);
    func_0208880c((char *) p + 0x23ec);
    func_020adf74((char *) p + 0x2404);
    val = 0xfff1;
    *((unsigned short *) ((char *) p + 0x2406)) = val;
    *((unsigned short *) ((char *) p + 0x2408)) = val;
    *((unsigned short *) ((char *) p + 0x240a)) = val;
    *((unsigned short *) ((char *) p + 0x240c)) = val;
    *((unsigned short *) ((char *) p + 0x240e)) = val;
    *((unsigned short *) ((char *) p + 0x2410)) = val;
    func_02088c10((char *) p + 0x2416);
    func_02088764((char *) p + 0x2427);
    func_02088460((char *) p + 0x242c);
    func_02097dd0((char *) p + 0x243e);
    func_02099e58((char *) p + 0x245c);
    func_0209529c((char *) p + 0x247e);
    return p;
}

void *func_02099ad0(unsigned char *self)
{
    func_0209526c(self + 0x247e);
    func_02099e40(self + 0x245c);
    func_02097dcc(self + 0x243e);
    func_02088450(self + 0x242c);
    func_02088760(self + 0x2427);
    func_02088c0c(self + 0x2416);
    func_020adf64(self + 0x2404);
    func_02088808(self + 0x23ec);
    func_020983fc(self + 0x23e0);
    func_02077d24(self + 0x1f5c);
    func_02077c0c(self + 0x1f0c);
    func_0209ade4(self + 0x1e40);
    func_02097e18(self + 0x1d3c);
    func_0203d388(self + 0x1d3b);
    func_0203cfa0(self + 0x1c18);
    __cxa_vec_cleanup((void *) (self + 0x1bf2), 15, 2, (void (*)(void *)) func_020051b0);
    __cxa_vec_cleanup((void *) (self + 0x11a8), 10, 256, (void (*)(void *)) func_02066688);
    func_02072ce8(self);
    return self;
}

void func_02099ac0(void *dest)
{
    MI_CpuFill8(dest, 0, 0x249c);
}

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

int func_02099a28(unsigned int r0)
{
    return func_020951bc(r0 + 0x247e);
}
