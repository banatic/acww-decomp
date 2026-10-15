/* func_ov068_02274dc8 @ 0x02274dc8, 0x118 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(unsigned int size);
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
extern void *func_ov068_02274714(void *p);

extern char data_020d8c64[];
extern char data_020da088[];
extern char data_ov068_02277e50[];

void *func_ov068_02274dc8(void)
{
    void *obj = func_020edf70(0x750);
    if (obj != 0) {
        char *base = (char *) obj;
        func_0203f130(obj);
        *(void **) obj = (void *) data_020d8c64;
        *(unsigned short *) (base + 0xea) = 0xfff1;
        func_0205467c(base + 0xec);
        func_0201b394(base + 0x2a0);
        func_0201a430(base + 0x2ac);
        func_020169a8(base + 0x334);
        func_0201b324(base + 0x350);
        func_0201af14(base + 0x3a8);
        func_0201b370(base + 0x3aa);
        func_0201adec(base + 0x3b0);
        func_0201a7ec(base + 0x418);
        func_0201a794(base + 0x420);
        func_02032c64(base + 0x49c);
        func_02089c88(base + 0x4cc);
        func_020f55cc(base + 0x514);
        func_02013c2c(base + 0x558);
        func_02019eb0(base + 0x564);
        func_0201489c(base + 0x618);
        *(void **) obj = (void *) data_020da088;
        func_02082f60(base + 0x640);
        *(void **) obj = (void *) data_ov068_02277e50;
        func_ov068_02274714(base + 0x65c);
    }
    return obj;
}
