/* func_ov003_0221dc38 @ 0x0221dc38, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int NNS_G3dBindMdlTex(void *, void *);
extern int NNS_G3dBindMdlPltt(void *, void *);

typedef struct {
    char pad_00[0x198];
    void *unk_198;
    char pad_19C[0x118];
    void *unk_2B4;
    void *unk_2B8;
} UnkStruct_0221dc38;

void func_ov003_0221dc38(UnkStruct_0221dc38 *p)
{
    if (p->unk_2B4 != 0) {
        NNS_G3dBindMdlTex(p->unk_198, p->unk_2B4);
    }
    if (p->unk_2B8 != 0) {
        NNS_G3dBindMdlTex(p->unk_198, p->unk_2B8);
        NNS_G3dBindMdlPltt(p->unk_198, p->unk_2B8);
    }
}
