/* func_0201e2d8 @ 0x0201e2d8, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(int);
extern int func_02019de8(int);
extern int func_02019c6c(int, int, unsigned short);
extern unsigned short data_020c80f8;
extern unsigned int data_020d8f58[2];

struct Pair {
    unsigned int a;
    unsigned int b;
};

struct UnkStruct_0201e2d8 {
    unsigned char pad_00[0xf0];
    unsigned int unk_F0;
    unsigned int unk_F4;
    unsigned char pad_F8[8];
    int unk_100;
};

void func_0201e2d8(struct UnkStruct_0201e2d8 *p)
{
    if (func_02019e00(p->unk_100 + 0x564) != 2) {
        return;
    }
    if (func_02019de8(p->unk_100 + 0x564) == 0) {
        return;
    }
    func_02019c6c(p->unk_100 + 0x564, 2, data_020c80f8);
    *(struct Pair *) &p->unk_F0 = *(struct Pair *) &data_020d8f58;
}
