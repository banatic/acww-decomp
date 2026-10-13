/* func_ov128_0229c408 @ 0x0229c408, 0x5c bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov127_0229a0bc(void *p);
extern void func_ov128_0229baa8(void *p);
extern void func_ov004_0222be7c(void);
extern void func_0203584c(void *p);

extern unsigned char data_021c526c[];

void func_ov128_0229c408(void *self)
{
    unsigned short *p16;
    unsigned int *p32;
    unsigned char *p8;
    void *p;

    p16 = (unsigned short *) ((char *) self + 0x2d68);
    *p16 = 0;
    p = (char *) self + 0x4a4;
    func_ov127_0229a0bc(p);
    p32 = (unsigned int *) ((char *) self + 0x2d48);
    *p32 = 0x80;
    p32 = (unsigned int *) ((char *) self + 0x2d4c);
    *p32 = 0x60;
    p8 = (unsigned char *) ((char *) self + 0x2d6c);
    *p8 = 1;
    func_ov128_0229baa8(self);
    func_ov004_0222be7c();
    p = *(void **) data_021c526c;
    p = (char *) p + 0x2f0;
    func_0203584c(p);
}
