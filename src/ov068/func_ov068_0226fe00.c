/* func_ov068_0226fe00 @ 0x0226fe00, 0x28 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0209d088(void *arg);
extern void NNS_G3dMdlSetMdlAlpha(void *dest, int value, int size);

struct UnkStruct_0226fe00 {
    char pad_00[0x130];
    char unk_130[0x251 - 0x130];
    char unk_251;
};

void func_ov068_0226fe00(struct UnkStruct_0226fe00 *obj)
{
    NNS_G3dMdlSetMdlAlpha(func_0209d088(&obj->unk_130), 0, 0x1f);
    obj->unk_251 = 0x12;
}
