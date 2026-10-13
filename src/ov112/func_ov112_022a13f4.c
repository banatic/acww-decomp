/* func_ov112_022a13f4 @ 0x022a13f4, 0x68 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xA0];
    int unk_A0;
    int unk_A4;
    int unk_A8;
} UnkStruct_022a13f4;

extern int func_ov002_02207f3c(UnkStruct_022a13f4 *, int);
extern void func_020027f0(int);
extern void func_ov002_022080a0(UnkStruct_022a13f4 *, int);
extern void func_ov002_02207e80(UnkStruct_022a13f4 *, int, int, int);
extern int func_ov002_02207f60(UnkStruct_022a13f4 *);

void func_ov112_022a13f4(UnkStruct_022a13f4 *p)
{
    if (func_ov002_02207f3c(p, 0)) {
        func_020027f0(4);
        func_020027f0(6);
        func_ov002_022080a0(p, 5);
    } else {
        func_ov002_02207e80(p, 4, 0, -8);
        func_ov002_02207e80(p, 6, 0, -8);
    }
    p->unk_A4 = func_ov002_02207f60(p);
    p->unk_A8 = p->unk_A4;
    p->unk_A0 = p->unk_A4;
}
