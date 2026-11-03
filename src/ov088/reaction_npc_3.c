/* reaction_npc_3: 7 functions, module ov088
 * mwccarm 1.2/base -O4,s
 * func_ov088_022798ac @ 0x022798ac, 0x118 bytes, Thumb
 * func_ov088_022798a0 @ 0x022798a0, 0xc bytes, Thumb
 * func_ov088_02279870 @ 0x02279870, 0x30 bytes, Thumb
 * func_ov088_02279850 @ 0x02279850, 0x20 bytes, Thumb
 * func_ov088_02279824 @ 0x02279824, 0x2c bytes, Thumb
 * func_ov088_0227981c @ 0x0227981c, 0x8 bytes, Thumb
 * func_ov088_02279814 @ 0x02279814, 0x8 bytes, Thumb
 */

extern void *func_020edf70(unsigned int);
extern void *func_0203f130(void *);
extern void *func_0205467c(void *);
extern void func_0201b394(void *);
extern void *func_0201a430(void *);
extern int func_020169a8(void *);
extern int func_0201b324(void *);
extern void func_0201af14(void *);
extern void func_0201b370(void *);
extern void func_0201adec(void *);
extern void *func_0201a7ec(void *);
extern void func_0201a794(void *);
extern void *func_02032c64(void *);
extern void *func_02089c88(void *);
extern void *func_020f55cc(void *);
extern void func_02013c2c(void *);
extern void *func_02019eb0(void *);
extern void func_0201489c(void *);
extern void *func_02082f60(void *);
extern void *func_ov088_02278d10(void *);
extern unsigned char data_020d8c64[];
extern unsigned char data_020da088[];
extern unsigned char data_ov088_02279cec[];
extern int data_020c8120;
extern int func_0202edc8(void *);
extern void func_0201c280(void *, void *);
extern void func_ov088_02278c94(void *, void *);
extern int func_0202ec58(void *argument0);
extern void func_ov088_02279784(int, int);
extern int func_0202ec14(void *argument0);
extern int func_02041620(void);
extern int func_0208602c(void);
extern int func_020860b8(int argument0);
extern int func_0208786c(int argument0);
extern int data_ov088_02279bf8;
extern int data_ov088_02279bc8;

void *func_ov088_022798ac(void)
{
    void *p;

    p = func_020edf70(0x73c);
    if (p) {
        func_0203f130(p);
        *(void **) p = (void *) data_020d8c64;
        *(unsigned short *) ((char *) p + 0xea) = 0xfff1;
        func_0205467c((char *) p + 0xec);
        func_0201b394((char *) p + 0x2a0);
        func_0201a430((char *) p + 0x2ac);
        func_020169a8((char *) p + 0x334);
        func_0201b324((char *) p + 0x350);
        func_0201af14((char *) p + 0x3a8);
        func_0201b370((char *) p + 0x3aa);
        func_0201adec((char *) p + 0x3b0);
        func_0201a7ec((char *) p + 0x418);
        func_0201a794((char *) p + 0x420);
        func_02032c64((char *) p + 0x49c);
        func_02089c88((char *) p + 0x4cc);
        func_020f55cc((char *) p + 0x514);
        func_02013c2c((char *) p + 0x558);
        func_02019eb0((char *) p + 0x564);
        func_0201489c((char *) p + 0x618);
        *(void **) p = (void *) data_020da088;
        func_02082f60((char *) p + 0x640);
        *(void **) p = (void *) data_ov088_02279cec;
        func_ov088_02278d10((char *) p + 0x658);
    }
    return p;
}

int func_ov088_022798a0(void)
{
    return data_020c8120;
}

int func_ov088_02279870(void *p)
{
    if (func_0202edc8(p) == 0) {
        return 0;
    }
    func_0201c280(p, (char *) p + 0x658);
    func_ov088_02278c94((char *) p + 0x658, p);
    return 1;
}

int func_ov088_02279850(int param)
{
    if (func_0202ec58((void *) param) == 0) {
        return 0;
    }
    func_ov088_02279784(param, 3);
    return 1;
}

int func_ov088_02279824(void *argument0)
{
    if (func_0202ec14(argument0) == 0) {
        return 0;
    }
    if (func_02041620() == 0) {

        func_0208786c(func_020860b8(func_0208602c()));
    }
    return 1;
}

int func_ov088_0227981c(void)
{
    return (int) &data_ov088_02279bf8;
}

int func_ov088_02279814(void)
{
    return (int) &data_ov088_02279bc8;
}
