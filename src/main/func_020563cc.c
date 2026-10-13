/* func_020563cc @ 0x020563cc, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_G3dRenderObjRemoveAnmObj(int param1, int param2, void *param3);

struct UnkStruct_020563cc {
    char pad_00[0x18];
    int unk_18;
};

void func_020563cc(struct UnkStruct_020563cc *a, int b)
{
    NNS_G3dRenderObjRemoveAnmObj(b, a->unk_18, a);
}
