/* func_ov080_02279060 @ 0x02279060, 0x118 bytes, Thumb, module ov080
 * mwccarm 1.2/base -O4,s
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
extern void *func_ov080_02278e48(void *);

extern unsigned char data_020d8c64[];
extern unsigned char data_020da088[];
extern unsigned char data_ov080_022792ec[];

void *func_ov080_02279060(void)
{
    void *s = func_020edf70(0x710);
    if (s != 0) {
        func_0203f130(s);
        *(int *) s = (int) (unsigned int) data_020d8c64;
        *(unsigned short *) ((char *) s + 0xea) = 0xfff1;
        func_0205467c((char *) s + 0xec);
        func_0201b394((char *) s + 0x2a0);
        func_0201a430((char *) s + 0x2ac);
        func_020169a8((char *) s + 0x334);
        func_0201b324((char *) s + 0x350);
        func_0201af14((char *) s + 0x3a8);
        func_0201b370((char *) s + 0x3aa);
        func_0201adec((char *) s + 0x3b0);
        func_0201a7ec((char *) s + 0x418);
        func_0201a794((char *) s + 0x420);
        func_02032c64((char *) s + 0x49c);
        func_02089c88((char *) s + 0x4cc);
        func_020f55cc((char *) s + 0x514);
        func_02013c2c((char *) s + 0x558);
        func_02019eb0((char *) s + 0x564);
        func_0201489c((char *) s + 0x618);
        *(int *) s = (int) (unsigned int) data_020da088;
        func_02082f60((char *) s + 0x640);
        *(int *) s = (int) (unsigned int) data_ov080_022792ec;
        func_ov080_02278e48((char *) s + 0x658);
    }
    return s;
}
