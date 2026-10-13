/* func_ov004_022226b4 @ 0x022226b4, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202dc3c(void *ptr, int value, int count);

typedef struct {
    char pad_00[0x1a8];
    int unk_1A8;
} UnkStruct_022226b4;

void func_ov004_022226b4(UnkStruct_022226b4 *obj, int val)
{
    func_0202dc3c(obj, val, 0x11);
    obj->unk_1A8 = val;
}
