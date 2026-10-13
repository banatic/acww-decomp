/* func_02094c38 @ 0x02094c38, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct UnkStruct_02094c38 {
    unsigned char v[4];
} UnkStruct_02094c38;
typedef struct UnkStruct_02094c38_2 {
    int unk_00;
    UnkStruct_02094c38 unk_04;
    int unk_08;
    void *unk_0C;
} UnkStruct_02094c38_2;

extern char data_021d5658[];
extern char data_021d52d8[];
extern void func_02094d6c(void *, void *, int, int);
extern void func_02090db0(void *);
extern void MI_CpuCopy8(void *, void *, int);

void func_02094c38(UnkStruct_02094c38_2 *a, int b, int c)
{
    UnkStruct_02094c38 tmp;
    char *g = data_021d5658;

    tmp = a->unk_04;
    func_02094d6c(a->unk_0C, g, b, c);
    func_02090db0(a->unk_0C);
    MI_CpuCopy8(g, data_021d52d8 + tmp.v[0] * 0x1c, 0x1c);
}
