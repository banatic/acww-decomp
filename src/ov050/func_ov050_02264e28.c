/* func_ov050_02264e28 @ 0x02264e28, 0x134 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(unsigned int);
extern void *func_0203f130(void *argument0);
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
extern void *func_ov050_022636c8(void *);
extern unsigned char data_020d8c64;
extern unsigned char data_020da088;
extern unsigned char data_ov050_02265a60;

void *func_ov050_02264e28(void)
{
    void *p;
    p = func_020edf70(0x744);
    if (p == 0) {
        goto skip;
    }
    func_0203f130(p);
    *(void **) p = (void *) &data_020d8c64;
    *(unsigned short *) ((char *) p + 0xEA) = 0xFFF1;
    func_0205467c((char *) p + 0xEC);
    func_0201b394((char *) p + 0x2A0);
    func_0201a430((char *) p + 0x2AC);
    func_020169a8((char *) p + 0x334);
    func_0201b324((char *) p + 0x350);
    func_0201af14((char *) p + 0x3A8);
    func_0201b370((char *) p + 0x3AA);
    func_0201adec((char *) p + 0x3B0);
    func_0201a7ec((char *) p + 0x418);
    func_0201a794((char *) p + 0x420);
    func_02032c64((char *) p + 0x49C);
    func_02089c88((char *) p + 0x4CC);
    func_020f55cc((char *) p + 0x514);
    func_02013c2c((char *) p + 0x558);
    func_02019eb0((char *) p + 0x564);
    func_0201489c((char *) p + 0x618);
    *(void **) p = (void *) &data_020da088;
    func_02082f60((char *) p + 0x640);
    *(void **) p = (void *) &data_ov050_02265a60;
    func_ov050_022636c8((char *) p + 0x658);
    *(unsigned short *) ((char *) p + 0x732) = 0xFFF1;
    *(unsigned int *) ((char *) p + 0x734) = 0;
    *(unsigned int *) ((char *) p + 0x738) = 0;
skip:
    return p;
}
