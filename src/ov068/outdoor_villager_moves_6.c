/* outdoor_villager_moves_6: 5 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_022690f8 @ 0x022690f8, 0x30 bytes, Thumb
 * func_ov068_022690f4 @ 0x022690f4, 0x4 bytes, Thumb
 * func_ov068_0226906c @ 0x0226906c, 0x88 bytes, Thumb
 * func_ov068_02269028 @ 0x02269028, 0x44 bytes, Thumb
 * func_ov068_02268fac @ 0x02268fac, 0x7c bytes, Thumb
 */

struct UnkStruct_02268fac {
    char pad_00[0x1c];
    unsigned char unk_1C;
};

struct OtherStruct {
    char pad_00[0x9f4];
    char unk_9F4;
    char pad_9F5[0xa06 - 0x9f4 - 1];
    unsigned short unk_A06;
};

extern void func_ov068_0226cfd4(int);
extern int func_02019c6c(void *, int, unsigned short);
extern void func_0202e194(int);
extern unsigned short data_020c80f8;
extern int func_0201c2c8(void *a, int b);
extern int func_02019d0c(void *a, int b1, int b2, int b3, int b4, int b5, int b6, int b7, int b8, int b9, int b10);
extern void func_ov068_02266c34(void *a, void *b, int c, int d, int e, void *f, int g, int h, int i);
extern void func_0202e188(void *a);
extern void func_0201cbc4(void *a);
extern int data_020c814c;
extern unsigned char data_021fbee8[];
extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern short data_ov068_02276724[];
extern int func_ov068_02266e7c(char *ptr);
extern void func_ov068_02266e78(char *ptr, int val);
extern void func_ov068_0226cce8(struct UnkStruct_02268fac *a, struct OtherStruct *b, int val);
extern int func_ov068_0226c0e0(struct UnkStruct_02268fac *a, struct OtherStruct *b);

int func_ov068_022690f8(int p1, int p2)
{
    func_ov068_0226cfd4(p2);
    func_02019c6c((void *) (p2 + 0x564), 2, data_020c80f8);
    func_0202e194(p2);
    return 1;
}

int func_ov068_022690f4(void)
{
    return 0;
}

int func_ov068_0226906c(int unused, void *obj)
{
    int val = func_0201c2c8(obj, 4);
    func_ov068_0226cfd4((int) obj);
    func_02019d0c((char *) obj + 0x564, 3, 1, 0, 0, 0, val, 0, 0, data_020c80f8, 0);
    func_ov068_02266c34((char *) obj + 0x898, obj, 1, 0, 0, (void *) data_021fbee8, 4, data_020c814c, 1);
    func_0202e188(obj);
    func_0201cbc4((char *) obj + 0x83c);
    return 1;
}

void func_ov068_02269028(void *a0, char *a1)
{
    if (func_02019e00(a1 + 0x564) == 3) {
        if (func_02019de8(a1 + 0x564) != 0) {
            func_02019c6c(a1 + 0x564, 1, data_020c80f8);
            ((unsigned char *) a0)[0x1c] = 1;
        }
    }
}

void func_ov068_02268fac(struct UnkStruct_02268fac *a, struct OtherStruct *b)
{
    if (func_ov068_02266e7c(&b->unk_9F4) == 0) {
        a->unk_1C = 2;
        func_ov068_0226cce8(a, b, 0);
    } else {
        if (b->unk_A06 >= data_ov068_02276724[0]) {
            func_ov068_02266e78(&b->unk_9F4, 0);
            func_ov068_0226cce8(a, b, 0x15);
        } else {
            if (func_ov068_0226c0e0(a, b) != 0) {
                func_ov068_02266e78(&b->unk_9F4, 0);
                func_ov068_0226cce8(a, b, 0x13);
            }
        }
    }
}
