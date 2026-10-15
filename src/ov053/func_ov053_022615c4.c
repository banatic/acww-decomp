/* func_ov053_022615c4 @ 0x022615c4, 0x88 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022615c4 UnkStruct_022615c4;
struct UnkStruct_022615c4 {
    char pad_00[0x4e8];
    unsigned int unk_4E8;
    char pad_4EC[0x22d];
    unsigned char unk_719;
    char pad_71A[2];
    unsigned short unk_71C;
};

typedef struct UnkStruct_022615c4_2 UnkStruct_022615c4_2;

extern int func_0202ec58(UnkStruct_022615c4 *p);
extern UnkStruct_022615c4_2 *data_020ccf94;
extern int func_02073d90(UnkStruct_022615c4_2 *p);
extern int func_02030864(int);
extern void func_ov053_02261524(UnkStruct_022615c4 *p, int);
extern int func_020b65b8(void);

int func_ov053_022615c4(UnkStruct_022615c4 *param)
{
    UnkStruct_022615c4_2 *p;

    if (func_0202ec58(param) == 0) {
        return 0;
    }

    p = data_020ccf94;

    if (func_02073d90(p) == 0) {
        func_02030864(0);
    }

    param->unk_71C = 0;
    param->unk_4E8 |= 2;
    param->unk_719 = 0;

    if (func_02073d90(p) != 0) {
        func_ov053_02261524(param, 1);
        return 1;
    } else {
        if (func_020b65b8() == 29) {
            func_ov053_02261524(param, 0);
        } else {
            func_ov053_02261524(param, 1);
        }
        return 1;
    }
}
