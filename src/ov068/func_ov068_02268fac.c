/* func_ov068_02268fac @ 0x02268fac, 0x7c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
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

extern short data_ov068_02276724[];

extern int func_ov068_02266e7c(char *ptr);
extern void func_ov068_02266e78(char *ptr, int val);
extern void func_ov068_0226cce8(struct UnkStruct_02268fac *a, struct OtherStruct *b, int val);
extern int func_ov068_0226c0e0(struct UnkStruct_02268fac *a, struct OtherStruct *b);

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
