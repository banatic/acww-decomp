/* func_020882f0 @ 0x020882f0, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020642e0(void *ptr);
struct UnkStruct_020882f0 {
    unsigned char pad_00[0xe];
    unsigned char unk_0E;
};
void func_020882f0(struct UnkStruct_020882f0 *param)
{
    func_020642e0(param);
    param->unk_0E &= ~0x0f;
    param->unk_0E &= ~0x10;
    param->unk_0E &= ~0x20;
}
