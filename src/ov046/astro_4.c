/* astro_4: 6 functions, module ov046
 * mwccarm 1.2/base -O4,s
 * func_ov046_02261b6c @ 0x02261b6c, 0x118 bytes, Thumb
 * func_ov046_02261b30 @ 0x02261b30, 0x3c bytes, Thumb
 * func_ov046_02261aa0 @ 0x02261aa0, 0x90 bytes, Thumb
 * func_ov046_02261a6c @ 0x02261a6c, 0x34 bytes, Thumb
 * func_ov046_02261a64 @ 0x02261a64, 0x8 bytes, Thumb
 * func_ov046_02261a5c @ 0x02261a5c, 0x8 bytes, Thumb
 */

typedef struct {
    char pad_00[0x740];
    int unk_740;
} UnkStruct_02261a6c;

extern void *func_020edf70(int size);
extern void *func_0203f130(void *arg0);
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
extern void *__arm func_020f55cc(void *);
extern void func_02013c2c(void *);
extern void *func_02019eb0(void *);
extern void func_0201489c(void *);
extern void *func_02082f60(void *);
extern void *func_ov046_02261304(void *);
extern unsigned char data_020d8c64[];
extern unsigned char data_020da088[];
extern unsigned char data_ov046_022620e0[];
extern int func_0202edc8(void *p);
extern void func_0201c280(void *a, void *b);
extern void func_ov046_02261270(void *a, void *b);
extern int func_0202ec58(void *arg0);
extern void func_ov046_02261268(char *addr, int val);
extern int func_0209dcac(void);
extern int func_02073d90(int value);
extern short *func_0209d358(int a, int b);
extern void func_ov046_022619cc(char *addr, int val);
extern int data_020ccf94;
extern int func_0202ec14(void *arg0);
extern void func_0209129c(int);
extern int data_ov046_02262028;
extern int data_ov046_02261ff8;

void *func_ov046_02261b6c(void)
{
    char *self;
    self = (char *) func_020edf70(0x744);
    if (self) {
        func_0203f130((void *) self);
        *(int *) self = (unsigned int) data_020d8c64;
        *(unsigned short *) (self + 0xea) = 0xfff1;
        func_0205467c(self + 0xec);
        func_0201b394(self + 0x2a0);
        func_0201a430(self + 0x2ac);
        func_020169a8(self + 0x334);
        func_0201b324(self + 0x350);
        func_0201af14(self + 0x3a8);
        func_0201b370(self + 0x3aa);
        func_0201adec(self + 0x3b0);
        func_0201a7ec(self + 0x418);
        func_0201a794(self + 0x420);
        func_02032c64(self + 0x49c);
        func_02089c88(self + 0x4cc);
        func_020f55cc(self + 0x514);
        func_02013c2c(self + 0x558);
        func_02019eb0(self + 0x564);
        func_0201489c(self + 0x618);
        *(int *) self = (unsigned int) data_020da088;
        func_02082f60(self + 0x640);
        *(int *) self = (unsigned int) data_ov046_022620e0;
        func_ov046_02261304(self + 0x658);
    }
    return self;
}

int func_ov046_02261b30(void *p)
{
    if (func_0202edc8(p) == 0) {
        return 0;
    }
    func_0201c280(p, (char *) p + 0x658);
    func_ov046_02261270((char *) p + 0x658, p);
    *(int *) ((char *) p + 0x740) = -1;
    return 1;
}

int func_ov046_02261aa0(char *p)
{
    if (func_0202ec58((void *) p) == 0) {
        return 0;
    }
    *(short *) (p + 0x73a) = *(short *) (p + 0x8e);
    *(short *) (p + 0x73c) = 0;
    *(int *) (p + 0x4e8) |= 2;
    func_ov046_02261268(p + 0x658, 5);
    if (func_0209dcac() == 2 || func_0209dcac() == 3 || func_02073d90(data_020ccf94) != 0) {
        goto call0;
    }
    if (func_0209d358(0, 0x4a)[0] == 0) {
        goto call2;
    }
call0:
    func_ov046_022619cc(p, 0);
    goto ret;
call2:
    func_ov046_022619cc(p, 2);
ret:
    return 1;
}

int func_ov046_02261a6c(UnkStruct_02261a6c *self)
{
    if (func_0202ec14((void *) self) == 0) {
        return 0;
    }
    if (self->unk_740 != -1) {
        func_0209129c(self->unk_740);
        self->unk_740 = -1;
    }
    return 1;
}

int func_ov046_02261a64(void)
{
    return (int) &data_ov046_02262028;
}

int func_ov046_02261a5c(void)
{
    return (int) &data_ov046_02261ff8;
}
