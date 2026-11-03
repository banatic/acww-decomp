/* outdoor_villager_acts_3: 4 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02267830 @ 0x02267830, 0xa0 bytes, Thumb
 * func_ov068_022677a0 @ 0x022677a0, 0x90 bytes, Thumb
 * func_ov068_02267728 @ 0x02267728, 0x78 bytes, Thumb
 * func_ov068_02267724 @ 0x02267724, 0x2 bytes, Thumb
 */

typedef struct UnkStruct_02267728 {
    unsigned char pad_00[0x1c];
    char unk_1C;
    unsigned char pad_1D[0x38 - 0x1c - 1];
    char unk_38;
    unsigned char pad_39[0x3a - 0x38 - 1];
    unsigned short unk_3A;
    unsigned char pad_3C[0xf4 - 0x3a - 2];
    int unk_F4;
} UnkStruct_02267728;

typedef struct UnkStruct_02267728_2 {
    unsigned char data[0xa0c];
    int unk_A0C;
} UnkStruct_02267728_2;

extern void func_02013aac(void *);
extern int func_020164a0(void *, int);
extern int func_02019de8(void *);
extern int func_02016104(void *);
extern int func_0201c314(void *, int);
extern void func_ov068_02266c34(void *, void *, int, int, int, const void *, int, int, int);
extern int func_020147fc(void *, int, int, int);
extern const int data_021fbee8[]; // 0x021fbee8
extern int data_020c814c;         // 0x020c814c
extern int func_02014868(const void *ptr);
extern void func_ov068_0226ad78(UnkStruct_02267728 *a, UnkStruct_02267728_2 *b, int, int, int);
extern void func_0203eddc(UnkStruct_02267728_2 *b);
extern int func_0203e020(UnkStruct_02267728_2 *b);
extern void func_0201ce5c(UnkStruct_02267728_2 *b, int);
extern void func_0201ce44(UnkStruct_02267728_2 *b, int);
extern void func_ov068_0226cce4(UnkStruct_02267728 *a, int);

int func_ov068_02267830(char *self, char *obj)
{
    int a, b;

    func_02013aac(obj);
    if (func_020164a0(obj + 0x334, 0) == 0xec) {
        if (func_02019de8(obj + 0x564) == 0) {
            goto zero;
        }
    }
    a = func_02016104(obj + 0x680);
    b = 0;
    if (a != 0) {
        b = func_0201c314(obj, a);
    }
    func_ov068_02266c34(obj + 0x898, obj, 1, 0, 0, data_021fbee8, 4, data_020c814c, 1);
    func_020147fc(obj + 0x618, 0, b, 0);
    self[0x1c] = 1;
    goto out;
zero:
    self[0x1c] = 0;
out:
    return 1;
}

void func_ov068_022677a0(char *self, unsigned char *obj)
{
    int a, b;

    if (func_020164a0(obj + 0x334, 0) == 0xec) {
        if (func_02019de8(obj + 0x564) == 0) {
            return;
        }
    }
    a = func_02016104(obj + 0x680);
    b = 0;
    if (a != 0) {
        b = func_0201c314((void *) obj, a);
    }
    func_ov068_02266c34(obj + 0x898, obj, 1, 0, 0, data_021fbee8, 4, data_020c814c, 1);
    func_020147fc(obj + 0x618, 0, b, 0);
    self[0x1c] = 1;
}

void func_ov068_02267728(UnkStruct_02267728 *a, UnkStruct_02267728_2 *b)
{
    if (func_02014868(&b->data[0x618]) != 0) {
        return;
    }
    func_ov068_0226ad78(a, b, 4, 1, 1);
    func_0203eddc(b);
    func_0203e020(b);
    func_0201ce5c(b, 0);
    func_0201ce44(b, 0);
    func_ov068_0226cce4(a, 0);
    a->unk_38 = 0;
    a->unk_3A = 0;
    b->unk_A0C = 3;
    a->unk_F4 = 0x4b0;
    a->unk_1C = 2;
}

void func_ov068_02267724(void *object, int event) {}
