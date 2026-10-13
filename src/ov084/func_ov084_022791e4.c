/* func_ov084_022791e4 @ 0x022791e4, 0x118 bytes, Thumb, module ov084
 * mwccarm 1.2/base -O4,s
 */

void *func_020edf70(unsigned int size);
void func_0203f130(void *p);
void func_0205467c(void *p);
void func_0201b394(void *p);
void func_0201a430(void *p);
void func_020169a8(void *p);
void func_0201b324(void *p);
void func_0201af14(void *p);
void func_0201b370(void *p);
void func_0201adec(void *p);
void func_0201a7ec(void *p);
void func_0201a794(void *p);
void func_02032c64(void *p);
void func_02089c88(void *p);
void func_020f55cc(void *p);
void func_02013c2c(void *p);
void func_02019eb0(void *p);
void func_0201489c(void *p);
void func_02082f60(void *p);
void func_ov084_02278fbc(void *p);

extern unsigned char data_020d8c64[];
extern unsigned char data_020da088[];
extern unsigned char data_ov084_022794ac[];

void *func_ov084_022791e4(void)
{
    void *obj;

    obj = func_020edf70(0x718);
    if (obj) {
        func_0203f130(obj);
        *(void **) obj = (void *) data_020d8c64;
        *(unsigned short *) ((char *) obj + 0xEA) = 0xfff1;
        func_0205467c((char *) obj + 0xEC);
        func_0201b394((char *) obj + 0x2A0);
        func_0201a430((char *) obj + 0x2AC);
        func_020169a8((char *) obj + 0x334);
        func_0201b324((char *) obj + 0x350);
        func_0201af14((char *) obj + 0x3A8);
        func_0201b370((char *) obj + 0x3AA);
        func_0201adec((char *) obj + 0x3B0);
        func_0201a7ec((char *) obj + 0x418);
        func_0201a794((char *) obj + 0x420);
        func_02032c64((char *) obj + 0x49C);
        func_02089c88((char *) obj + 0x4CC);
        func_020f55cc((char *) obj + 0x514);
        func_02013c2c((char *) obj + 0x558);
        func_02019eb0((char *) obj + 0x564);
        func_0201489c((char *) obj + 0x618);
        *(void **) obj = (void *) data_020da088;
        func_02082f60((char *) obj + 0x640);
        *(void **) obj = (void *) data_ov084_022794ac;
        func_ov084_02278fbc((char *) obj + 0x658);
    }
    return obj;
}
