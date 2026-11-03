/* town_nook_3: 15 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226e874 @ 0x0226e874, 0x4 bytes, Thumb
 * func_ov068_0226e854 @ 0x0226e854, 0x1e bytes, Thumb
 * func_ov068_0226e81c @ 0x0226e81c, 0x38 bytes, Thumb
 * func_ov068_0226e7e4 @ 0x0226e7e4, 0x38 bytes, Thumb
 * func_ov068_0226e7ac @ 0x0226e7ac, 0x38 bytes, Thumb
 * func_ov068_0226e76c @ 0x0226e76c, 0x40 bytes, Thumb
 * func_ov068_0226e738 @ 0x0226e738, 0x34 bytes, Thumb
 * func_ov068_0226e708 @ 0x0226e708, 0x30 bytes, Thumb
 * func_ov068_0226e688 @ 0x0226e688, 0x80 bytes, Thumb
 * func_ov068_0226e648 @ 0x0226e648, 0x40 bytes, Thumb
 * func_ov068_0226e638 @ 0x0226e638, 0x10 bytes, Thumb
 * func_ov068_0226e604 @ 0x0226e604, 0x34 bytes, Thumb
 * func_ov068_0226e5ec @ 0x0226e5ec, 0x18 bytes, Thumb
 * func_ov068_0226e5d4 @ 0x0226e5d4, 0x18 bytes, Thumb
 * func_ov068_0226e5b4 @ 0x0226e5b4, 0x20 bytes, Thumb
 */

struct UnkStruct_0226e7ac {
    unsigned int a;
    unsigned int b;
    unsigned int c;
};

typedef struct {
    char pad_00[0x658];
    void *vtable;
} UnkStruct_0226e76c;

typedef struct {
    unsigned char pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    unsigned char pad_68[0x564 - 0x68];
    char unk_564[0x1b4];
    int unk_718;
    int unk_71C;
    int unk_720;
    unsigned char unk_724;
} UnkStruct_0226e688;

extern int func_0203e0a8(int, int);
extern void func_02095eec(int, int);
extern int func_02016104(void *);
extern int func_0201c314(void *, int);
extern int func_020147fc(void *, int, int, int);
extern int func_02014868(void *ptr);
extern int func_0203b144(void);
extern void func_02035684(int a, int b, int c);
extern void func_02035638(int a);
extern void func_ov068_0226e878(void *ptr, int b);
extern struct UnkStruct_0226e7ac *func_02095794(int);
extern int func_02095ab0(void *, unsigned int, unsigned int);
extern void *func_0209615c(int size);
extern int func_0201c2a4(void *self, int a);
extern void func_02016108(void *addr, int b);
extern int func_02019d0c(int, int, int, int, int, int, int, int, int, int, int);
extern unsigned short data_020c80f8;
extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern int func_020e8858(const void *);
extern int func_0203e020(const void *);
extern int func_020984e8(void);
extern void func_020a128c(void);
extern void func_02035624(int);
extern void func_020ee470(void *);
extern void *func_0202eb70(void *self);
extern void *func_0202eb20(void *);
extern void func_020edb3c(void *self);
extern unsigned char data_ov068_022774e4[];

int func_ov068_0226e874(void)
{
    return 1;
}

int func_ov068_0226e854(int param)
{
    if (func_0203e0a8(param, 0)) {
        func_02095eec(1, 4);
    }
    return 1;
}

int func_ov068_0226e81c(void *self)
{
    int size = func_02016104((char *) self + 0x658);
    int ret = 0;
    if (size != 0) {
        ret = func_0201c314(self, size);
    }
    func_020147fc((char *) self + 0x618, 0, ret, 1);
    return 1;
}

int func_ov068_0226e7e4(void *arg)
{
    if (func_02014868((char *) arg + 0x618) != 0) {
        goto done;
    }
    func_0203b144();
    func_02035684(0x13, 0x3c, 0);
    func_02035638(0x47);
    func_ov068_0226e878(arg, 3);
done:
    return 1;
}

int func_ov068_0226e7ac(void)
{
    struct UnkStruct_0226e7ac *src;
    struct UnkStruct_0226e7ac local;

    src = func_02095794(4);
    local.a = src->a;
    local.b = src->b;
    local.c = src->c;
    local.c += 0x2000;
    func_02095ab0(&local, 0x400, 4);
    return 1;
}

int func_ov068_0226e76c(UnkStruct_0226e76c *self)
{
    int r;
    if (func_0209615c(4) == 0) {
        (*(void (**)(void *))(*(void ***) ((char *) self + 0x658) + 2))((char *) self + 0x658);
        r = func_0201c2a4(self, 4);
        func_02016108((char *) self + 0x658, r);
        func_ov068_0226e878(self, 1);
    }
    return 1;
}

int func_ov068_0226e738(int param)
{
    func_02019d0c(param + 0x564, 3, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov068_0226e708(void *arg)
{
    if (func_02019e00((char *) arg + 0x564) == 3) {
        if (func_02019de8((char *) arg + 0x564) != 0) {
            func_ov068_0226e878(arg, 4);
        }
    }
    return 1;
}

int func_ov068_0226e688(UnkStruct_0226e688 *r4)
{
    r4->unk_718 = r4->unk_5C;
    r4->unk_71C = r4->unk_60;
    r4->unk_720 = r4->unk_64;
    r4->unk_718 -= 0x2000;
    r4->unk_720 += 0xa000;
    func_02019d0c((int) r4->unk_564, 2, 1, r4->unk_718, r4->unk_720, 0, 0, 0, 0, data_020c80f8, 0);
    r4->unk_724 = 0x3c;
    return 1;
}

int func_ov068_0226e648(char *p)
{
    if (func_02019de8((void *) (p + 0x564)) != 0 || func_020e8858(p + 0x724) == 0) {
        int r = func_0203e020(p);
        if (func_020984e8() != 0) {
            func_020a128c();
        }
    }
    return 1;
}

int func_ov068_0226e638(char *self)
{
    self[0x724] = 0xa;
    return 1;
}

int func_ov068_0226e604(void *arg0)
{
    if (func_020e8858((const void *) ((char *) arg0 + 0x724)) == 0) {
        func_02035624(0x13);
        func_02035684(0x12, 5, 5);
        func_020ee470(arg0);
    }
    return 1;
}

void *func_ov068_0226e5ec(void *self)
{
    func_0202eb70(self);
    *(void **) self = ((char *) data_ov068_022774e4);
    return self;
}

void *func_ov068_0226e5d4(void *self)
{
    *(void **) self = (void *) ((int *) data_ov068_022774e4);
    func_0202eb20(self);
    return self;
}

void *func_ov068_0226e5b4(void *self)
{
    *(void **) self = (void *) data_ov068_022774e4;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
