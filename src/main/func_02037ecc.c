/* func_02037ecc @ 0x02037ecc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02037ecc {
    unsigned char pad_00[0xc];
    int unk_0C;
} UnkStruct_02037ecc;
typedef struct {
    unsigned char pad_00[4];
    int unk_04;
    int unk_08;
    unsigned char pad_0C[0x14];
    UnkStruct_02037ecc *unk_20;
} UnkStruct_02037ecc_2;
extern int func_02030c84(int a, int b, int c, int d);
void func_02037ecc(UnkStruct_02037ecc_2 *p, UnkStruct_02037ecc *v, int flag, int d)
{
    p->unk_20 = v;
    if (p->unk_20 != 0) {
        flag = p->unk_20->unk_0C;
    }
    if (flag != 0) {
        func_02030c84(p->unk_04, p->unk_08, flag, d);
    }
}