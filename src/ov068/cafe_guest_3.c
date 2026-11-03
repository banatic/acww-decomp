/* cafe_guest_3: 3 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02274224 @ 0x02274224, 0x14 bytes, Thumb
 * func_ov068_022741e4 @ 0x022741e4, 0x40 bytes, Thumb
 * func_ov068_02274194 @ 0x02274194, 0x50 bytes, Thumb
 */

struct UnkStruct_02274224 {
    char pad_00[0xb4];
    unsigned char *data;
};

struct UnkStruct_02274194 {
    char pad_00[0x652];
    unsigned short unk_652;
    char pad_654[0xf7];
    char unk_74B;
    char unk_74C;
};

struct UnkStruct_02274194_2 {
    char pad_00[0xb4];
    struct UnkStruct_02274194 *inner;
};

extern int func_02099e9c(void *ptr);
extern void func_0209a050(int index);
extern int func_0209a000(void *ptr, int val);
extern unsigned short func_ov068_02273980(void);

void func_ov068_02274224(struct UnkStruct_02274224 *self, int flag)
{
    if (flag == 0) {
        self->data[0x74a] = 1;
    }
}

void func_ov068_022741e4(int unused, int flag)
{
    short a;
    short b;
    int index;
    if (flag != 0) {
        return;
    }
    a = 0x3530;
    if ((index = func_02099e9c(&a)) == -1) {
        return;
    }
    func_0209a050(index);
    b = 0x4a34;
    func_0209a000(&b, 0);
}

void func_ov068_02274194(struct UnkStruct_02274194_2 *obj, int cond)
{
    if (cond == 0) {
        obj->inner->unk_74C = 1;
    } else {
        obj->inner->unk_74C = 0;
        obj->inner->unk_74B = 0;
        obj->inner->unk_652 =
            (unsigned short) ((void) *(struct UnkStruct_02274194 *volatile *) &obj->inner, func_ov068_02273980());
    }
}
