/* func_ov003_0221fdc8 @ 0x0221fdc8, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int FX_Div(int, int);
extern void func_02030b80(int);
extern int data_ov003_0223cad4;

typedef struct {
    char pad[1];
    unsigned char unk_01;
} UnkStruct_0221fdc8;
typedef struct {
    char pad[0xe8];
    signed char unk_E8;
} UnkStruct_0221fdc8_2;
typedef struct {
    char pad[0x2c];
    UnkStruct_0221fdc8_2 *unk_2C;
} UnkStruct_0221fdc8_3;
typedef struct {
    char pad[0x28];
    int unk_28;
} Bb;
typedef struct {
    UnkStruct_0221fdc8 *unk_00;
    UnkStruct_0221fdc8_3 *unk_04;
    char pad[0xa8];
    Bb *unk_B0;
} UnkStruct_0221fdc8_4;

void func_ov003_0221fdc8(UnkStruct_0221fdc8_4 *s)
{
    UnkStruct_0221fdc8_2 *t;
    unsigned char c;
    if (data_ov003_0223cad4 == 0) {
        t = s->unk_04->unk_2C;
        c = s->unk_00->unk_01;
        if (t != 0 && t->unk_E8 == c) {
            func_02030b80(FX_Div(s->unk_B0->unk_28 + 0xda2, 0xda2));
            data_ov003_0223cad4 = 1;
        }
    }
}
