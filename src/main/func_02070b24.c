/* func_02070b24 @ 0x02070b24, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02002dc8(int arg);
extern int func_02002e04(int arg);

struct UnkStruct_02070b24 {
    char pad_00[0x2c];
    int unk_2C;
    char pad_30[0x38 - 0x30];
    char unk_38;
    char unk_39;
    char pad_3A[0x50 - 0x3a];
    int unk_50;
    char pad_54[0x55 - 0x54];
    char unk_55;
};

struct UnkStruct_02070b24_2 {
    char pad_00[0x68];
    struct UnkStruct_02070b24 *unk_68;
};

void func_02070b24(struct UnkStruct_02070b24_2 *a, int b, char c, char d)
{
    int r = func_02002dc8(b);
    if (a->unk_68) {
        a->unk_68->unk_2C = r;
        if (func_02002e04(b)) {
            a->unk_68->unk_50 = 2;
        } else {
            a->unk_68->unk_50 = 1;
        }
        if (r == 4) {
            a->unk_68->unk_55 = 1;
        } else {
            a->unk_68->unk_55 = 0;
        }
        a->unk_68->unk_39 = d;
        a->unk_68->unk_38 = c;
    }
}
