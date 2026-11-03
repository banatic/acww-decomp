/* friend_roster_input_5: 18 functions, module ov119
 * mwccarm 1.2/base -O4,s
 * func_ov119_0229bfa4 @ 0x0229bfa4, 0x38 bytes, Thumb
 * func_ov119_0229bf7c @ 0x0229bf7c, 0x28 bytes, Thumb
 * func_ov119_0229bee0 @ 0x0229bee0, 0x9c bytes, Thumb
 * func_ov119_0229be8c @ 0x0229be8c, 0x54 bytes, Thumb
 * func_ov119_0229be50 @ 0x0229be50, 0x3c bytes, Thumb
 * func_ov119_0229bdf0 @ 0x0229bdf0, 0x5e bytes, Thumb
 * func_ov119_0229bdbc @ 0x0229bdbc, 0x34 bytes, Thumb
 * func_ov119_0229bd80 @ 0x0229bd80, 0x3c bytes, Thumb
 * func_ov119_0229bd64 @ 0x0229bd64, 0x1a bytes, Thumb
 * func_ov119_0229bd40 @ 0x0229bd40, 0x24 bytes, Thumb
 * func_ov119_0229bcf8 @ 0x0229bcf8, 0x46 bytes, Thumb
 * func_ov119_0229bcb0 @ 0x0229bcb0, 0x48 bytes, Thumb
 * func_ov119_0229bc74 @ 0x0229bc74, 0x3c bytes, Thumb
 * func_ov119_0229bc48 @ 0x0229bc48, 0x2a bytes, Thumb
 * func_ov119_0229bc30 @ 0x0229bc30, 0x16 bytes, Thumb
 * func_ov119_0229bc14 @ 0x0229bc14, 0x1c bytes, Thumb
 * func_ov119_0229bbe4 @ 0x0229bbe4, 0x30 bytes, Thumb
 * func_ov119_0229bba8 @ 0x0229bba8, 0x3c bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229be50 {
    unsigned char pad_00[0xA0];
    unsigned char b0;
    unsigned char pad_A1[0x10];
    unsigned char b1;
};

typedef struct {
    unsigned char pad_00[0xb1];
    unsigned char unk_B1;
    unsigned char pad_B2[2];
    unsigned char unk_B4;
} SelfType;

typedef struct {
    char pad_00[0x9d];
    unsigned char unk_9D;
    char pad_9E[0x1a];
    int count;
} UnkStruct_0229bcf8;

struct UnkStruct_0229bcb0 {
    char pad_00[0xb8];
    int unk_B8;
};

typedef struct {
    unsigned char pad_00[0xb4];
    unsigned char flag;
} UnkStruct_0229bc48;

struct UnkStruct_0229bbe4 {
    char pad_00[0x9a];
    short unk_9A;
};

extern int func_0208e484(int);
extern int func_ov119_0229b188(int);
extern void func_ov119_0229b7e8(int);
extern void func_ov119_0229b7c8(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern int func_0206f56c(void);
extern void func_ov119_0229a4e4(void *p);
extern int func_ov002_02208014(void *receiver);
extern void func_ov119_0229b9a4(void *p);
extern int func_ov002_02208008(void *p);
extern int func_ov119_0229a420(void *p, int v);
extern int func_ov002_02209044(void *p, int v, void *q, u8 b);
extern void func_ov119_0229b8e4(void *p);
extern void func_ov002_0220a1dc(void *p);
extern int func_ov119_0229b884(void *p);
extern struct {
    u16 _pad0;
    u16 flags;
} data_021fbe40;
extern void func_ov002_02209114(int, int, int);
extern int func_ov119_0229a5cc(int, int);
extern void func_ov119_0229b510(struct UnkStruct_0229be50 *self);
extern void func_ov119_0229b49c(struct UnkStruct_0229be50 *self);
extern void func_ov119_0229ad5c(void *self);
extern int func_020ee45c(void *self);
extern void func_ov090_02298fa4(int x);
extern int func_ov119_0229ae68(void *receiver);
extern int func_020eae80(int x);
extern void func_ov119_0229a410(void *self, int x);
extern void func_ov119_0229a714(void *self);
extern int func_0206fe54(void);
extern void func_ov119_0229b828(void *);
extern int func_ov002_02208e28(void *);
extern int func_ov002_0220909c(void *);
extern void func_ov002_022096d8(void *, int);
extern int func_0208e4bc(void *);
extern void func_ov119_0229a560(void *);
extern int func_ov002_02208e18(void *);
extern int func_ov002_0220b8ac(void *ptr, int arg);
extern void func_ov119_0229ae84(UnkStruct_0229bcf8 *, int);
extern void func_0200277c(int);
extern void func_ov119_0229a69c(UnkStruct_0229bcf8 *, unsigned char);
extern void func_02002708(int);
extern int func_0206fe60(void);
extern void *func_ov119_0229ae50(void *receiver);
extern void *func_02077c3c(void *object);
extern int func_02077d68(void *object);
extern int func_020eaf48(unsigned char a, int b);
extern void func_ov119_0229b248(const void *p, unsigned char b);
extern void func_ov119_0229ba3c(void *arg);
extern void func_ov002_02207fc0(void *arg);
extern unsigned char data_021f43ec;
extern int func_ov002_0220b9b8(int, void *, int, int);

void func_ov119_0229bc30(void *p);
void func_ov119_0229bbe4(struct UnkStruct_0229bbe4 *obj);

void func_ov119_0229bfa4(int r0)
{
    int r4 = r0;
    int r1;

    if (func_0208e484(r4 + 0xda8) != 0) {
        r1 = func_ov119_0229b188(r4);
        if (r1 == 1) {
            return;
        }
        if (r1 == 2) {
            func_ov119_0229b7e8(r4);
            return;
        }
        func_ov119_0229b7e8(r4);
    }
}

void func_ov119_0229bf7c(void *p)
{
    if (func_0208e484((int) ((char *) p + 0xda8))) {
        func_ov119_0229b7c8(p);
        func_ov002_02208098(p, 2);
    }
}

void func_ov119_0229bee0(char *param)
{
    if (func_0206f56c() != 0) {
        func_ov119_0229a4e4(param);
    } else if (func_ov002_02208014(param) != 0) {
        func_ov119_0229b9a4(param);
        func_ov002_02208098(param, 1);
    } else {
        int x = func_ov002_02208008(param);
        u8 y = (u8) func_ov119_0229a420(param, 0x10);
        if (func_ov002_02209044((char *) param + 0xdc, x, (char *) param + 0xae, y) != 0) {
            func_ov119_0229b8e4(param);
        } else {
            if (data_021fbe40.flags & 1) {
                func_ov002_0220a1dc((char *) param + 0xda8);
                func_ov002_02208098(param, 7);
            } else if (data_021fbe40.flags & 2) {
                func_ov119_0229b884(param);
            }
        }
    }
}

void func_ov119_0229be8c(int r0)
{
    int r4 = r0;
    if (func_0206f56c()) {
        func_ov119_0229a4e4((void *) r4);
        return;
    }
    if (func_0208e484(r4 + 0xda8)) {
        func_ov002_02209114(r4 + 0xdc, *(unsigned char *) (r4 + 0xae), 1);
        *(unsigned char *) (r4 + 0xad) = func_ov119_0229a5cc(r4, *(unsigned char *) (r4 + 0xae));
        func_ov002_02208098((void *) r4, 0xb);
    }
}

void func_ov119_0229be50(struct UnkStruct_0229be50 *self)
{
    if (self->b1 != 0) {
        self->b1--;
    } else {
        func_ov119_0229b9a4((void *) self);
        if (self->b0 == 0x16) {
            func_ov119_0229b510(self);
        } else {
            func_ov119_0229b49c(self);
        }
    }
}

void func_ov119_0229bdf0(SelfType *self)
{
    if (self->unk_B1 != 0) {
        self->unk_B1 = 0;
        func_ov119_0229ad5c(self);
        (void) func_ov090_02298fa4(func_020ee45c(self));
        if (func_ov119_0229ae68(self) != 0) {
            if (func_020eae80(self->unk_B4) == 0) {
                func_ov002_02208098(self, 0x11);
            }
        }
    } else {
        func_ov119_0229a410(self, 2);
        func_ov119_0229a714(self);
        func_ov119_0229bbe4((struct UnkStruct_0229bbe4 *) self);
    }
}

void func_ov119_0229bdbc(void *arg0)
{
    if (func_ov002_02208e28((char *) arg0 + 0xdc)) {
        if (func_0206fe54()) {
            func_ov119_0229b828(arg0);
            func_ov002_02208098(arg0, 6);
        } else {
            func_ov002_02208098(arg0, 1);
        }
    }
}

void func_ov119_0229bd80(void *p)
{
    if (func_ov002_0220909c((char *) p + 0xDC) != 0) {
        func_ov002_022096d8((char *) p + 0xDC, 0);
        if (func_0208e4bc((char *) p + 0xDA8) != 0) {
            func_ov119_0229b9a4(p);
        }
        func_ov002_02208098(p, 0xC);
    }
}

void func_ov119_0229bd64(void *self)
{
    if (func_ov002_02208e18((char *) self + 0xdc)) {
        func_ov119_0229a560(self);
    }
}

void func_ov119_0229bd40(void *ptr)
{
    if (func_ov002_0220b8ac((char *) ptr + 0x1efc, 1)) {
        func_ov119_0229bbe4((struct UnkStruct_0229bbe4 *) ptr);
    }
}

void func_ov119_0229bcf8(UnkStruct_0229bcf8 *self)
{
    if (self->count > 0) {
        self->count--;
        func_ov119_0229ae84(self, self->count);
    } else {
        func_0200277c(4);
        func_ov119_0229a69c(self, self->unk_9D);
        func_ov002_02208098((void *) self, 0xf);
    }
}

void func_ov119_0229bcb0(struct UnkStruct_0229bcb0 *p)
{
    if (p->unk_B8 < 5) {
        func_02002708(4);
        p->unk_B8++;
        func_ov119_0229ae84((UnkStruct_0229bcf8 *) p, p->unk_B8);
    } else {
        if (func_0206fe60()) {
            func_ov119_0229bc30((void *) p);
        } else {
            func_ov119_0229b7e8((int) p);
        }
    }
}

void func_ov119_0229bc74(const unsigned char *self)
{
    int v;

    v = (int) func_ov119_0229ae50((void *) self);
    v += self[0xb4] * 36;
    v = (int) func_02077c3c((void *) v);
    v = func_02077d68((void *) v);
    if (func_020eaf48(self[0xb4], v) != 0) {
        func_ov119_0229b248(self, self[0xb4]);
    }
}

void func_ov119_0229bc48(UnkStruct_0229bc48 *self)
{
    if (func_020eae80((unsigned char) self->flag)) {
        func_ov119_0229a410((void *) self, 2);
        func_ov119_0229a714((void *) self);
        func_ov119_0229bbe4((struct UnkStruct_0229bbe4 *) self);
    }
}

void func_ov119_0229bc30(void *p)
{
    func_ov119_0229b9a4((void *) p);
    func_ov002_02208098(p, 0);
}

void func_ov119_0229bc14(void *arg)
{
    func_ov119_0229ba3c(arg);
    func_ov002_02207fc0(arg);
    func_ov002_02208098(arg, 2);
}

void func_ov119_0229bbe4(struct UnkStruct_0229bbe4 *obj)
{
    obj->unk_9A = -1;
    func_ov119_0229a410((void *) obj, 4);
    if (func_0206fe60() != 0) {
        func_ov119_0229bc30((void *) obj);
    } else {
        func_ov119_0229bc14((void *) obj);
    }
}

void func_ov119_0229bba8(int arg0, unsigned char arg1)
{
    unsigned char local_0;
    unsigned char *local_ptr;

    local_ptr = &local_0;
    local_0 = data_021f43ec;
    *local_ptr = arg1;
    func_ov002_0220b9b8(arg0 + 0x1efc, local_ptr, 1, 0);
    func_ov002_02208098((void *) arg0, 0xd);
    func_ov119_0229b9a4((void *) arg0);
}
