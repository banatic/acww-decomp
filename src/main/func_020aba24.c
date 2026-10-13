/* func_020aba24 @ 0x020aba24, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020aba24 {
    char pad_00[0x6c];
    char unk_6C[0xd0];
    int unk_13C;
};

extern void func_0208f0c4(void *, int);

void func_020aba24(struct UnkStruct_020aba24 *obj)
{
    obj->unk_13C = 8;
    func_0208f0c4(obj->unk_6C, 2);
}
