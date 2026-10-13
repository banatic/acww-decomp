/* func_ov104_0229d500 @ 0x0229d500, 0x28 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209d84(void *);
extern int func_ov002_02209d7c(void *);

typedef struct {
    char pad_00[0xa8];
    int unk_A8;
    int unk_AC;
    char pad_B0[0x23d8];
    int sub;
} UnkStruct_0229d500;

void func_ov104_0229d500(UnkStruct_0229d500 *p)
{
    p->unk_A8 = func_ov002_02209d84(&p->sub);
    p->unk_AC = func_ov002_02209d7c(&p->sub);
}
