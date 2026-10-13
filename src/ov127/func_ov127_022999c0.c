/* func_ov127_022999c0 @ 0x022999c0, 0x40 bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022999c0 {
    char pad_00[0x282a];
    unsigned short unk_282A;
    short unk_282C;
};

extern void func_ov127_02299868(struct UnkStruct_022999c0 *obj, int val);

void func_ov127_022999c0(struct UnkStruct_022999c0 *obj, int a, int b)
{
    obj->unk_282A = (unsigned short) ((a - 0x80) & 0x1ff);
    obj->unk_282C = (short) (b - 0x60);
    if (obj->unk_282C < -24) {
        obj->unk_282C = -24;
    } else if (obj->unk_282C > 0x54) {
        obj->unk_282C = 0x54;
    }
    func_ov127_02299868(obj, 4);
}
