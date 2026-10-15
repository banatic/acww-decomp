/* func_ov083_02278fe8 @ 0x02278fe8, 0x118 bytes, Thumb, module ov083
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(int size);
extern void *func_0203f130(void *p);
extern void *func_0205467c(void *p);
extern void func_0201b394(void *p);
extern void *func_0201a430(void *p);
extern int func_020169a8(void *p);
extern int func_0201b324(void *p);
extern void func_0201af14(void *p);
extern void func_0201b370(void *p);
extern void func_0201adec(void *p);
extern void *func_0201a7ec(void *p);
extern void func_0201a794(void *p);
extern void *func_02032c64(void *p);
extern void *func_02089c88(void *p);
extern void *func_020f55cc(void *p);
extern void func_02013c2c(void *p);
extern void *func_02019eb0(void *p);
extern void func_0201489c(void *p);
extern void *func_02082f60(void *p);
extern void *func_ov083_02278d7c(void *p);

extern char data_020d8c64[];
extern char data_020da088[];
extern char data_ov083_0227928c[];

void *func_ov083_02278fe8(void)
{
    unsigned char *p;

    p = func_020edf70(0x71c);
    if (p != 0) {
        func_0203f130(p);

        *(void **) p = data_020d8c64;
        *(unsigned short *) (p + 0xea) = 0xfff1;
        func_0205467c(p + 0xec);
        func_0201b394(p + 0x2a0);
        func_0201a430(p + 0x2ac);
        func_020169a8(p + 0x334);
        func_0201b324(p + 0x350);
        func_0201af14(p + 0x3a8);
        func_0201b370(p + 0x3aa);
        func_0201adec(p + 0x3b0);
        func_0201a7ec(p + 0x418);
        func_0201a794(p + 0x420);
        func_02032c64(p + 0x49c);
        func_02089c88(p + 0x4cc);
        func_020f55cc(p + 0x514);
        func_02013c2c(p + 0x558);
        func_02019eb0(p + 0x564);
        func_0201489c(p + 0x618);
        *(void **) p = data_020da088;
        func_02082f60(p + 0x640);
        *(void **) p = data_ov083_0227928c;
        func_ov083_02278d7c(p + 0x65c);
    }
    return p;
}
