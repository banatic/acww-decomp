/* func_ov075_0227960c @ 0x0227960c, 0x118 bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(int size);
extern void *func_0203f130(void *arg0);
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
extern void *func_ov075_02278bb8(void *p);

extern int data_020d8c64;
extern int data_020da088;
extern int data_ov075_022799fc;

void *func_ov075_0227960c(void)
{
    void *ptr;

    ptr = func_020edf70(0x71c);
    if (ptr != 0) {
        func_0203f130((void *) ptr);
        *(void **) ptr = &data_020d8c64;
        *(unsigned short *) ((char *) ptr + 0xea) = 0xfff1;
        func_0205467c((char *) ptr + 0xec);

        func_0201b394((char *) ptr + 0x2a0);
        func_0201a430((char *) ptr + 0x2ac);
        func_020169a8((char *) ptr + 0x334);
        func_0201b324((char *) ptr + 0x350);
        func_0201af14((char *) ptr + 0x3a8);
        func_0201b370((char *) ptr + 0x3aa);
        func_0201adec((char *) ptr + 0x3b0);
        func_0201a7ec((char *) ptr + 0x418);
        func_0201a794((char *) ptr + 0x420);
        func_02032c64((char *) ptr + 0x49c);
        func_02089c88((char *) ptr + 0x4cc);
        func_020f55cc((char *) ptr + 0x514);
        func_02013c2c((char *) ptr + 0x558);
        func_02019eb0((char *) ptr + 0x564);
        func_0201489c((char *) ptr + 0x618);

        *(void **) ptr = &data_020da088;
        func_02082f60((char *) ptr + 0x640);
        *(void **) ptr = &data_ov075_022799fc;
        func_ov075_02278bb8((char *) ptr + 0x658);
    }

    return ptr;
}
