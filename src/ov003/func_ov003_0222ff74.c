/* func_ov003_0222ff74 @ 0x0222ff74, 0x68 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x18];
    int unk_18;
    int unk_1C;
    char pad_20[0x130 - 0x20];
    char sub130[0x100];
    char sub230[0x19];
    unsigned char unk_249;
    char pad_24A[3];
    unsigned char unk_24D;
    char pad_24E[2];
    unsigned char unk_250;
    char pad_251[0xb];
} UnkStruct_0222ff74;

extern void func_0209d238(char *a, char *b);
extern void func_0209d0a4(char *p);
extern UnkStruct_0222ff74 data_ov003_02260994[];

int func_ov003_0222ff74(char *a, int e, int idx)
{
    UnkStruct_0222ff74 *s = &data_ov003_02260994[idx];
    if (s->unk_250 == 0) {
        func_0209d238(a + 0x68, s->sub230);
        func_0209d0a4(s->sub130);
        s->unk_249 = 1;
        s->unk_18 = 0;
        s->unk_1C = 0;
        s->unk_24D = (unsigned char) e;
        s->unk_250 = 2;
        return 1;
    }
    return 0;
}
