/* func_ov068_022693f0 @ 0x022693f0, 0x60 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x1c];
    unsigned char unk_1C;
    int unk_20;
} UnkStruct_022693f0;

extern unsigned short data_020c80f8;
extern int func_02019e00(char *addr);
extern int func_02019de8(char *addr);
extern int func_02019c6c(char *addr, int val, unsigned short data);
extern int func_ov068_0226c0e0(UnkStruct_022693f0 *a, char *b);
extern void func_ov068_0226cce8(UnkStruct_022693f0 *a, char *b, int c);

void func_ov068_022693f0(UnkStruct_022693f0 *a, char *b)
{
    if (func_02019e00(b + 0x564) == 3 && func_02019de8(b + 0x564) != 0) {
        func_02019c6c(b + 0x564, 1, data_020c80f8);
        a->unk_1C = 4;
        a->unk_20 = 10;
    } else {
        if (func_ov068_0226c0e0(a, b) != 0) {
            func_ov068_0226cce8(a, b, 0x13);
        }
    }
}
