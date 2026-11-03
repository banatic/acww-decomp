/* sky_objects: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020bc548 @ 0x020bc548, 0x7c bytes, Thumb
 * func_020bc514 @ 0x020bc514, 0x32 bytes, Thumb
 * func_020bc4f8 @ 0x020bc4f8, 0x1c bytes, Thumb
 * func_020bc4dc @ 0x020bc4dc, 0x1c bytes, Thumb
 * func_020bc464 @ 0x020bc464, 0x78 bytes, Thumb
 * func_020bc42c @ 0x020bc42c, 0x38 bytes, Thumb
 * func_020bc428 @ 0x020bc428, 0x2 bytes, Thumb
 * func_020bc388 @ 0x020bc388, 0xa0 bytes, Thumb
 * func_020bc380 @ 0x020bc380, 0x8 bytes, Thumb
 */

typedef struct UnkStruct_020bc514 {
    unsigned char data[0x60];
    int unk_60;
    unsigned char pad_64[0x10];
} UnkStruct_020bc514;

struct Object {
    char pad_00[0x2f08];
    int unk_2F08;
    int unk_2F0C;
};

struct Global {
    char pad_00[0x34];
    int state;
};

typedef struct {
    char pad_00[0x24];
    int unk_24;
    char pad_28[0x0C];
    int unk_34;
} UnkStruct_020bc42c;

extern unsigned char data_021f87c0[];
extern struct UnkStruct_020bc548 {
    int unk_00;
    int unk_04;
} data_021f75b0;
extern int func_020be0d4(void *p, int a);
extern void *func_020bdc50(void *p, int a, int b, int c, int d);
extern void func_020be0a8(void *arg);
extern void func_020be628(void *ptr);
extern void func_020be600(void *ptr);
extern void func_020be0a0(void *ptr);
extern struct Global data_021f8ab0;
extern void func_020bd938(struct Object *);
extern void func_020bd7a4(struct Object *);
extern void func_020bceb4(struct Object *);
extern void func_020bd688(struct Object *);
extern void func_020bd054(struct Object *);
extern void func_020bd6d0(struct Object *);
extern void func_020bd3b4(struct Object *);
extern int func_020b65c4(void);
extern void func_020bd2d0(struct Object *);
extern void func_020bd1c4(struct Object *);
extern void func_020bd124(struct Object *);
extern void func_020bcfbc(struct Object *);
extern int func_020b6840(int param);
extern void func_020bda88(int arg);
extern void func_020bde24(void *self);
extern void func_020be388(void *self);
extern void func_020bf5b8(void *p);
extern void func_0208a0c8(void *base);
extern void func_020bf700(void *p);
extern void func_020bf5f0(void *p);
extern void func_020be348(void *self);
extern void func_020bea1c(void *p);
extern void func_020be568(void *p);

void func_020bc548(unsigned char *param)
{
    unsigned short *ptr;
    unsigned short *end1;
    unsigned short *end2;
    unsigned char byte;
    unsigned short value;
    int mult;
    int i;
    int tmp;

    ptr = (unsigned short *) (data_021f87c0 + data_021f75b0.unk_04 * 0x180);
    end1 = (unsigned short *) ((char *) ptr + 0xee);
    end2 = (unsigned short *) ((char *) ptr + 0x12e);
    byte = param[0x2f51];
    value = (unsigned short) (byte | 0x1000);

    while (ptr < end1) {
        *ptr++ = value;
    }

    mult = -((int) byte << 12) / 0x20;
    i = 0;
    while (ptr < end2) {
        tmp = ((mult * i + 0x800) >> 12) + byte;
        *ptr++ = (unsigned short) (tmp | 0x1000);
        i++;
    }
}

void func_020bc514(UnkStruct_020bc514 *param)
{
    int index;
    UnkStruct_020bc514 *r4;
    index = func_020be0d4(param, 3);
    r4 = param + index;
    if (r4 != 0) {
        func_020bdc50(param, 2, 0x3c, 0, 1);
        r4->unk_60 = 1;
    }
}

void func_020bc4f8(void *arg)
{
    func_020be0a8(arg);
    func_020be628((char *) arg + 0x2fcc);
}

void func_020bc4dc(void *arg)
{
    func_020be600((char *) arg + 0x2fcc);
    func_020be0a0(arg);
}

void func_020bc464(struct Object *obj)
{
    switch (data_021f8ab0.state) {
        case 1:
            func_020bd938(obj);
            break;
        case 2:
            func_020bd7a4(obj);
            break;
        default:
            obj->unk_2F08 = 0;
            obj->unk_2F0C = 0;
            break;
    }
    func_020bceb4(obj);
    func_020bd688(obj);
    func_020bd054(obj);
    func_020bd6d0(obj);
    func_020bd3b4(obj);
    if (func_020b65c4() != 0x2c) {
        func_020bd2d0(obj);
        func_020bd1c4(obj);
        func_020bd124(obj);
        func_020bcfbc(obj);
    }
}

void func_020bc42c(int arg)
{
    int result;
    result = func_020b6840(0);
    if (result == 0 || result == 3) {
        return;
    }
    if ((*(UnkStruct_020bc42c *) &data_021f8ab0).unk_34 == 1 && (*(UnkStruct_020bc42c *) &data_021f8ab0).unk_24 == 4) {
        func_020bda88(arg);
    }
    func_020bd3b4((struct Object *) arg);
}

void func_020bc428(void *object) {}

void func_020bc388(void *self)
{
    char *p = (char *) self;
    char *end = (char *) self + 0x1b30;
    int *counter;
    char *base;

    func_020bde24(self);
    func_020bc428(self);
    func_020bc464((struct Object *) self);

    counter = (int *) ((char *) self + 0x2f14);

    while (p < end) {
        if (*(int *) (p + 8) != 0x34) {
            base = p + 0x10;
            switch (*(int *) (p + 4)) {
                case 1:
                    if (*(int *) (p + 0x24) != 6) {
                        func_020be388(self);
                    }
                    func_020bf5b8(p);
                    *(int *) (p + 4) = 2;
                    break;
                case 2:
                    func_0208a0c8(base);
                    func_020bf700(p);
                    break;
                case 3:
                    func_020bf5f0(p);
                    *counter = *counter - 1;
                    break;
                default:
                    break;
            }
        }
        p += 0x74;
    }

    func_020be348(self);
    func_020bea1c((char *) self + 0x2fa8);
    func_020be568((char *) self + 0x2fcc);
}

void func_020bc380(int argument0)
{
    func_020bc42c((int) argument0);
}
