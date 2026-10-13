/* func_02056498 @ 0x02056498, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x18];
    unsigned int *unk_18;
    unsigned int *unk_1C;
} UnkStruct_02056498;

typedef struct {
    char pad_00[4];
    unsigned short unk_04;
} UnkStruct_02056498_2;

extern void func_02056fcc(UnkStruct_02056498 *a, unsigned int b, int c, void *d, unsigned int e);
extern void NNS_G3dAnmObjInit(unsigned int *a, UnkStruct_02056498_2 *b, unsigned int *c, void *d);

void func_02056498(UnkStruct_02056498 *a, UnkStruct_02056498_2 *b, void *c, int d, void *e, unsigned short f)
{
    func_02056fcc(a, b->unk_04, d, e, f);
    NNS_G3dAnmObjInit(a->unk_18, b, a->unk_1C, c);
    *a->unk_18 = f << 12;
}
