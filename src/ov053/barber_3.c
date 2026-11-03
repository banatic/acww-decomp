/* barber_3: 5 functions, module ov053
 * mwccarm 1.2/base -O4,s
 * func_ov053_022616a8 @ 0x022616a8, 0x118 bytes, Thumb
 * func_ov053_0226164c @ 0x0226164c, 0x5c bytes, Thumb
 * func_ov053_022615c4 @ 0x022615c4, 0x88 bytes, Thumb
 * func_ov053_022615bc @ 0x022615bc, 0x8 bytes, Thumb
 * func_ov053_022615b4 @ 0x022615b4, 0x8 bytes, Thumb
 */

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_0226164c;

typedef struct UnkStruct_022615c4 UnkStruct_022615c4;

struct UnkStruct_022615c4 {
    char pad_00[0x4e8];
    unsigned int unk_4E8;
    char pad_4EC[0x22d];
    unsigned char unk_719;
    char pad_71A[2];
    unsigned short unk_71C;
};

typedef struct UnkStruct_022615c4_2 UnkStruct_022615c4_2;

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
extern void *func_ov053_02260c14(void *);
extern char data_020d8c64;
extern char data_020da088;
extern char data_ov053_02261b98;
extern int func_0202edc8(void *);
extern void func_0201c280(void *, void *);
extern void func_ov053_02260bb8(void *, void *);
extern void func_0201c3f4(void *, int);
extern void func_0201af28(void *, int, int, int, int);
extern UnkStruct_0226164c data_ov053_022617e0;
extern int func_0202ec58(UnkStruct_022615c4 *p);
extern UnkStruct_022615c4_2 *data_020ccf94;
extern int func_02073d90(UnkStruct_022615c4_2 *p);
extern int func_02030864(int);
extern void func_ov053_02261524(UnkStruct_022615c4 *p, int);
extern int func_020b65b8(void);
extern int data_ov053_02261a74;
extern int data_ov053_02261a44;

void *func_ov053_022616a8(void)
{
    void *p;
    p = func_020edf70(0x720);
    if (p) {
        func_0203f130(p);
        *(void **) p = &data_020d8c64;
        *(unsigned short *) ((char *) p + 0xea) = 0xfff1;
        func_0205467c((char *) p + 0xec);
        func_0201b394((char *) p + 0x2a0);
        func_0201a430((char *) p + 0x2ac);
        func_020169a8((char *) p + 0x334);
        func_0201b324((char *) p + 0x350);
        func_0201af14((char *) p + 0x3a8);
        func_0201b370((char *) p + 0x3aa);
        func_0201adec((char *) p + 0x3b0);
        func_0201a7ec((char *) p + 0x418);
        func_0201a794((char *) p + 0x420);
        func_02032c64((char *) p + 0x49c);
        func_02089c88((char *) p + 0x4cc);
        func_020f55cc((char *) p + 0x514);
        func_02013c2c((char *) p + 0x558);
        func_02019eb0((char *) p + 0x564);
        func_0201489c((char *) p + 0x618);
        *(void **) p = &data_020da088;
        func_02082f60((char *) p + 0x640);
        *(void **) p = &data_ov053_02261b98;
        func_ov053_02260c14((char *) p + 0x658);
    }
    return p;
}

int func_ov053_0226164c(void *self)
{
    if (!func_0202edc8(self)) {
        return 0;
    }
    func_0201c280(self, (char *) self + 0x658);
    func_ov053_02260bb8((char *) self + 0x658, self);
    func_0201c3f4(self, 0x100);
    func_0201af28((char *) self + 0x350, 2, data_ov053_022617e0.a, data_ov053_022617e0.b, data_ov053_022617e0.c);
    return 1;
}

int func_ov053_022615c4(UnkStruct_022615c4 *param)
{
    UnkStruct_022615c4_2 *p;

    if (func_0202ec58(param) == 0) {
        return 0;
    }

    p = data_020ccf94;

    if (func_02073d90(p) == 0) {
        func_02030864(0);
    }

    param->unk_71C = 0;
    param->unk_4E8 |= 2;
    param->unk_719 = 0;

    if (func_02073d90(p) != 0) {
        func_ov053_02261524(param, 1);
        return 1;
    } else {
        if (func_020b65b8() == 29) {
            func_ov053_02261524(param, 0);
        } else {
            func_ov053_02261524(param, 1);
        }
        return 1;
    }
}

int func_ov053_022615bc(void)
{
    return (int) &data_ov053_02261a74;
}

int func_ov053_022615b4(void)
{
    return (int) &data_ov053_02261a44;
}
