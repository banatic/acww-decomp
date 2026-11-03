/* cafe_guest_6: 13 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0227492c @ 0x0227492c, 0xb0 bytes, Thumb
 * func_ov068_022748f0 @ 0x022748f0, 0x3c bytes, Thumb
 * func_ov068_02274878 @ 0x02274878, 0x78 bytes, Thumb
 * func_ov068_0227483c @ 0x0227483c, 0x3c bytes, Thumb
 * func_ov068_02274838 @ 0x02274838, 0x4 bytes, Thumb
 * func_ov068_02274834 @ 0x02274834, 0x4 bytes, Thumb
 * func_ov068_02274830 @ 0x02274830, 0x4 bytes, Thumb
 * func_ov068_02274810 @ 0x02274810, 0x20 bytes, Thumb
 * func_ov068_02274790 @ 0x02274790, 0x80 bytes, Thumb
 * func_ov068_02274734 @ 0x02274734, 0x5c bytes, Thumb
 * func_ov068_02274714 @ 0x02274714, 0x20 bytes, Thumb
 * func_ov068_022746fc @ 0x022746fc, 0x18 bytes, Thumb
 * func_ov068_022746dc @ 0x022746dc, 0x20 bytes, Thumb
 */

struct UnkStruct_022748f0 {
    char pad_00[0x730];
    int unk_730;
};

typedef struct StructWithOffsets {
    unsigned char pad_00[0x3b0];
    unsigned char unk_3B0;
    unsigned char pad_3B1[0x1b3];
    unsigned char unk_564;
    unsigned char pad_565[0xb3];
    unsigned char unk_618;
    unsigned char pad_619[0x117];
    unsigned int unk_730;
} StructWithOffsets;

extern void func_0201ad18(void *, int, int, int, int, int, int, int);
extern int func_02019c20(void *, int, int, int, int, int);
extern void func_0201acbc(void *, int, int, int, int, int);
extern int data_020c814c;
extern unsigned short data_020c80f8;
extern short data_020c80f4;
extern short data_020c80ec;
extern unsigned char data_021fbee8[];
extern int func_ov068_022739f4(struct UnkStruct_022748f0 *p);
extern void func_020ee470(struct UnkStruct_022748f0 *p);
extern void func_ov004_0222daf0(void);
extern void func_ov004_0222dad8(void);
extern int func_020147e0(void *p, int a, int b);
extern int func_02014868(void *);
extern int func_0203e020(void *);
extern void func_ov068_022749dc(void *, int);
extern int func_020960f8(int, int);
extern int func_ov004_02246eb8(void);
extern void func_02035684(int, int, int);
extern void func_020355b8(void);
extern int func_ov004_0222c070(int);
extern void func_02035624(int);
extern void func_020355cc(void);
extern int func_0203b144(void);
extern void *func_0202eb70(void *obj);
extern void func_020f9680(void *obj);
extern char data_ov068_02277dc0;
extern void *func_0202eb20(void *);
extern void func_020edb3c(void *a);

int func_ov068_0227492c(void *self)
{
    if (*(int *) ((char *) self + 0x730) == 7) {
        func_0201ad18((char *) self + 0x3b0, 0, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
        func_02019c20((char *) self + 0x564, 1, 0x105, 0, data_020c80f8, 0);
        func_0201acbc((char *) self + 0x3b0, 0, -3096, 0, data_020c80f4, data_020c80ec);
    } else {
        func_0201ad18((char *) self + 0x3b0, 1, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    }
    return 1;
}

int func_ov068_022748f0(struct UnkStruct_022748f0 *p)
{
    int field = p->unk_730;
    if (field == 8) {
        func_020ee470(p);
        return 1;
    } else if (field == 7) {
        func_ov068_022739f4(p);
    } else {
        func_ov004_0222daf0();
    }
    if (p->unk_730 == 6) {
        func_ov004_0222dad8();
    }
    return 1;
}

int func_ov068_02274878(StructWithOffsets *this)
{
    if (this->unk_730 == 7) {
        func_02019c20(&this->unk_564, 1, 0x102, 0, data_020c80f8, 0);
    }
    func_0201ad18(&this->unk_3B0, 4, 0, 0, (unsigned int) data_021fbee8, 4, (*(unsigned int *) &data_020c814c), 0);
    func_020147e0(&this->unk_618, 0, 0);
    return 1;
}

int func_ov068_0227483c(void *self)
{
    if (func_02014868((char *) self + 0x618)) {
        return 1;
    }
    if (!func_02014868((char *) self + 0x618)) {
        func_0203e020(self);
        func_ov068_022749dc(self, 4);
    }
    return 1;
}

int func_ov068_02274838(void)
{
    return 1;
}

int func_ov068_02274834(void)
{
    return 1;
}

int func_ov068_02274830(void)
{
    return 1;
}

int func_ov068_02274810(int param)
{
    int result;
    int r4 = param;
    result = func_020960f8(0x28, 4);
    if (result != 0) {
        func_ov068_022749dc((void *) r4, 2);
    }
    return 1;
}

int func_ov068_02274790(void *p)
{

    (void) ((void *) func_02019c20((char *) p + 0x564, 1, 0x102, 0, (unsigned short) data_020c80f8, 0));
    func_ov004_02246eb8();
    func_0201acbc((char *) p + 0x3b0, 0, 0, 0x1000, (short) data_020c80f4, (short) data_020c80ec);
    func_020147e0((char *) p + 0x618, 0, 1);
    func_02035684(0x10, 0xf, 0);
    func_020355b8();
    return 1;
}

int func_ov068_02274734(char *self)
{
    if (func_02014868(self + 0x618)) {
        return 1;
    }
    if (!func_02014868(self + 0x618)) {
        func_0203e020(self);
        if (func_020960f8(0x28, 4)) {
            func_ov004_0222c070(0);
        }
        func_02035624(0x10);
        func_020355cc();
        func_0203b144();
        func_ov068_022749dc(self, 4);
    }
    return 1;
}

void *func_ov068_02274714(void *self)
{
    func_0202eb70(self);
    *(void **) self = (void *) &data_ov068_02277dc0;
    func_020f9680((char *) self + 0xbc);
    return self;
}

void *func_ov068_022746fc(void *this)
{
    *(int **) this = ((int *) &data_ov068_02277dc0);
    func_0202eb20(this);
    return this;
}

void *func_ov068_022746dc(void *p)
{
    *(void **) p = &data_ov068_02277dc0;
    func_0202eb20(p);
    func_020edb3c(p);
    return p;
}
