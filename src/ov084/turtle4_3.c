/* turtle4_3: 5 functions, module ov084
 * mwccarm 1.2/base -O4,s
 * func_ov084_022791e4 @ 0x022791e4, 0x118 bytes, Thumb
 * func_ov084_022791b4 @ 0x022791b4, 0x30 bytes, Thumb
 * func_ov084_02279120 @ 0x02279120, 0x94 bytes, Thumb
 * func_ov084_02279118 @ 0x02279118, 0x8 bytes, Thumb
 * func_ov084_02279110 @ 0x02279110, 0x8 bytes, Thumb
 */

typedef struct {
    unsigned char data[8];
} UnkStruct_02279120;

void *func_020edf70(unsigned int size);
void *func_0203f130(void *p);
void *func_0205467c(void *p);
void func_0201b394(void *p);
void *func_0201a430(void *p);
int func_020169a8(void *p);
int func_0201b324(void *p);
void func_0201af14(void *p);
void func_0201b370(void *p);
void func_0201adec(void *p);
void *func_0201a7ec(void *p);
void func_0201a794(void *p);
void *func_02032c64(void *p);
void *func_02089c88(void *p);
void *func_020f55cc(void *p);
void func_02013c2c(void *p);
void *func_02019eb0(void *p);
void func_0201489c(void *p);
void *func_02082f60(void *p);
void *func_ov084_02278fbc(void *p);
extern unsigned char data_020d8c64[];
extern unsigned char data_020da088[];
extern unsigned char data_ov084_022794ac[];
extern int func_0202edc8(void *self);
extern void func_0201c280(void *a, void *b);
extern void func_ov084_02278f60(void *a, void *b);
extern int func_0202ec58(void *p);
extern void func_ov084_02279080(void *p, int a);
extern void func_020866b8(void *p, int a);
extern void func_02016764(void *a, void *b, int c, int d, int e, int f, int g, int h);
extern void func_02054188(void *a, int b, int c);
extern void func_0209df64(void *p);
extern int _s32_div_f(int a, int b);
extern unsigned char data_021f3aa4[];
extern int data_ov084_022793f8;
extern int data_ov084_022793c8;

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

int func_ov084_022791b4(void *self)
{
    if (!func_0202edc8(self)) {
        return 0;
    }
    func_0201c280(self, (char *) self + 0x658);
    func_ov084_02278f60((char *) self + 0x658, self);
    return 1;
}

int func_ov084_02279120(unsigned char *self)
{
    if (func_0202ec58(self) == 0) {
        return 0;
    }

    func_ov084_02279080(self, 0);
    func_020866b8((void *) data_021f3aa4, 0);
    func_02016764(self + 0x334, self, 0x140, 0, 0, 0x1000, 0, 1);
    func_02054188(self + 0xec, 12, 14);

    *(unsigned int *) (self + 0x4e8) |= 2;

    {
        UnkStruct_02279120 local;
        func_0209df64(&local);
        *(unsigned char *) (self + 0x714) = (unsigned char) _s32_div_f(((unsigned char *) &local)[0] - 1, 7);
        ++*(unsigned char *) (self + 0x714);
    }

    return 1;
}

int func_ov084_02279118(void)
{
    return (int) &data_ov084_022793f8;
}

int func_ov084_02279110(void)
{
    return (int) &data_ov084_022793c8;
}
