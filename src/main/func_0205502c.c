/* func_0205502c @ 0x0205502c, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_G3dRenderObjRemoveAnmObj(int *addr, int val);

typedef struct {
    char pad_00[8];
    int unk_08;
    char pad_0C[0x18 - 0xC];
    int unk_18;
    char pad_1C[0xB4 - 0x1C];
    int flag;
} UnkStruct_0205502c;

void func_0205502c(UnkStruct_0205502c *p)
{
    if (p->flag != 0) {
        int *addr = &p->unk_08;
        NNS_G3dRenderObjRemoveAnmObj(addr, p->unk_18);
        p->flag = 0;
    }
}
