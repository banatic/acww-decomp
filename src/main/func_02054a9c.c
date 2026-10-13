/* func_02054a9c @ 0x02054a9c, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x10];
    int unk_10;
} UnkStruct_02054a9c;
typedef struct {
    unsigned char pad_00[8];
    unsigned char sub[0x10];
    UnkStruct_02054a9c *unk_18;
} UnkStruct_02054a9c_2;
extern void NNS_G3dRenderObjRemoveAnmObj(void *p, UnkStruct_02054a9c *y);
extern void NNS_G3dRenderObjAddAnmObj(void *p, UnkStruct_02054a9c *q);
void func_02054a9c(UnkStruct_02054a9c_2 *p, UnkStruct_02054a9c *q)
{
    UnkStruct_02054a9c *y = p->unk_18;
    if (y != q && y != 0 && y->unk_10 == 0) {
        NNS_G3dRenderObjRemoveAnmObj(p->sub, y);
        NNS_G3dRenderObjAddAnmObj(p->sub, q);
    }
}
