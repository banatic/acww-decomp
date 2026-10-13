/* func_ov068_022761d0 @ 0x022761d0, 0x20 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202dc3c(void *ptr, int value, int count);

typedef struct {
    char pad_00[0x1a4];
    int unk_1A4;
} UnkStruct_022761d0;

void func_ov068_022761d0(UnkStruct_022761d0 *obj, int val)
{
    func_0202dc3c(obj, val, 0x11);
    obj->unk_1A4 = val;
}
