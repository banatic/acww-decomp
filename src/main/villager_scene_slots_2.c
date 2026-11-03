/* villager_scene_slots_2: 18 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202e8e4 @ 0x0202e8e4, 0x118 bytes, Thumb
 * func_0202e7e4 @ 0x0202e7e4, 0x100 bytes, Thumb
 * func_0202e6e0 @ 0x0202e6e0, 0x104 bytes, Thumb
 * func_0202e5e0 @ 0x0202e5e0, 0x100 bytes, Thumb
 * func_0202e58c @ 0x0202e58c, 0x54 bytes, Thumb
 * func_0202e550 @ 0x0202e550, 0x3c bytes, Thumb
 * func_0202e530 @ 0x0202e530, 0x20 bytes, Thumb
 * func_0202e50c @ 0x0202e50c, 0x24 bytes, Thumb
 * func_0202e508 @ 0x0202e508, 0x4 bytes, Thumb
 * func_0202e504 @ 0x0202e504, 0x2 bytes, Thumb
 * func_0202e4c8 @ 0x0202e4c8, 0x3c bytes, Thumb
 * func_0202e498 @ 0x0202e498, 0x30 bytes, Thumb
 * func_0202e468 @ 0x0202e468, 0x30 bytes, Thumb
 * func_0202e45c @ 0x0202e45c, 0xc bytes, Thumb
 * func_0202e430 @ 0x0202e430, 0x2c bytes, Thumb
 * func_0202e42c @ 0x0202e42c, 0x4 bytes, Thumb
 * func_0202e428 @ 0x0202e428, 0x4 bytes, Thumb
 * func_0202e424 @ 0x0202e424, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xEA];
    u16 unk_EA;
    u8 pad_EC[0x830 - 0xEC];
    u32 unk_830;
    u32 unk_834;
} UnkStruct_0202e58c;

typedef struct {
    unsigned char pad_00[0x830];
    void *unk_830;
} UnkStruct_0202e550;

typedef struct {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_0202e530;

extern void *data_020d8c64;
extern void *data_020d9e88;
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
extern void *func_0202e0a8(void *);
extern void *func_0202de9c(void *);
extern void *func_02082fd4(void *);
extern int func_0201cdcc(void *);
extern void *data_020d8414;
extern void *func_0201cdbc(void *);
extern void *func_02082fbc(void *);
extern void *func_0202de84(void *);
extern void *func_0202e094(void *);
extern void func_02014898(void *);
extern void func_02019eac(void *);
extern void func_02013c28(void *);
extern void func_020f5914(void *);
extern void *func_02089c70(void *);
extern void *func_02032c50(void *);
extern void func_0201a790(void *);
extern void func_0201a7e8(void *);
extern void func_0201ade4(void *);
extern void func_0201b320(void *);
extern int func_02016998(void *);
extern void *func_0201a3f8(void *);
extern void func_0201b390(void *);
extern void *func_02054630(void *);
extern void *func_0203f080(void *);
extern void func_020edf54(void *);
extern u32 func_0201c444(void *self);
extern u32 func_0207cec0(void *arg1, u32 arg2);
extern u32 func_0207f270(u32 object);
extern u8 data_021e5a2c[];
extern unsigned int func_0208150c(void *p);
extern int func_02003704(void *);
extern int func_02003648(unsigned char *);
extern int func_02003618(int, int);
extern int func_020036c0(unsigned char *);
extern int func_02064328(void *a, void *b, int c, int d);
extern char data_021c1d84[];
extern char data_020d9fd8[];
extern char data_021c1da4[];
extern char data_020d9fc0[];
extern int func_0201cd2c(void *ptr);
extern void func_0201cc6c(void *ptr, int arg1, int arg2);

void *func_0202e8e4(u8 *p)
{
    func_0203f130(p);
    *(void **) p = &data_020d8c64;
    *(u16 *) (p + 0xea) = 0xfff1;
    func_0205467c(p + 0xec);
    func_0201b394(p + 0x2a0);
    func_0201a430(p + 0x2ac);
    func_020169a8(p + 0x334);
    func_0201b324(p + 0x350);
    func_0201af14(p + 0x3a8);
    func_0201b370(p + 0x3aa);
    func_0201adec(p + 0x3b0);
    func_0201a7ec(p + 0x418);
    func_0201a794(p + 0x420);
    func_02032c64(p + 0x49c);
    func_02089c88(p + 0x4cc);
    func_020f55cc(p + 0x514);
    func_02013c2c(p + 0x558);
    func_02019eb0(p + 0x564);
    func_0201489c(p + 0x618);
    *(void **) p = &data_020d9e88;
    func_0202e0a8(p + 0x64c);
    func_0202de9c(p + 0x680);
    func_02082fd4(p + 0x828);
    func_0201cdcc(p + 0x83c);
    return p;
}

void *func_0202e7e4(u8 *p)
{
    *(void **) p = &data_020d9e88;
    func_0201cdbc(p + 0x83c);
    func_02082fbc(p + 0x828);
    func_0202de84(p + 0x680);
    func_0202e094(p + 0x64c);
    *(void **) p = &data_020d8c64;
    func_02014898(p + 0x618);
    func_02019eac(p + 0x564);
    func_02013c28(p + 0x558);
    *(void **) (p + 0x514) = &data_020d8414;
    func_020f5914(p + 0x514);
    func_02089c70(p + 0x4cc);
    func_02032c50(p + 0x49c);
    func_0201a790(p + 0x420);
    func_0201a7e8(p + 0x418);
    func_0201ade4(p + 0x3b0);
    func_0201b320(p + 0x350);
    func_02016998(p + 0x334);
    func_0201a3f8(p + 0x2ac);
    func_0201b390(p + 0x2a0);
    func_02054630(p + 0xec);
    func_0203f080(p);
    return p;
}

void *func_0202e6e0(u8 *p)
{
    *(void **) p = &data_020d9e88;
    func_0201cdbc(p + 0x83c);
    func_02082fbc(p + 0x828);
    func_0202de84(p + 0x680);
    func_0202e094(p + 0x64c);
    *(void **) p = &data_020d8c64;
    func_02014898(p + 0x618);
    func_02019eac(p + 0x564);
    func_02013c28(p + 0x558);
    *(void **) (p + 0x514) = &data_020d8414;
    func_020f5914(p + 0x514);
    func_02089c70(p + 0x4cc);
    func_02032c50(p + 0x49c);
    func_0201a790(p + 0x420);
    func_0201a7e8(p + 0x418);
    func_0201ade4(p + 0x3b0);
    func_0201b320(p + 0x350);
    func_02016998(p + 0x334);
    func_0201a3f8(p + 0x2ac);
    func_0201b390(p + 0x2a0);
    func_02054630(p + 0xec);
    func_0203f080(p);
    func_020edf54(p);
    return p;
}

void *func_0202e5e0(u8 *p)
{
    *(void **) p = &data_020d9e88;
    func_0201cdbc(p + 0x83c);
    func_02082fbc(p + 0x828);
    func_0202de84(p + 0x680);
    func_0202e094(p + 0x64c);
    *(void **) p = &data_020d8c64;
    func_02014898(p + 0x618);
    func_02019eac(p + 0x564);
    func_02013c28(p + 0x558);
    *(void **) (p + 0x514) = &data_020d8414;
    func_020f5914(p + 0x514);
    func_02089c70(p + 0x4cc);
    func_02032c50(p + 0x49c);
    func_0201a790(p + 0x420);
    func_0201a7e8(p + 0x418);
    func_0201ade4(p + 0x3b0);
    func_0201b320(p + 0x350);
    func_02016998(p + 0x334);
    func_0201a3f8(p + 0x2ac);
    func_0201b390(p + 0x2a0);
    func_02054630(p + 0xec);
    func_0203f080(p);
    return p;
}

void func_0202e58c(UnkStruct_0202e58c *self)
{
    if (((self->unk_EA & 0xF000) >> 12) == 14) {
        self->unk_830 = func_0207cec0(data_021e5a2c, func_0201c444(self));
        if (self->unk_830 != 0) {
            self->unk_834 = func_0207f270(self->unk_830);
        } else {
            self->unk_834 = 0;
        }
    }
}

int func_0202e550(UnkStruct_0202e550 *param)
{
    int result = -1;
    if (param->unk_830 != 0) {
        if (func_02003704((void *) func_0208150c(param->unk_830)) == 1) {
            result = func_02003648((unsigned char *) func_0208150c(param->unk_830));
        }
    }
    return result;
}

void func_0202e530(UnkStruct_0202e530 *s, int arg2)
{
    if (s->unk_830) {
        func_02003618((int) func_0208150c((void *) s->unk_830), arg2);
    }
}

int func_0202e50c(void *arg0)
{
    int result = 2;
    if (*(unsigned int *) ((char *) arg0 + 0x830) != 0) {
        result = func_020036c0((unsigned char *) (int) func_0208150c((void *) (*(unsigned int *) ((char *) arg0 + 0x830))));
    }
    return result;
}

int func_0202e508(void *object)
{
    (void) object;
    return 1;
}

void func_0202e504(void *object)
{
    (void) object;
}

int func_0202e4c8(void *param)
{
    unsigned int object;

    if (((*(unsigned short *) ((char *) param + 0xEA) & 0xF000) >> 12) == 0xE) {
        if ((object = *(unsigned int *) ((char *) param + 0x830)) != 0) {
            return func_02003648((unsigned char *) func_0208150c((void *) object));
        }
    }
    return 0xFFFF;
}

void *func_0202e498(void *argument0)
{
    int x = func_0202e550((UnkStruct_0202e550 *) ((void *) argument0));
    if (x == -1) {
        x = 0;
    }
    func_02064328(data_021c1d84, data_020d9fd8, x & 0xf8, x);
    return data_021c1d84;
}

void *func_0202e468(void *argument0)
{
    int x = func_0202e550((UnkStruct_0202e550 *) ((void *) argument0));
    if (x == -1) {
        x = 0;
    }
    func_02064328(data_021c1da4, data_020d9fc0, x & 0xf8, x);
    return data_021c1da4;
}

unsigned int func_0202e45c(unsigned int *r0)
{
    return r0[0x20c];
}

void func_0202e430(void *arg0, int arg1, int arg2)
{
    if (func_0201cd2c((void *) ((char *) arg0 + 0x83c))) {
        func_0201cc6c((void *) ((char *) arg0 + 0x83c), arg1, arg2);
    }
}

int func_0202e42c(void *object)
{
    (void) object;
    return 1;
}

int func_0202e428(void *object)
{
    (void) object;
    return 0;
}

int func_0202e424(void *object)
{
    (void) object;
    return 0;
}
