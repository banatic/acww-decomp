/* walrus_3: 7 functions, module ov079
 * mwccarm 1.2/base -O4,s
 * func_ov079_02279d5c @ 0x02279d5c, 0x118 bytes, Thumb
 * func_ov079_02279d50 @ 0x02279d50, 0xc bytes, Thumb
 * func_ov079_02279d20 @ 0x02279d20, 0x30 bytes, Thumb
 * func_ov079_02279d00 @ 0x02279d00, 0x20 bytes, Thumb
 * func_ov079_02279cd4 @ 0x02279cd4, 0x2c bytes, Thumb
 * func_ov079_02279ccc @ 0x02279ccc, 0x8 bytes, Thumb
 * func_ov079_02279cc4 @ 0x02279cc4, 0x8 bytes, Thumb
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
extern void *func_ov079_02278d34(void *);
extern unsigned char data_020d8c64;
extern unsigned char data_020da088;
extern unsigned char data_ov079_0227a104;
extern int data_020c8120;
extern int func_0202edc8(void *);
extern void func_0201c280(void *, void *);
extern void func_ov079_02278c7c(void *, void *);
extern int func_0202ec58(void *argument0);
extern void func_ov079_02279c34(int, int);
extern int func_0202ec14(void *argument0);
extern int func_02041620(void);
extern int func_0208602c(void);
extern int func_020860b8(int argument0);
extern int func_0208786c(int argument0);
extern int data_ov079_0227a050;
extern int data_ov079_0227a020;

void *func_ov079_02279d5c(void)
{
    void *obj = func_020edf70(0x724);
    if (obj != 0) {
        func_0203f130(obj);
        *(void **) obj = (void *) &data_020d8c64;
        *(unsigned short *) ((char *) obj + 0xea) = 0xfff1;
        func_0205467c((char *) obj + 0xec);
        func_0201b394((char *) obj + 0x2a0);
        func_0201a430((char *) obj + 0x2ac);
        func_020169a8((char *) obj + 0x334);
        func_0201b324((char *) obj + 0x350);
        func_0201af14((char *) obj + 0x3a8);
        func_0201b370((char *) obj + 0x3aa);
        func_0201adec((char *) obj + 0x3b0);
        func_0201a7ec((char *) obj + 0x418);
        func_0201a794((char *) obj + 0x420);
        func_02032c64((char *) obj + 0x49c);
        func_02089c88((char *) obj + 0x4cc);
        func_020f55cc((char *) obj + 0x514);
        func_02013c2c((char *) obj + 0x558);
        func_02019eb0((char *) obj + 0x564);
        func_0201489c((char *) obj + 0x618);
        *(void **) obj = (void *) &data_020da088;
        func_02082f60((char *) obj + 0x640);
        *(void **) obj = (void *) &data_ov079_0227a104;
        func_ov079_02278d34((char *) obj + 0x658);
    }
    return obj;
}

int func_ov079_02279d50(void)
{
    return data_020c8120;
}

int func_ov079_02279d20(void *self)
{
    if (!func_0202edc8(self)) {
        return 0;
    }
    func_0201c280(self, (char *) self + 0x658);
    func_ov079_02278c7c((char *) self + 0x658, self);
    return 1;
}

int func_ov079_02279d00(int param)
{
    int result;
    if (func_0202ec58((void *) param) == 0) {
        result = 0;
    } else {
        func_ov079_02279c34(param, 3);
        result = 1;
    }
    return result;
}

int func_ov079_02279cd4(void *argument0)
{
    if (func_0202ec14(argument0) == 0) {
        return 0;
    }
    if (func_02041620() == 0) {

        func_0208786c(func_020860b8(func_0208602c()));
    }
    return 1;
}

int func_ov079_02279ccc(void)
{
    return (int) &data_ov079_0227a050;
}

int func_ov079_02279cc4(void)
{
    return (int) &data_ov079_0227a020;
}
