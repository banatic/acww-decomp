/* func_ov122_022a0774 @ 0x022a0774, 0x30 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xb4];
    unsigned char b4;
} UnkStruct_022a0774;

extern unsigned short data_021fbe40;
extern void func_ov002_02208098(UnkStruct_022a0774 *obj, unsigned char b);
extern void func_ov122_022a14c0(UnkStruct_022a0774 *obj);

void func_ov122_022a0774(UnkStruct_022a0774 *obj)
{
    int masked = data_021fbe40 & 0x100;
    if (masked != 0) {
        return;
    }
    func_ov002_02208098(obj, obj->b4);
    func_ov122_022a14c0(obj);
}
