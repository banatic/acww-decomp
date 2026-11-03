/* mole_4: 7 functions, module ov077
 * mwccarm 1.2/base -O4,s
 * func_ov077_022794d8 @ 0x022794d8, 0x128 bytes, Thumb
 * func_ov077_02279474 @ 0x02279474, 0x64 bytes, Thumb
 * func_ov077_02279430 @ 0x02279430, 0x44 bytes, Thumb
 * func_ov077_02279414 @ 0x02279414, 0x1c bytes, Thumb
 * func_ov077_022793f8 @ 0x022793f8, 0x1c bytes, Thumb
 * func_ov077_022793f0 @ 0x022793f0, 0x8 bytes, Thumb
 * func_ov077_022793e8 @ 0x022793e8, 0x8 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x654];
    int unk_654;
} UnkStruct_022793f8;

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
extern void *func_ov077_02278d64(void *);
extern unsigned char data_020d8c64[];
extern unsigned char data_020da088[];
extern unsigned char data_ov077_0227988c[];
extern int func_0202edc8(void *p);
extern void func_0201c280(void *a, void *b);
extern void func_ov077_02278ca0(void *a, void *b);
extern void func_0201b38c(void *a, int b);
extern void func_0201b388(void *a, int b);
extern int func_0202ec58(void *arg0);
extern void func_0203edf4(int, int);
extern void func_ov077_02279358(int, int);
extern void func_0203edd0(int);
extern void func_0203e310(void);
extern int func_0202ec14(void *parameter0);
extern void func_0203e304(void);
extern int func_0201b790(void *);
extern int data_ov077_022797b4;
extern int data_ov077_02279784;

void *func_ov077_022794d8(void)
{
    void *p = func_020edf70(0x728);
    if (p) {
        func_0203f130(p);
        *(void **) p = (void *) data_020d8c64;
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
        *(void **) p = (void *) data_020da088;
        func_02082f60((char *) p + 0x640);
        *(void **) p = (void *) data_ov077_0227988c;
        func_ov077_02278d64((char *) p + 0x658);
        {
            int zero = 0;
            *(int *) ((char *) p + 0x71C) = zero;
            *(int *) ((char *) p + 0x720) = zero;
        }
    }
    return p;
}

int func_ov077_02279474(unsigned char *self)
{
    if (func_0202edc8(self) == 0) {
        return 0;
    }
    self[0x718] = 0xff;
    func_0201c280(self, self + 0x658);
    func_ov077_02278ca0(self + 0x658, self);
    func_0201b38c(self + 0x2a0, 0xfc);
    func_0201b388(self + 0x2a0, 0xfc);
    self[0x511] = 0;
    self[0x510] = 0;
    return 1;
}

int func_ov077_02279430(int param)
{
    int result;
    int *ptr;

    if (func_0202ec58((void *) param) == 0) {
        return 0;
    }
    ptr = (int *) ((char *) param + 0x4e8);
    *ptr |= 2;
    func_0203edf4(param, 0);
    func_ov077_02279358(param, 3);
    func_0203edd0(param);
    func_0203e310();
    return 1;
}

int func_ov077_02279414(void *arg0)
{
    if (func_0202ec14((void *) arg0) == 0) {
        return 0;
    }
    func_0203e304();
    return 1;
}

int func_ov077_022793f8(UnkStruct_022793f8 *self)
{
    if (self->unk_654 != 3) {
        func_0201b790(self);
    }
    return 1;
}

int func_ov077_022793f0(void)
{
    return (int) &data_ov077_022797b4;
}

int func_ov077_022793e8(void)
{
    return (int) &data_ov077_02279784;
}
