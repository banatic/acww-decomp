/* func_02056730 @ 0x02056730, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[40];
} UnkStruct_02056730;

extern int func_02056958(UnkStruct_02056730 *p);
extern void func_020569b0(UnkStruct_02056730 *p, unsigned int a, unsigned int b, unsigned int c, unsigned int d);

typedef struct {
    char pad_00[8];
    unsigned int unk_08;
    char pad_0C[12];
    unsigned int unk_18;
    unsigned int unk_1C;
    unsigned int unk_20;
    char pad_24[2];
    unsigned char unk_26;
    char pad_27;
    UnkStruct_02056730 *unk_28;
} UnkStruct_02056730_2;

void func_02056730(UnkStruct_02056730_2 *s)
{
    unsigned int flag = (s->unk_08 << 4) >> 16;
    int i;
    for (i = 0; i < s->unk_26; i++) {
        if (func_02056958(s->unk_28 + i) == 0) {
            func_020569b0(s->unk_28 + i, flag, s->unk_20, s->unk_1C, s->unk_18);
        }
    }
}
