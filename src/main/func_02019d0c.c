/* func_02019d0c @ 0x02019d0c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02019d0c_2 {
    char pad_00[4];
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    char pad_14[4];
    short unk_18;
    short unk_1A;
    unsigned short unk_1C;
    unsigned short unk_1E;
} UnkStruct_02019d0c_2;

typedef struct UnkStruct_02019d0c {
    char pad_00[0x28];
    int unk_28;
    UnkStruct_02019d0c_2 sub;
} UnkStruct_02019d0c;

extern void func_02019d70(UnkStruct_02019d0c *s, int kind, int value);
extern void func_02019ea0(UnkStruct_02019d0c_2 *sub);

int func_02019d0c(UnkStruct_02019d0c *s, int kind, int value, int r3val, int argA, short argB, short argC, int argD, int argE,
                  unsigned short argF, unsigned short argG)
{
    int result = 0;
    if (value >= s->unk_28 || s->unk_28 == 3) {
        if (kind != 0xc) {
            UnkStruct_02019d0c_2 *sub = &s->sub;
            short c;
            short b;
            func_02019d70(s, kind, value);
            func_02019ea0(sub);
            sub->unk_04 = r3val;
            sub->unk_08 = argA;
            if (argD == 0 && argE == 0) {
                sub->unk_0C = r3val;
                sub->unk_10 = argA;
            } else {
                sub->unk_0C = argD;
                sub->unk_10 = argE;
            }
            c = argC;
            b = argB;
            sub->unk_18 = c;
            sub->unk_1A = b;
            sub->unk_1C = argF;
            sub->unk_1E = argG;
            result = 1;
        }
    }
    return result;
}
